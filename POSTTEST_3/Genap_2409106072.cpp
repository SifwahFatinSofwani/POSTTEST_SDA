#include <iostream>
#include <limits>
#include <string>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

int jumlahJadwal = 0;
int posisi;
int pilihan;
int idCounter = 0;

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
    Node* prev;
};

void tampilkanMenu();
void menuTambah(Node*& head, Node*& tail, int& jumlahJadwal);
void menuHapus(Node*& head, Node*& tail, int& jumlahJadwal);
void tambahJadwalAwal(Node*& head, Node*& tail, int& jumlahJadwal);
void tambahJadwalAkhir(Node*& head, Node*& tail, int& jumlahJadwal);
void tambahJadwalPosisi(Node*& head, Node*& tail, int& jumlahJadwal);
void sisipkanJadwal(Node*& head, Node*& tail, int& jumlahJadwal);
void hapusJadwalAwal(Node*& head, Node*& tail, int& jumlahJadwal);
void hapusJadwalAkhir(Node*& head, Node*& tail, int& jumlahJadwal);
void hapusJadwalPosisi(Node*& head, Node*& tail, int& jumlahJadwal);
void updateStatusPenerbangan(Node* head);
void tampilkanSemuaJadwal(Node* head);
void tampilkanJadwalId(Node* head);
void hapusSemuaJadwal(Node*& head, Node*& tail);
void clearScreen();
Node* inputDataJadwal();
string inputHandling(const string& output);
void tampilkanJadwalDariBelakang(Node* tail, int jumlahJadwal);
void cariDanTampilkanDetail(Node* head);

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

Node* inputDataJadwal() {
    Node* newNode = new Node;
    if (idCounter == 0) {
        newNode->data.kodepenerbangan = "JT-072";
    } else {
        newNode->data.kodepenerbangan = "JT-072-" + to_string(idCounter);
    }
    idCounter++;

    cout << "\n--- Tambah Data Jadwal Baru ---" << endl;
    cout << "Kode Penerbangan Otomatis: " << newNode->data.kodepenerbangan << endl;
    newNode->data.bandarasal = inputHandling("Bandara Asal: ");
    newNode->data.bandaratujuan = inputHandling("Bandara Tujuan: ");
    newNode->data.tanggalkeberangkatan = inputHandling("Tanggal Keberangkatan (DD-MM-YYYY): ");
    newNode->data.waktukeberangkatan = inputHandling("Waktu Keberangkatan (HH:MM): ");
    newNode->data.tanggalkedatangan = inputHandling("Tanggal Kedatangan (DD-MM-YYYY): ");
    newNode->data.waktukedatangan = inputHandling("Waktu Kedatangan (HH:MM): ");
    newNode->data.statuspenerbangan = inputHandling("Status Penerbangan (On Time, Delayed): ");
    
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

void tampilkanSemuaJadwal(Node* head) {
    clearScreen();
    cout << "--- Menampilkan Semua Jadwal Penerbangan (Dari Depan) ---" << endl;
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
            tabelJadwal.add_row({to_string(i++), current->data.kodepenerbangan, current->data.bandarasal, current->data.bandaratujuan, berangkat, tiba, current->data.statuspenerbangan});
            current = current->next;
        }
        
        for (int i = 1; i < tabelJadwal.size(); ++i) {
            tabelJadwal[i].format().font_align(FontAlign::center);
        }
        cout << "\n" << tabelJadwal << endl;
    }
}

void tampilkanJadwalId(Node* head) {
    clearScreen();
    cout << "--- Menampilkan Semua ID Jadwal Penerbangan (Dari Depan) ---" << endl;
    if (head == nullptr) {
        cout << "\nBelum ada jadwal penerbangan yang terdaftar" << endl;
    } else {
        Table tabelJadwal;
        tabelJadwal.add_row({"No", "Kode"});
        tabelJadwal[0].format().font_align(FontAlign::center).font_style({FontStyle::bold}).font_color(Color::yellow);

        Node* current = head;
        int i = 1;
        while (current != nullptr) {
            tabelJadwal.add_row({to_string(i++), current->data.kodepenerbangan});
            current = current->next;
        }
        
        for (int i = 1; i < tabelJadwal.size(); ++i) {
            tabelJadwal[i].format().font_align(FontAlign::center);
        }
        cout << "\n" << tabelJadwal << endl;
    }
}

void tambahJadwalAwal(Node*& head, Node*& tail, int& jumlahJadwal) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node* nodeBaru = inputDataJadwal();
    nodeBaru->next = head;
    if (head != nullptr) {
        head->prev = nodeBaru;
    } else {
        tail = nodeBaru;
    }
    head = nodeBaru;
    jumlahJadwal++;
    cout << "\nJadwal berhasil ditambahkan di awal!" << endl;
    system("pause");
}

void tambahJadwalAkhir(Node*& head, Node*& tail, int& jumlahJadwal) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (head == nullptr) {
        tambahJadwalAwal(head, tail, jumlahJadwal);
    } else {
        Node* nodeBaru = inputDataJadwal();
        tail->next = nodeBaru;
        nodeBaru->prev = tail;
        tail = nodeBaru;
        jumlahJadwal++;
        cout << "\nJadwal berhasil ditambahkan di akhir!" << endl;
        system("pause");
    }
}

void tambahJadwalPosisi(Node*& head, Node*& tail, int& jumlahJadwal) {
    if (head == nullptr) {
        tambahJadwalAwal(head, tail, jumlahJadwal);
        return;
    }

    tampilkanSemuaJadwal(head);
    cout << "Masukkan posisi (1-" << jumlahJadwal + 1 << "): ";
    cin >> posisi;
    
    if (cin.fail() || posisi <= 0 || posisi > jumlahJadwal + 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Posisi tidak valid!" << endl;
        system("pause");
        return;
    }

    if (posisi == 1) {
        tambahJadwalAwal(head, tail, jumlahJadwal);
    } else if (posisi == jumlahJadwal + 1) {
        tambahJadwalAkhir(head, tail, jumlahJadwal);
    } else {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Node* nodeBaru = inputDataJadwal();
        Node* temp = head;
        for (int i = 1; i < posisi - 1; i++) {
            temp = temp->next;
        }
        nodeBaru->next = temp->next;
        temp->next->prev = nodeBaru;
        temp->next = nodeBaru;
        nodeBaru->prev = temp;
        jumlahJadwal++;
        cout << "\nJadwal berhasil disisipkan di posisi " << posisi << "." << endl;
        system("pause");
    }
}

void sisipkanJadwal(Node*& head, Node*& tail, int& jumlahJadwal) {
    if (jumlahJadwal < 2) {
        cout << "\nData masih terlalu sedikit untuk disisipkan!" << endl;
        system("pause");
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Node* nodeBaru = inputDataJadwal();
    Node* temp = head->next; 

    nodeBaru->next = temp->next;
    nodeBaru->prev = temp;

    if (temp->next != nullptr) {
        temp->next->prev = nodeBaru;
    } else {
        tail = nodeBaru;
    }
    temp->next = nodeBaru;
    
    jumlahJadwal++;
    cout << "\nJadwal berhasil disisipkan di posisi NIM yaitu 3" << endl;
    system("pause");
}

void menuTambah(Node*& head, Node*& tail, int& jumlahJadwal) {
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
    cin >> pilihan;

    switch (pilihan) {
        case 1: 
            tambahJadwalAwal(head, tail, jumlahJadwal); 
            break;
        case 2: 
            tambahJadwalAkhir(head, tail, jumlahJadwal); 
            break;
        case 3: 
            tambahJadwalPosisi(head, tail, jumlahJadwal); 
            break;
        case 0: 
            break;
        default: 
            break;
    }
}

void hapusJadwalAwal(Node*& head, Node*& tail, int& jumlahJadwal) {
    if (head == nullptr) {
        cout << "\nTidak ada jadwal untuk dihapus." << endl;
        system("pause");
        return;
    }
    
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    
    cout << "\nJadwal dengan kode '" << temp->data.kodepenerbangan << "' berhasil dihapus." << endl;
    delete temp;
    jumlahJadwal--;
    system("pause");
}

void hapusJadwalAkhir(Node*& head, Node*& tail, int& jumlahJadwal) {
    if (head == nullptr) {
        cout << "\nTidak ada jadwal untuk dihapus." << endl;
        system("pause");
        return;
    }

    if (head->next == nullptr) {
        hapusJadwalAwal(head, tail, jumlahJadwal);
        return;
    }

    Node* nodeDihapus = tail;
    tail = tail->prev;
    tail->next = nullptr;
    
    cout << "\nJadwal dengan kode '" << nodeDihapus->data.kodepenerbangan << "' berhasil dihapus." << endl;
    delete nodeDihapus;
    jumlahJadwal--;
    system("pause");
}

void hapusJadwalPosisi(Node*& head, Node*& tail, int& jumlahJadwal) {
    if (head == nullptr) {
        cout << "\nTidak ada jadwal untuk dihapus." << endl;
        system("pause");
        return;
    }

    tampilkanSemuaJadwal(head);
    cout << "Masukkan posisi yang akan dihapus (1-" << jumlahJadwal << "): ";
    cin >> posisi;

    if (cin.fail() || posisi <= 0 || posisi > jumlahJadwal) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Posisi tidak valid!" << endl;
        system("pause");
        return;
    }

    if (posisi == 1) {
        hapusJadwalAwal(head, tail, jumlahJadwal);
    } else if (posisi == jumlahJadwal) {
        hapusJadwalAkhir(head, tail, jumlahJadwal);
    } else {
        Node* temp = head;
        for (int i = 1; i < posisi; i++) {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        cout << "\nJadwal dengan kode '" << temp->data.kodepenerbangan << "' berhasil dihapus." << endl;
        delete temp;
        jumlahJadwal--;
        system("pause");
    }
}

void menuHapus(Node*& head, Node*& tail, int& jumlahJadwal) {
    Table subMenuHapus;
    subMenuHapus.add_row({"--- Menu Hapus Jadwal ---"});
    subMenuHapus.add_row({"1. Hapus di Awal"});
    subMenuHapus.add_row({"2. Hapus di Akhir"});
    subMenuHapus.add_row({"3. Hapus di Posisi Tertentu"});
    subMenuHapus.add_row({"0. Kembali ke Menu Utama"});
    subMenuHapus[0].format().font_style({FontStyle::bold}).font_align(FontAlign::center);

    clearScreen();
    if (head == nullptr) {
        cout << "\nTidak ada jadwal untuk dihapus." << endl;
        system("pause");
        return;
    }
    cout << subMenuHapus << endl;
    cout << "Pilihan Anda: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1: 
            hapusJadwalAwal(head, tail, jumlahJadwal); 
            break;
        case 2: 
            hapusJadwalAkhir(head, tail, jumlahJadwal); 
            break;
        case 3: 
            hapusJadwalPosisi(head, tail, jumlahJadwal); 
            break;
        case 0: 
            break;
        default: 
            break;
    }
}

void tampilkanMenu() {
    Table menu;
    menu.add_row({"NAMA : Sifwah Fatin Sofwani"});
    menu.add_row({"NIM  : 2409106072"});   
    menu.add_row({"FLIGHT SCHEDULE SYSTEM"});
    menu.add_row({"1. Buka Menu Tambah Jadwal"});
    menu.add_row({"2. Buka Menu Hapus Jadwal"});
    menu.add_row({"3. Sisipkan Jadwal (Sesuai NIM)"});
    menu.add_row({"4. Update Jadwal Penerbangan"});
    menu.add_row({"5. Tampilkan Semua Jadwal (Dari Depan)"});
    menu.add_row({"6. Tampilkan Semua Jadwal (Dari Belakang)"});
    menu.add_row({"7. Cari Detail Jadwal"});
    menu.add_row({"0. Keluar"});

    menu[0].format().font_align(FontAlign::center).font_style({FontStyle::bold}).font_color({Color::blue});
    menu[1].format().font_align(FontAlign::center).font_style({FontStyle::bold}).font_color({Color::blue});
    menu[2].format().font_align(FontAlign::center).font_style({FontStyle::bold}).font_color(Color::yellow).padding_top(1).padding_bottom(1);
    
    for (int i = 3; i < menu.size(); ++i) {
        menu[i].format().font_align(FontAlign::left);
    }
    cout << menu << endl;
    cout << "=============================================" << endl;
    cout << "Pilih menu: ";
}

void tampilkanMenuEdit(Node* current) {
    Table menuEdit;
    menuEdit.add_row({"Jadwal ditemukan pilih data yang ingin diubah:"});
    menuEdit.add_row({"1. Tanggal Keberangkatan"});
    menuEdit.add_row({"2. Waktu Keberangkatan"});
    menuEdit.add_row({"3. Tanggal Kedatangan"});
    menuEdit.add_row({"4. Waktu Kedatangan"});
    menuEdit.add_row({"5. Status Penerbangan"});
    menuEdit.add_row({"0. Selesai Mengubah"});

    menuEdit[0].format().font_align(FontAlign::center).font_style({FontStyle::bold}).font_color(Color::yellow);
    for (int i = 1; i < menuEdit.size(); ++i) {
        menuEdit[i].format().font_align(FontAlign::left);
    }
    cout << "\n" << menuEdit << endl;
}

void updateStatusPenerbangan(Node* head) {
    if (head == nullptr) {
        cout << "\nBelum ada jadwal yang terdaftar." << endl;
        system("pause");
        return;
    }
    tampilkanSemuaJadwal(head);
    string kodeCari = inputHandling("\nMasukkan Kode Penerbangan yang akan di-update: ");

    Node* current = head;
    bool ditemukan = false;
    while (current != nullptr) {
        if (current->data.kodepenerbangan == kodeCari) {
            ditemukan = true;
            while(true) {
                clearScreen();
                tampilkanSemuaJadwal(head);
                cout << "\n>>> Mengubah Data untuk Kode: " << current->data.kodepenerbangan << " <<<\n";
                tampilkanMenuEdit(current);
                cout << "Pilihan Anda: ";
                
                cin >> pilihan;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    pilihan = -1;
                }
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
        system("pause");
    }
}

void tampilkanJadwalDariBelakang(Node* tail, int jumlahJadwal) {
    clearScreen();
    cout << "--- Menampilkan Semua Jadwal Penerbangan (Dari Belakang) ---" << endl;
    if (tail == nullptr) {
        cout << "\nBelum ada jadwal penerbangan yang terdaftar" << endl;
    } else {
        Table tabelJadwal;
        tabelJadwal.add_row({"No", "Kode", "Asal", "Tujuan", "Berangkat", "Tiba", "Status"});
        tabelJadwal[0].format().font_align(FontAlign::center).font_style({FontStyle::bold}).font_color(Color::yellow);

        Node* current = tail;
        int i = jumlahJadwal;
        while (current != nullptr) {
            string berangkat = current->data.tanggalkeberangkatan + " " + current->data.waktukeberangkatan;
            string tiba = current->data.tanggalkedatangan + " " + current->data.waktukedatangan;
            tabelJadwal.add_row({to_string(i--), current->data.kodepenerbangan, current->data.bandarasal, current->data.bandaratujuan, berangkat, tiba, current->data.statuspenerbangan});
            current = current->prev;
        }
        
        for (int i = 1; i < tabelJadwal.size(); ++i) {
            tabelJadwal[i].format().font_align(FontAlign::center);
        }
        cout << "\n" << tabelJadwal << endl;
    }
}

void cariDanTampilkanDetail(Node* head) {
    clearScreen();
    if (head == nullptr) {
        cout << "\nBelum ada jadwal yang terdaftar." << endl;
        system("pause");
        return;
    }

    tampilkanJadwalId(head);
    string kodeCari = inputHandling("Masukkan Kode Penerbangan yang ingin dilihat detailnya: ");

    Node* current = head;
    bool ditemukan = false;
    while (current != nullptr) {
        if (current->data.kodepenerbangan == kodeCari) {
            ditemukan = true;
            cout << "\n--- Detail Jadwal Penerbangan ---" << endl;
            Table detailTabel;
            detailTabel.add_row({"Keterangan", "Data"});
            detailTabel[0].format().font_style({FontStyle::bold});
            detailTabel.add_row({"Kode Penerbangan", current->data.kodepenerbangan});
            detailTabel.add_row({"Bandara Asal", current->data.bandarasal});
            detailTabel.add_row({"Bandara Tujuan", current->data.bandaratujuan});
            detailTabel.add_row({"Keberangkatan", current->data.tanggalkeberangkatan + " " + current->data.waktukeberangkatan});
            detailTabel.add_row({"Kedatangan", current->data.tanggalkedatangan + " " + current->data.waktukedatangan});
            detailTabel.add_row({"Status", current->data.statuspenerbangan});

            cout << detailTabel << endl; 
            system("pause");
            break; 
        }
        current = current->next;
    }

    if (!ditemukan) {
        cout << "\nJadwal dengan kode '" << kodeCari << "' tidak ditemukan." << endl;
        system("pause");
    }
}

void hapusSemuaJadwal(Node*& head, Node*& tail) {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

int main() {
    Node* headJadwal = nullptr;
    Node* tailJadwal = nullptr;

    while (true) {
        clearScreen();
        tampilkanMenu();
        
        cin >> pilihan;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1;
        }

        switch (pilihan) {
            case 1:
                menuTambah(headJadwal, tailJadwal, jumlahJadwal);
                break;
            case 2:
                menuHapus(headJadwal, tailJadwal, jumlahJadwal);
                break;
            case 3:
                sisipkanJadwal(headJadwal, tailJadwal, jumlahJadwal);
                break;
            case 4:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                updateStatusPenerbangan(headJadwal);
                break;
            case 5:
                tampilkanSemuaJadwal(headJadwal);
                system("pause");
                break;
            case 6:
                tampilkanJadwalDariBelakang(tailJadwal, jumlahJadwal);
                system("pause");
                break;
            case 7:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cariDanTampilkanDetail(headJadwal);
                break;
            case 0:
                hapusSemuaJadwal(headJadwal, tailJadwal);
                return 0;
            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi." << endl;
                system("pause");
                break;
        }
    }
}