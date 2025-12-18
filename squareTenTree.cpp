#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) int(a.size())

char l[1000007], r[1000007];
int m, n;

// Add 1 to string l at position pos
void plus1(int pos) {
    int t = 1;
    for (int i = pos; i >= 1; --i) {
        if (l[i] == '9') l[i] = '0';
        else {
            ++l[i];
            break;
        }
    }
}

// Subtract l from 9s
vector<int> sub9(int s, int f) {
    int t = 0;
    vector<int> ans;
    for (int i = f; i >= s; --i) {
        int v = '9' - l[i] - t;
        if (v < 0) { v += 10; t = 1; }
        else t = 0;
        ans.pb(v);
    }
    return ans;
}

// Subtract l from r
vector<int> sub(int s, int f) {
    int t = 0;
    vector<int> ans;
    for (int i = f; i >= s; --i) {
        int v = r[i] - l[i] - t;
        if (v < 0) { v += 10; t = 1; }
        else t = 0;
        ans.pb(v);
    }
    return ans;
}

// Add two vectors of digits
vector<int> add(vector<int>& a, vector<int>& b) {
    while (sz(a) < sz(b)) a.pb(0);
    while (sz(b) < sz(a)) b.pb(0);
    vector<int> c;
    int t = 0;
    for (int i = 0; i < sz(a); ++i) {
        int v = a[i] + b[i] + t;
        c.pb(v % 10);
        t = v / 10;
    }
    if (t > 0) c.pb(t);
    return c;
}

// Print vector of digits
void printVector(vector<int>& a) {
    for (int i = sz(a) - 1; i >= 0; --i) cout << a[i];
}

// Block structure
struct Block {
    int s;
    vector<int> cnt;
    Block() {}
    Block(int _s, vector<int>& _cnt) {
        s = _s;
        cnt = _cnt;
        while (sz(cnt) > 1 && cnt.back() == 0) cnt.pop_back();
    }
};

vector<Block> result;

int main() {
    cout << "Enter the first number (l): ";
    cin >> (l + 1);
    m = strlen(l + 1);

    cout << "Enter the second number (r): ";
    cin >> (r + 1);
    n = strlen(r + 1);

    // Preprocessing l to match length of r
    for (int i = n; i >= n - m + 1; --i) l[i] = l[i - (n - m)];
    for (int i = n - m; i >= 1; --i) l[i] = '0';

    int x = 0;
    while (x <= n && l[x + 1] == r[x + 1]) ++x;
    if (x > n) {
        cout << "1\n0 1\n";
        return 0;
    }

    while (x < n) {
        if (x == n - 1) {
            vector<int> cnt; cnt.pb(r[n] - l[n] + 1);
            result.pb(Block(0, cnt));
            l[n] = r[n];
            break;
        }
        else if (l[n] != '1') {
            vector<int> cnt; cnt.pb(0);
            while (l[n] != '1') {
                plus1(n);
                ++cnt[0];
                while (x < n && l[x + 1] == r[x + 1]) ++x;
                if (x == n) { ++cnt[0]; break; }
            }
            result.pb(Block(0, cnt));
        }
        else {
            int u = n - 1;
            while (u - 1 > x && l[u] == '0') --u;
            int len = n - u;
            int s = 1;
            while ((1 << s) <= len) ++s;
            int leftBound = n - (1 << s);
            int rightBound = n - (1 << (s - 1));
            leftBound = max(leftBound, 0);
            vector<int> cnt;
            if (x < leftBound) cnt = sub9(leftBound + 1, rightBound);
            else cnt = sub(leftBound + 1, rightBound);
            result.pb(Block(s, cnt));
            for (int i = leftBound + 1; i <= rightBound; ++i) l[i] = (x < leftBound ? '0' : r[i]);
            l[n] = '0';
            if (x < leftBound) plus1(leftBound);
            while (x < n && l[x + 1] == r[x + 1]) ++x;
            if (x < n) l[n] = '1';
        }
    }

    cout << sz(result) << "\n";
    for (int i = 0; i < sz(result); ) {
        int j = i;
        vector<int> sum = result[i].cnt;
        while (j + 1 < sz(result) && result[j + 1].s == result[i].s)
            sum = add(sum, result[++j].cnt);
        cout << result[i].s << " ";
        printVector(sum);
        cout << "\n";
        i = j + 1;
    }

    return 0;
}
