#include <iostream>
#include <chrono>
#include <limits>
using namespace std;

const int totalPasien = 100;

struct Pasien {
    string nama;
    int umur;
    string alamat;
    string keluhan;
};

Pasien daftarPasien[totalPasien];
int jumlahPasien = 0;

void sleep(){
    auto start = chrono::high_resolution_clock::now();
    while (chrono::duration_cast<chrono::seconds>(
                chrono::high_resolution_clock::now() - start).count() < 1) {
    }
}

void clear(){
    system("cls");
}

void pause(){
    system("pause");
}

void warnaTeks(string teks, string warna){
    if(warna =="merah"){
    cout << "\033[31m" << teks << "\033[0m" << endl; 
    }
    else if(warna == "biru"){
    cout << "\033[34m" << teks << "\033[0m" << endl;  
    }
}

int inputInteger(string teks) {
    int numerik;
    while (true) {
        cout << teks;
        cin >> numerik;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            warnaTeks("Error: Masukan tidak valid. Harap masukkan angka integer.","merah");
        } else {
            return numerik; 
        }
    }
}

void tambahPasien(Pasien* pasienBaru) {
    if (jumlahPasien >= totalPasien) {
        warnaTeks("Data penuh, tidak bisa menambah pasien lagi.","merah");
        sleep();
        return;
    }
    daftarPasien[jumlahPasien] = *pasienBaru;
    jumlahPasien++;
    warnaTeks("Pasien berhasil ditambahkan.","biru" );
    sleep();
}

bool dataKosong(){
    if (jumlahPasien == 0) {
        warnaTeks("Tidak ada pasien yang terdaftar.","merah");
        sleep();
        return true;
    }else{
        return false;
    }
}

int cariPasien(string nama) {
    for (int i = 0; i < jumlahPasien; i++) {
        if (daftarPasien[i].nama == nama) {
            return i;
        }
    }
    return -1;
}

void tampilkanDaftarPasien() {
    for (int i = 0; i < jumlahPasien; i++) {
        cout << "--------------------------" << endl;
        cout << "Pasien ke-" << i + 1 << ":" << endl;
        cout << "Nama: " << daftarPasien[i].nama << endl;
        cout << "Umur: " << daftarPasien[i].umur << endl;
        cout << "Alamat: " << daftarPasien[i].alamat << endl;
        cout << "Keluhan: " << daftarPasien[i].keluhan << endl;
        cout << "--------------------------" << endl;
    }
    pause();
}

void updatePasien(string nama) {
    int index = cariPasien(nama);
    if (index == -1) {
        warnaTeks("Pasien tidak ditemukan.","merah");
        sleep();
        return;
    }
    cout << "Masukkan data baru untuk pasien " << nama << ":" << endl;
    cout << "Nama   : ";
    getline(cin, daftarPasien[index].nama);
    // cin.ignore();
    daftarPasien[index].umur = inputInteger("Masukkan Umur   : ");
    cin.ignore();
    cout << "Alamat : ";
    getline(cin, daftarPasien[index].alamat);
    cout << "Keluhan: ";
    getline(cin, daftarPasien[index].keluhan);
    warnaTeks("Pasien berhasil diperbarui.","biru" );
    sleep();
}

void hapusPasien(string nama) {
    int index = cariPasien(nama);
    if (index == -1) {
        warnaTeks("Pasien tidak ditemukan.","merah");
        sleep();
        return;
    }
    for (int i = index; i < jumlahPasien - 1; i++) {
        daftarPasien[i] = daftarPasien[i + 1];
    }
    jumlahPasien--;
    warnaTeks("Data pasien berhasil dihapus.", "biru");
    sleep();
}

void tampilkanMenu(){
    cout << "====================================" << endl;
    cout << "::      Manajemen Puskesmas       ::" << endl;
    cout << "====================================" << endl;
    cout << "::   1. Tambah Pasien             ::" << endl;
    cout << "::   2. Tampilkan Daftar Pasien   ::" << endl;
    cout << "::   3. Update Data Pasien        ::" << endl;
    cout << "::   4. Hapus Pasien              ::" << endl;
    cout << "::   5. Keluar                    ::" << endl;
    cout << "====================================" << endl;
}

int main() {
    int pilihan;
    do {
        clear();
        tampilkanMenu();
        pilihan = inputInteger("Pilih Opsi : ");
        switch (pilihan) {
            case 1: {
                Pasien* pasienBaru = new Pasien;
                cin.ignore();
                cout << "Masukkan nama   : ";
                getline(cin, pasienBaru->nama);
                pasienBaru->umur = inputInteger("Masukkan Umur   : ");
                cin.ignore();
                cout << "Masukkan alamat : ";
                getline(cin, pasienBaru->alamat);
                cout << "Masukkan keluhan: ";
                getline(cin, pasienBaru->keluhan);
                tambahPasien(pasienBaru);
                delete pasienBaru; 
                break;
            }
            case 2:
                if(dataKosong()){
                    break;
                }else{
                    tampilkanDaftarPasien();
                }
                break;
            case 3: {
                if(dataKosong()){
                    break;
                }else{
                    fflush(stdin);
                    string nama;
                    cout << "Masukkan nama pasien yang ingin diupdate: ";
                    getline(cin, nama);
                    updatePasien(nama);
                }
                break;
            }
            case 4: {
                if(dataKosong()){
                    break;
                }
                else{
                    fflush(stdin);
                    string nama;
                    cout << "Masukkan nama pasien yang ingin dihapus: ";
                    getline(cin, nama);
                    hapusPasien(nama);
                }
                break;
            }
            case 5:
                cout << "Terima kasih! Program selesai." << endl;
                break;
            default:
                warnaTeks("Pilihan tidak valid. Coba lagi.","merah");
                sleep();
                break;
        }
    } while (pilihan != 5);
    return 0;
}
