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

void print_singly_linked_list(SinglyLinkedListNode* node) {
    while (node) {
        cout << node->data;
        node = node->next;
        if (node) cout << " ";
    }
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
    while (node) {
        SinglyLinkedListNode* temp = node;
        node = node->next;
        delete temp;
    }
}

SinglyLinkedListNode* reverse(SinglyLinkedListNode* head) {
    SinglyLinkedListNode* rHead = NULL;
    while (head != NULL) {
        SinglyLinkedListNode* node = new SinglyLinkedListNode(head->data);
        node->next = rHead;
        rHead = node;
        head = head->next;
    }
    return rHead;
}

int main() {
    int tests;
    cin >> tests;

    while (tests--) {
        int n;
        cin >> n;

        SinglyLinkedList* list = new SinglyLinkedList();

        for (int i = 0; i < n; i++) {
            int value;
            cin >> value;
            list->insert_node(value);
        }

        SinglyLinkedListNode* reversed = reverse(list->head);

        print_singly_linked_list(reversed);
        cout << endl;

        free_singly_linked_list(reversed);
    }

    return 0;
}
