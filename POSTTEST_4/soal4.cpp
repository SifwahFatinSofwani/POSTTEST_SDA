#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void sortedInsert(Node*& head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr}; // buat node baru dengan data

    if (head_ref == nullptr) { // jika list kosong maka node baru menjadi head
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    Node* tail = head_ref->prev; // dapatkan pointer ke tail (node sebelum head)

    if (data <= head_ref->data) { // Sisipkan di awal jika data lebih kecil atau sama dengan head
        newNode->next = head_ref;
        newNode->prev = tail;
        tail->next = newNode;
        head_ref->prev = newNode;
        head_ref = newNode;
        return;
    }

    if (data >= tail->data) { // Sisipkan di akhir (Optimasi) jika data lebih besar atau sama dengan tail
        newNode->next = head_ref;
        newNode->prev = tail;
        tail->next = newNode;
        head_ref->prev = newNode;
        return;
    }
    
    // Sisipkan di tengah
    Node* current = head_ref;
    while (current->next->data < data) {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
}

void printList(Node* head_ref) {
    if (head_ref == nullptr) { // jika list kosong maka akan ada output list kosong
        cout << "List kosong" << endl;
        return;
    }
    Node* current = head_ref; // jika tidak maka akan mencetak seluruh isi list
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref); // handling agar tidak terjadi infinite loop
    cout << endl;
}

int main() {
    Node* head = nullptr;

    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 40);
    sortedInsert(head, 20);

    cout << "Circular Doubly Linked List (sorted): ";
    printList(head);

    return 0;
}