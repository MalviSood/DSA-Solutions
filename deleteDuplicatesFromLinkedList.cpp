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

void print_list(SinglyLinkedListNode* node) {
    cout << "Linked List after removing duplicates: ";
    while (node) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

SinglyLinkedListNode* removeDuplicates(SinglyLinkedListNode* head) {
    SinglyLinkedListNode* curr = head;

    while (curr != NULL && curr->next != NULL) {
        if (curr->data == curr->next->data) {
            SinglyLinkedListNode* dup = curr->next;
            curr->next = dup->next;
            delete dup;
        } else {
            curr = curr->next;
        }
    }

    return head;
}

int main() {

    SinglyLinkedList* llist = new SinglyLinkedList();

    int n;
    cout << "Enter number of elements in the linked list: ";
    cin >> n;

    cout << "Enter " << n << " elements (sorted): ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        llist->insert_node(val);
    }

    SinglyLinkedListNode* result = removeDuplicates(llist->head);

    print_list(result);

    return 0;
}
