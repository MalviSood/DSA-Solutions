#include <bits/stdc++.h>
using namespace std;

struct node {
    int freq;
    char data;
    node* left;
    node* right;
};

// Comparator for priority queue
struct deref {
    bool operator()(const node* a, const node* b) const {
        return a->freq > b->freq;
    }
};

// Build Huffman tree from string
node* buildHuffmanTree(const string& s) {
    vector<int> count(256, 0);
    for (char c : s) count[c]++;

    priority_queue<node*, vector<node*>, deref> pq;

    for (int i = 0; i < 256; i++) {
        if (count[i] == 0) continue;
        node* n = new node{count[i], (char)i, nullptr, nullptr};
        pq.push(n);
    }

    while (pq.size() > 1) {
        node* left = pq.top(); pq.pop();
        node* right = pq.top(); pq.pop();

        node* parent = new node{left->freq + right->freq, '\0', left, right};
        pq.push(parent);
    }

    return pq.top();
}

// Generate codes for each character
void generateCodes(node* root, string code, map<char, string>& mp) {
    if (!root) return;
    if (root->data != '\0') mp[root->data] = code;
    generateCodes(root->left, code + '0', mp);
    generateCodes(root->right, code + '1', mp);
}

// Decode Huffman string
string decodeHuffman(node* root, const string& encoded) {
    string ans = "";
    node* n = root;
    for (char bit : encoded) {
        n = (bit == '0') ? n->left : n->right;
        if (n->data != '\0') {
            ans += n->data;
            n = root;
        }
    }
    return ans;
}

int main() {
    string s;
    cout << "Enter string to encode: ";
    cin >> s;

    // Build Huffman tree
    node* root = buildHuffmanTree(s);

    // Generate codes
    map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "Huffman Codes for each character:\n";
    for (auto& p : codes) {
        cout << p.first << " : " << p.second << endl;
    }

    // Encode
    string encoded = "";
    for (char c : s) encoded += codes[c];
    cout << "Encoded string: " << encoded << endl;

    // Decode
    string decoded = decodeHuffman(root, encoded);
    cout << "Decoded string: " << decoded << endl;

    return 0;
}
