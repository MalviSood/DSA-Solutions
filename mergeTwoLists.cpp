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
    cout << "Merged Linked List: ";
    while (node) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    if(!head1) return head2;
    if(!head2) return head1;

    SinglyLinkedListNode *p1 = head1, *p2 = head2, *h, *p;

    if(p1->data < p2->data) {
        h = p1;
        p1 = p1->next;
    } else {
        h = p2;
        p2 = p2->next;
    }

    p = h;

    while(p1 != NULL || p2 != NULL) {
        if(!p2 || (p1 && p1->data < p2->data)) {
            p->next = p1;
            p1 = p1->next;
        } else {
            p->next = p2;
            p2 = p2->next;
        }
        p = p->next;
    }

    return h;
}

int main() {
    SinglyLinkedList *llist1 = new SinglyLinkedList();
    SinglyLinkedList *llist2 = new SinglyLinkedList();

    int n1, n2;

    cout << "Enter number of elements in List 1: ";
    cin >> n1;

    cout << "Enter " << n1 << " sorted elements for List 1: ";
    for(int i = 0; i < n1; i++) {
        int x;
        cin >> x;
        llist1->insert_node(x);
    }

    cout << "Enter number of elements in List 2: ";
    cin >> n2;

    cout << "Enter " << n2 << " sorted elements for List 2: ";
    for(int i = 0; i < n2; i++) {
        int x;
        cin >> x;
        llist2->insert_node(x);
    }

    SinglyLinkedListNode* merged = mergeLists(llist1->head, llist2->head);

    print_list(merged);

    return 0;
}
