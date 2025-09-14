#include <iostream>
#include <limits>

using namespace std;

int main() {
    int i, j, sum = 0;
    int array[3][3];

    cout << "Masukkan angka untuk matriks 3x3:" << endl;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            
            cout << "Masukkan angka untuk baris ke-" << i + 1 << ", kolom ke-" << j + 1 << ": ";

            while (!(cin >> array[i][j])) {
                cout << "\nInput tidak valid! Mohon masukkan hanya angka.\n";
                
                cin.clear();
            
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Masukkan angka untuk baris ke-" << i + 1 << ", kolom ke-" << j + 1 << ": ";
            }
        }
    }

    cout << endl;
    cout << "Matrix: " << endl;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            cout << array[i][j] << " | ";
        }
        cout << endl;
    }

    for (j = 0; j < 3; j++) {
        sum += array[1][j];
    }

    cout << endl;
    cout << "Baris yang dihitung: " << endl;
    for (j = 0; j < 3; j++) {
        cout << array[1][j] << " | ";
    }

    cout << endl << endl;
    cout << "Hasil penjumlahan baris ke-2 adalah " << sum << endl;
    
    return 0;
}