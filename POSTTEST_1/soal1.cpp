#include <iostream>
#include <limits>

using namespace std;

int i, sizeangka, cache;
int angka[7];

void balikArray(int *arr, int size) {
    int *ptr_awal = arr; 
    int *ptr_akhir = arr + size - 1; 

    while (ptr_awal < ptr_akhir) {
        cache = *ptr_awal;
        *ptr_awal = *ptr_akhir;
        *ptr_akhir = cache;


        ptr_awal++;
        ptr_akhir--;
    }
}

int main() {
    

    cout << "Masukkan 7 angka yang anda inginkan: " << endl;

    sizeangka = (sizeof(angka) / sizeof(angka[0]));
    
    for (i = 0; i < sizeangka; i++) {
        cout << "Masukkan angka ke " << i + 1 << ": ";
        cin >> angka[i];

        if (cin.fail()) {
            cout << "\nInput tidak valid! Mohon masukkan hanya angka.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--; 
        }
    }
    
    cout << "\nArray sebelum dibalik: " << endl;
    for (i = 0; i < sizeangka; i++) {
        cout << angka[i] << " | ";
    }

    balikArray(angka, sizeangka);
    
    cout << endl << endl;
    cout << "Array setelah dibalik: " << endl;
    for (i = 0; i < sizeangka; i++) {
        cout << angka[i] << " | ";
    }
    cout << endl;

    return 0;
}