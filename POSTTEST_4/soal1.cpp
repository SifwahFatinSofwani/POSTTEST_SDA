#include <iostream>
using namespace std;

struct Node { // struktur untuk node stack
    char data;
    Node* next;
};

void push(Node*& top, char data) { // menambahkan elemen ke stack
    Node* newNode = new Node{data, top}; // buat node baru dengan data dan next menunjuk ke node teratas saat ini
    top = newNode; // update top untuk menunjuk ke node baru
}

char pop(Node*& top) {
    if (top == nullptr) return '\0'; // Return null character jika stack kosong
    Node* temp = top; // simpan node teratas dalam variabel sementara
    char poppedValue = temp->data; // ambil data dari node teratas dan simpan dalam variabel poppedValue
    top = top->next; // ambil node berikutnya sebagai node teratas
    delete temp; // hapus node teratas yang lama
    return poppedValue; // kembalikan nilai yang di-pop
}

string reverseString(string s) {
    Node* stackTop = nullptr; // Inisialisasi stack kosong
    string reversed = ""; // String untuk menyimpan hasil terbalik

    for (int i = 0; i < s.length(); i++) {
        push(stackTop, s[i]); // Push setiap karakter dari string ke stack untuk implementasi stack
    }

    while (stackTop != nullptr) {
        reversed += pop(stackTop); // Pop karakter dari stack dan tambahkan ke string hasil
    }

    return reversed; // Kembalikan string yang sudah terbalik
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl; // Output: ataD rutkurtS
    return 0;
}