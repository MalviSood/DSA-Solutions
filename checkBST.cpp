#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to check BST using allowed range technique
bool checkBST(Node* root, int minValue, int maxValue) {
    if (root == NULL) return true;

    if (root->data < minValue || root->data > maxValue)
        return false;

    return checkBST(root->left, minValue, root->data - 1) &&
           checkBST(root->right, root->data + 1, maxValue);
}

bool checkBST(Node* root) {
    return checkBST(root, 0, 10000);
}

// Utility function to insert nodes level-wise for testing
Node* buildTree(vector<pair<int,int>>& nodes) {
    // nodes[i] = {leftChild, rightChild}
    vector<Node*> arr(nodes.size() + 1, NULL);

    // Create root
    arr[1] = new Node(1);

    // Create remaining nodes
    for (int i = 2; i <= (int)nodes.size(); i++)
        arr[i] = new Node(i);

    // Connect children
    for (int i = 1; i <= (int)nodes.size(); i++) {
        if (nodes[i-1].first != -1)
            arr[i]->left = arr[nodes[i-1].first];
        if (nodes[i-1].second != -1)
            arr[i]->right = arr[nodes[i-1].second];
    }

    return arr[1];
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<pair<int,int>> nodes;
    cout << "Enter left and right child index (-1 for NULL):\n";
    for (int i = 0; i < n; i++) {
        int L, R;
        cin >> L >> R;
        nodes.push_back({L, R});
    }

    Node* root = buildTree(nodes);

    if (checkBST(root))
        cout << "YES, it is a BST\n";
    else
        cout << "NO, it is NOT a BST\n";

    return 0;
}

