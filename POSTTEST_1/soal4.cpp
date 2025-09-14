#include <iostream>
#include <limits>

using namespace std;

void tukar(int& var1, int& var2) {
    int temp = var2;
    var2 = var1;
    var1 = temp;
}

int main(){
    int var1, var2;

    cout << "Masukkan nilai pertama: ";
    
    while(true) {
        cin >> var1;
        if (cin.fail()) { 
            cout << "Input tidak valid. Harap masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break; 
        }
    }

    cout << "Masukkan nilai kedua: ";
    while(true) {
        cin >> var2;
        if (cin.fail()) { 
            cout << "Input tidak valid. Harap masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    
    cout << endl;

    cout << "Variable sebelum ditukar" << endl;
    cout << "Variable 1: " << var1 << endl;
    cout << "Variable 2: " << var2 << endl << endl;

    tukar(var1, var2);

    cout << "Variable sesudah ditukar" << endl;
    cout << "Variable 1: " << var1 << endl;
    cout << "Variable 2: " << var2 << endl;
    
    return 0;
}