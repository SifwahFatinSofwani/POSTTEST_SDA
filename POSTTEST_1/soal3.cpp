#include <iostream>
#include <limits> 

using namespace std;

struct Mahasiswa {
    string nama;
    int NIM;
    float IPK;
};

int main() {
    Mahasiswa mahasiswa[4];
    int i; 

    cout << "<<--Input data mahasiswa-->>" << endl;
    for (i = 0; i < 4; i++) {
        cout << "\nMasukkan data mahasiswa ke-" << i + 1 << ":" << endl;

        if (i > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Masukkan nama mahasiswa: ";
        getline(cin, mahasiswa[i].nama);

        cout << "Masukkan NIM: ";
        while (!(cin >> mahasiswa[i].NIM)) {
            cout << "Input tidak valid! Harap masukkan NIM dalam bentuk angka.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Masukkan NIM: "; 
        }

        cout << "Masukkan IPK: ";
        while (!(cin >> mahasiswa[i].IPK)) {
            cout << "Input tidak valid! Harap masukkan IPK dalam bentuk angka (misal: 3.75).\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan IPK: "; 
        }
    }

    for (int i = 0; i < 4 - 1; i++) {
        for (int j = 0; j < 4 - i - 1; j++) {
            if (mahasiswa[j].IPK > mahasiswa[j + 1].IPK) {
                Mahasiswa cache = mahasiswa[j];
                mahasiswa[j] = mahasiswa[j + 1];
                mahasiswa[j + 1] = cache;
            }
        }
    }

    cout << "\n<<--Data Mahasiswa (Diurutkan berdasarkan IPK)-->>" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Nama: " << mahasiswa[i].nama << ", NIM: " << mahasiswa[i].NIM << ", IPK: " << mahasiswa[i].IPK << endl;
    }

    return 0;
}