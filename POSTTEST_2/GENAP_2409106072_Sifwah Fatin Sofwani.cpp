#include <iostream>
#include <iomanip>
#include <limits>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

int jumlahJadwal = 0; int posisi; int pilihan;


struct Jadwal {
    string kodepenerbangan;
    string bandaratujuan;
    string bandarasal;
    string tanggalkeberangkatan;
    string waktukeberangkatan;
    string tanggalkedatangan;
    string waktukedatangan;
    string statuspenerbangan;
};

struct Node {
    Jadwal data;
    Node* next;
};

void tampilkanMenu();
void menuTambah(Node*& head, int& jumlahJadwal);
void tambahJadwalAwal(Node*& head, int& jumlahJadwal);
void tambahJadwalAkhir(Node*& head, int& jumlahJadwal);
void tambahJadwalPosisi(Node*& head, int& jumlahJadwal);
void sisipkanJadwal(Node*& head, int posisi, int& jumlahJadwal);
void hapusJadwalAwal(Node*& head, int& jumlahJadwal);
void updateStatusPenerbangan(Node* head);
void tampilkanSemuaJadwal(Node* head);
void clearScreen();
Node* inputDataJadwal(int& jumlahJadwal);
string inputHandling(string& output);

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string inputHandling(const string& output) {
    string input;
    while (true) {
        cout << output;
        getline(cin, input);
        if (!input.empty()) {
            return input;
        }
        cout << "Input tidak boleh kosong! Silakan coba lagi." << endl;
    }
}

Node* inputDataJadwal(int& jumlahJadwal) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node* newNode = new Node;

    if (jumlahJadwal == 0) {
        newNode->data.kodepenerbangan = "JT-072";
    } else {
        newNode->data.kodepenerbangan = "JT-072-" + to_string(jumlahJadwal);
    }

    cout << "\n--- Tambah Data Jadwal Baru ---" << endl;
    cout << "Kode Penerbangan Otomatis: " << newNode->data.kodepenerbangan << endl;
    
    newNode->data.bandarasal = inputHandling("Bandara Asal: ");
    newNode->data.bandaratujuan = inputHandling("Bandara Tujuan: ");
    newNode->data.tanggalkeberangkatan = inputHandling("Tanggal Keberangkatan (DD-MM-YYYY): ");
    newNode->data.waktukeberangkatan = inputHandling("Waktu Keberangkatan (HH:MM): ");
    newNode->data.tanggalkedatangan = inputHandling("Tanggal Kedatangan (DD-MM-YYYY): ");
    newNode->data.waktukedatangan = inputHandling("Waktu Kedatangan (HH:MM): ");
    newNode->data.statuspenerbangan = inputHandling("Status Penerbangan (On Time, Delayed): ");
    
    jumlahJadwal++;
    newNode->next = nullptr;
    return newNode;
}

// MODIFIED: Disesuaikan untuk menampilkan semua data baru
void tampilkanSemuaJadwal(Node* head) {
    clearScreen();
    cout << "--- Menampilkan Semua Jadwal Penerbangan ---" << endl;
    if (head == nullptr) {
        cout << "\nBelum ada jadwal penerbangan yang terdaftar" << endl;
    } else {
        Table tabelJadwal;
        tabelJadwal.add_row({"No", "Kode", "Asal", "Tujuan", "Berangkat", "Tiba", "Status"});
        
        tabelJadwal[0].format().font_align(FontAlign::center).font_style({FontStyle::bold}).font_color(Color::yellow);

        Node* current = head;
        int i = 1;
        while (current != nullptr) {
            string berangkat = current->data.tanggalkeberangkatan + " " + current->data.waktukeberangkatan;
            string tiba = current->data.tanggalkedatangan + " " + current->data.waktukedatangan;

            tabelJadwal.add_row({
                to_string(i),
                current->data.kodepenerbangan,
                current->data.bandarasal,
                current->data.bandaratujuan,
                berangkat,
                tiba,
                current->data.statuspenerbangan
            });
            current = current->next;
            i++;
        }
        
        for (i = 1; i < tabelJadwal.size(); ++i) {
            tabelJadwal[i].format().font_align(FontAlign::center);
        }
        cout << "\n" << tabelJadwal << endl;
    }
}

void tambahJadwalAwal(Node*& head, int& jumlahJadwal) {
    Node* nodeBaru = inputDataJadwal(jumlahJadwal);
    nodeBaru->next = head;
    head = nodeBaru;   
    cout << "\nJadwal berhasil ditambahkan di awal!" << endl;
}

void tambahJadwalAkhir(Node*& head, int& jumlahJadwal) {
    if (head == nullptr) {
        tambahJadwalAwal(head, jumlahJadwal);
    } else {
        Node* nodeBaru = inputDataJadwal(jumlahJadwal);
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }
    cout << "\nJadwal berhasil ditambahkan di akhir!" << endl;
}

void tambahJadwalPosisi(Node*& head, int& jumlahJadwal) {

    
    if (head == nullptr) {
        cout << "Urutan ke (hanya 1): ";
    } else {
        tampilkanSemuaJadwal(head);
        cout << "Masukkan posisi (1-" << jumlahJadwal + 1 << "): ";
    }
    
    cin >> posisi;
    
    if (cin.fail() || posisi <= 0 || posisi > jumlahJadwal + 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Posisi tidak valid!" << endl;
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (posisi == 1) {
        tambahJadwalAwal(head, jumlahJadwal);
        return;
    } 

    else if (posisi == jumlahJadwal + 1) {
        tambahJadwalAkhir(head, jumlahJadwal);
        return; 
    }

    Node* nodeBaru = inputDataJadwal(jumlahJadwal);
    Node* temp = head;
    
    for (int i = 1; i < posisi - 1; i++) {
        temp = temp->next;
    }
    
    nodeBaru->next = temp->next;
    temp->next = nodeBaru;

    cout << "\nJadwal berhasil disisipkan di posisi " << posisi << "." << endl;
}

void sisipkanJadwal(Node*& head, int& jumlahJadwal) {
    if (jumlahJadwal < 2) {
        cout << "\nData masih terlalu sedikit untuk disisipkan!" << endl;
        return;
    }

    Node* temp = head;
    for (int i = 1; i < 3 - 1; i++) {
        temp = temp->next;
    }
    Node* nodeBaru = inputDataJadwal(jumlahJadwal);
    nodeBaru->next = temp->next;
    temp->next = nodeBaru;
    cout << "\nJadwal berhasil disisipkan di posisi NIM yaitu 3" << endl;
}

void menuTambah(Node*& head, int& jumlahJadwal) {
    Table subMenuTambah;
    subMenuTambah.add_row({"--- Menu Tambah Jadwal ---"});
    subMenuTambah.add_row({"1. Tambah di Awal"});
    subMenuTambah.add_row({"2. Tambah di Akhir"});
    subMenuTambah.add_row({"3. Tambah di Posisi Tertentu"});
    subMenuTambah.add_row({"0. Kembali ke Menu Utama"});
    
    subMenuTambah[0].format().font_style({FontStyle::bold}).font_align(FontAlign::center);
    
    clearScreen();
    cout << subMenuTambah << endl;
    cout << "Pilihan Anda: ";

    int pilihan;
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            tambahJadwalAwal(head, jumlahJadwal);
            break;
        case 2:
            tambahJadwalAkhir(head, jumlahJadwal);
            break;
        case 3:
            tambahJadwalPosisi(head, jumlahJadwal);
            break;
        case 0:
            cout << "Kembali ke menu utama..." << endl;
            break;
        default:
            break;
    }
}

void tampilkanMenu() {
    Table menu;
    menu.add_row({"FLIGHT SCHEDULE SYSTEM"});
    menu.add_row({"1. Buka Menu Tambah Jadwal"});
    menu.add_row({"2. Sisipkan Jadwal (Sesuai NIM)"});
    menu.add_row({"3. Hapus Jadwal Paling Awal"});
    menu.add_row({"4. Update Status Penerbangan"});
    menu.add_row({"5. Tampilkan Semua Jadwal"});
    menu.add_row({"0. Keluar"});

    menu[0].format().font_align(FontAlign::center).font_style({FontStyle::bold}).font_color(Color::cyan).padding_top(1).padding_bottom(1);
    for (int i = 1; i < menu.size(); ++i) {
        menu[i].format().font_align(FontAlign::left);
    }
    cout << menu << endl;
    cout << "===================================" << endl;
    cout << "Pilih menu: ";
}

void hapusJadwalAwal(Node*& head, int& jumlahJadwal) {
    if (head == nullptr) {
        cout << "\nTidak ada jadwal untuk dihapus." << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    cout << "\nJadwal dengan kode '" << temp->data.kodepenerbangan << "' berhasil dihapus." << endl;
    delete temp;
    jumlahJadwal--;
}

void tampilkanMenuEdit(Node* head) {
    Table menuEdit;
    menuEdit.add_row({"Jadwal ditemukan pilih data yang ingin diubah:"});
    menuEdit.add_row({"1. Tanggal Keberangkatan"});
    menuEdit.add_row({"2. Waktu Keberangkatan"});
    menuEdit.add_row({"3. Tanggal Kedatangan"});
    menuEdit.add_row({"4. Waktu Kedatangan"});
    menuEdit.add_row({"5. Status Penerbangan"});
    menuEdit.add_row({"0. Keluar"});

    menuEdit[0].format().font_align(FontAlign::center).font_style({FontStyle::bold}).font_color(Color::yellow);
    for (int i = 1; i < menuEdit.size(); ++i) {
            menuEdit[i].format().font_align(FontAlign::center);
        }
    cout << "\n" << menuEdit << endl;

}

void updateStatusPenerbangan(Node* head) {
    if (head == nullptr) {
        cout << "\nBelum ada jadwal yang terdaftar." << endl;
        return;
    }
    tampilkanSemuaJadwal(head);
    string kodeCari;
    cout << "\nMasukkan Kode Penerbangan yang akan di-update: ";
    getline(cin, kodeCari);

    Node* current = head;
    bool ditemukan = false;
    while (current != nullptr) {
        if (current->data.kodepenerbangan == kodeCari) {
            ditemukan = true;
            cout << "Jadwal ditemukan! Status saat ini: " << current->data.statuspenerbangan << endl;
            
            while(true) { 
                clearScreen();
                tampilkanMenuEdit(current);
                cout << "Pilihan Anda: ";
                
                cin >> pilihan;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pilihan == 0) {
                    cout << "Selesai mengubah data." << endl;
                    break; 
                }

                switch (pilihan) {
                    case 1:
                        current->data.tanggalkeberangkatan = inputHandling("Masukkan Tanggal Keberangkatan baru: ");
                        break;
                    case 2:
                        current->data.waktukeberangkatan = inputHandling("Masukkan Waktu Keberangkatan baru: ");
                        break;
                    case 3:
                        current->data.tanggalkedatangan = inputHandling("Masukkan Tanggal Kedatangan baru: ");
                        break;
                    case 4:
                        current->data.waktukedatangan = inputHandling("Masukkan Waktu Kedatangan baru: ");
                        break;
                    case 5:
                        current->data.statuspenerbangan = inputHandling("Masukkan Status Penerbangan baru: ");
                        break;
                    default:
                        cout << "Pilihan tidak valid." << endl;
                        system("pause");
                        continue; 
                }
                cout << "Data berhasil diperbarui!" << endl;
                system("pause");

            }
            break;
        }
        current = current->next;
    }
    if (!ditemukan) {
        cout << "\nJadwal dengan kode '" << kodeCari << "' tidak ditemukan." << endl;
    }
}

int main() {
    Node* headJadwal = nullptr;
    while (true) { 
        clearScreen();
        tampilkanMenu();
        
        cin >> pilihan;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1; 
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        switch (pilihan) {
            case 1:
                menuTambah(headJadwal, jumlahJadwal);
                break;
            case 2:
                sisipkanJadwal(headJadwal, jumlahJadwal);
                break;
            case 3:
                hapusJadwalAwal(headJadwal, jumlahJadwal);
                break;
            case 4:
                updateStatusPenerbangan(headJadwal);
                break;
            case 5:
                tampilkanSemuaJadwal(headJadwal);
                break;
            case 0:
                return 0; 
            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }

        cout << "\nTekan Enter untuk kembali ke menu...";
        cin.get();
    }
}

