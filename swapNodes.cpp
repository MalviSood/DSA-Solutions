#include <iostream>
#include <vector>
using namespace std;

vector<int> leftNode, rightNode;
int swapLevel;

void traverse(int node = 1) {
    if (node == -1) return;
    traverse(leftNode[node]);
    cout << node << " ";
    traverse(rightNode[node]);
    if (node == 1) cout << endl;
}

void swapNodes(int level = 1, int node = 1) {
    if (node == -1) return;

    if (level % swapLevel == 0) {
        int temp = leftNode[node];
        leftNode[node] = rightNode[node];
        rightNode[node] = temp;
    }

    swapNodes(level + 1, leftNode[node]);
    swapNodes(level + 1, rightNode[node]);
}

int main() {
    int count;

    cout << "Enter number of nodes: ";
    cin >> count;

    leftNode.push_back(0);   // Index 0 dummy
    rightNode.push_back(0);  // Index 0 dummy

    cout << "Enter left and right children (-1 if none):\n";
    for (int i = 1; i <= count; i++) {
        int L, R;
        cout << "Node " << i << ": ";
        cin >> L >> R;
        leftNode.push_back(L);
        rightNode.push_back(R);
    }

    cout << "Enter number of swap operations: ";
    cin >> count;

    while (count--) {
        cout << "Enter swap level K: ";
        cin >> swapLevel;

        swapNodes();
        cout << "Inorder traversal after swap: ";
        traverse();
    }

    return 0;
}
