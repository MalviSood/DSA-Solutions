#include <bits/stdc++.h>
using namespace std;

class SinglyLinkedListNode {
public:
    int data;
    SinglyLinkedListNode *next;

    SinglyLinkedListNode(int node_data) {
        data = node_data;
        next = nullptr;
    }
};

class SinglyLinkedList {
public:
    SinglyLinkedListNode *head;
    SinglyLinkedListNode *tail;

    SinglyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void insert_node(int node_data) {
        SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

        if (!head) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
};

bool has_cycle(SinglyLinkedListNode* head) {
    SinglyLinkedListNode* s = head;   // slow
    SinglyLinkedListNode* f = head;   // fast

    while (f && f->next) {
        s = s->next;
        f = f->next->next;

        if (s == f) return true;
    }
    return false;
}

int main() {
    SinglyLinkedList* llist = new SinglyLinkedList();

    int n;
    cout << "Enter number of nodes in the linked list: ";
    cin >> n;

    cout << "Enter " << n << " node values: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        llist->insert_node(val);
    }

    int index;
    cout << "Enter index to create cycle (-1 for no cycle): ";
    cin >> index;

    SinglyLinkedListNode* temp = llist->head;
    SinglyLinkedListNode* cycleNode = nullptr;

    for (int i = 0; i < n; i++) {
        if (i == index) cycleNode = temp;
        if (i != n - 1) temp = temp->next;
    }

    if (index != -1)
        temp->next = cycleNode;  // create cycle

    bool result = has_cycle(llist->head);

    cout << "Cycle present? " << (result ? "Yes" : "No") << endl;

    return 0;
}
