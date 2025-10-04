#include <iostream>
#include <string>
using namespace std;

struct Node { // struktur untuk node stack
    char data;
    Node* next;
};

void push(Node*& top, char data) {
    Node* newNode = new Node{data, top}; // buat node baru dengan data dan next menunjuk ke node teratas saat ini
    top = newNode; // update top untuk menunjuk ke node baru
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top; // simpan node teratas dalam variabel sementara
    char poppedValue = temp->data; // ambil data dari node teratas dan simpan dalam variabel poppedValue
    top = top->next; // ambil node berikutnya sebagai node teratas
    delete temp; // hapus node teratas yang lama
    return poppedValue; // kembalikan nilai yang di-pop
}

bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr; // Inisialisasi stack kosong

    for (char c : expr) {  // iterasi setiap karakter dalam string expr
        if (c == '(' || c == '{' || c == '[') {
            push(stackTop, c); // push karakter pembuka ke stack   
            }

        else if (c == ')' || c == '}' || c == ']') { // jika karakter adalah penutup
            if (stackTop == nullptr) {
                return false; // jika stack kosong, berarti tidak seimbang
            }

            char topChar = pop(stackTop);
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '[')) {
                return false; // jika karakter penutup tidak cocok dengan karakter pembuka
            }
        }
    }

    return stackTop == nullptr; // jika stack kosong, berarti semua pembuka memiliki penutup yang sesuai

}

int main() {
    string expr1 = "{[()]}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;

    string expr2 = "{[(])}";
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;

    return 0;
}