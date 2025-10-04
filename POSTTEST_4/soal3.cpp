#include <iostream>
#include <string>
using namespace std;

struct Node {
    string document;
    Node* next;
};

void enqueue(Node*& front, Node*& rear, string document) {
    Node* newNode = new Node{document, nullptr}; // buat node baru dengan data dokumen dan next sebagai nullptr

    if (front == nullptr) {
        front = rear = newNode; // jika antrian kosong, front dan rear menunjuk ke node baru
    } 
    
    else {
        rear->next = newNode; // tambahkan node baru di belakang rear
        rear = newNode; // update rear untuk menunjuk ke node baru
    }
}

string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return ""; // return string kosong jika antrian kosong

    Node* temp = front; // simpan node depan dalam variabel sementara
    string docData = temp->document; // ambil data dokumen dari node depan  

    front = front->next; // update front untuk menunjuk ke node berikutnya

    if (front == nullptr) {  // jika antrian menjadi kosong, set rear ke nullptr juga
        rear = nullptr;
    }

    delete temp; // hapus node depan yang lama
    return docData; // kembalikan data dokumen yang di-dequeue
}

void processAllDocuments(Node*& front, Node*& rear) {
    cout << "Memulai pemrosesan antrian printer:" << endl;
    while (front != nullptr) { // selama antrian tidak kosong akan memproses dokumen satu per satu dari depan antrian
        string docToProcess = dequeue(front, rear);
        cout << "Memproses: " << docToProcess << endl;
    }
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;

    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");

    processAllDocuments(front, rear);

    return 0;
}