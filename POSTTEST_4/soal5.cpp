#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void exchangeHeadAndTail(Node*& head_ref) {
    if (head_ref == nullptr || head_ref->next == head_ref) {
        return;
    }

    // Dapatkan pointer ke node-node penting
    Node* head = head_ref;
    Node* tail = head->prev;
    Node* head_next = head->next;
    Node* tail_prev = tail->prev;

    // Kondisi khusus jika hanya ada dua node
    if (head_next == tail) {
        head_ref = tail;
        return;
    }
    
    // Sambungkan tail (head baru) dengan head lama
    tail->next = head_next;
    head_next->prev = tail;

    // Sambungkan head (tail baru) dengan tail lama
    head->prev = tail_prev;
    tail_prev->next = head;

    // Tutup lingkaran baru antara head dan tail
    head->next = tail;
    tail->prev = head;

    // Update head_ref menjadi tail yang lama
    head_ref = tail;
}

void printList(Node* head_ref) { // fungsi untuk mencetak isi list
    if (head_ref == nullptr) {
        cout << "List kosong" << endl;
        return;
    }
    Node* current = head_ref;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

void insertEnd(Node*& head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr}; // buat node baru dengan data
    if (head_ref == nullptr) { // jika list kosong maka node baru menjadi head
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }
    Node* tail = head_ref->prev; // kode untuk memasukkan node di akhir
    newNode->next = head_ref;
    newNode->prev = tail;
    head_ref->prev = newNode;
    tail->next = newNode;
}

int main() {
    Node* head = nullptr;

    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    printList(head);

    return 0;
}