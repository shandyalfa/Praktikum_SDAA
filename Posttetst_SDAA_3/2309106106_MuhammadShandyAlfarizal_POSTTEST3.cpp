#include <iostream>
#include <chrono>
#include <limits>
using namespace std;

struct Pasien
{
    string nama;
    int umur;
    string alamat;
    string keluhan;
};

struct Node
{
    Pasien data;
    Node *next;
};

Node *head = nullptr;

void sleep()
{
    auto start = chrono::high_resolution_clock::now();
    while (chrono::duration_cast<chrono::seconds>(
               chrono::high_resolution_clock::now() - start)
               .count() < 1)
    {
    }
}

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause()
{
    system("pause");
    cin.ignore();
}

void warnaTeks(string teks, string warna)
{
    if (warna == "merah")
    {
        cout << "\033[31m" << teks << "\033[0m" << endl;
    }
    else if (warna == "biru")
    {
        cout << "\033[34m" << teks << "\033[0m" << endl;
    }
}

int inputInteger(string teks)
{
    int numerik;
    while (true)
    {
        cout << teks;
        cin >> numerik;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            warnaTeks("Error: Masukan tidak valid. Harap masukkan angka integer.", "merah");
        }
        else
        {
            return numerik;
        }
    }
}

void tambahPasien(Pasien *pasienBaru)
{
    Node *nodeBaru = new Node();
    nodeBaru->data = *pasienBaru;
    nodeBaru->next = nullptr;

    if (head == nullptr)
    {
        head = nodeBaru;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }
    warnaTeks("Pasien berhasil ditambahkan.", "biru");
    sleep();
}

bool dataKosong()
{
    if (head == nullptr)
    {
        warnaTeks("Tidak ada pasien yang terdaftar.", "merah");
        sleep();
        return true;
    }
    else
    {
        return false;
    }
}

int cariPasien(string nama)
{
    Node *temp = head;
    int indeks = 0;
    while (temp != nullptr)
    {
        if (temp->data.nama == nama)
        {
            return indeks;
        }
        temp = temp->next;
        indeks++;
    }
    return -1;
}

void tampilkanDaftarPasien()
{
    if (dataKosong())
        return;

    Node *temp = head;
    int i = 1;
    while (temp != nullptr)
    {
        cout << "--------------------------" << endl;
        cout << "Pasien ke-" << i << ":" << endl;
        cout << "Nama: " << temp->data.nama << endl;
        cout << "Umur: " << temp->data.umur << endl;
        cout << "Alamat: " << temp->data.alamat << endl;
        cout << "Keluhan: " << temp->data.keluhan << endl;
        cout << "--------------------------" << endl;
        temp = temp->next;
        i++;
    }
    pause();
}

void updatePasien(string nama)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data.nama == nama)
        {
            cout << "Masukkan data baru untuk pasien " << nama << ":" << endl;
            cout << "Nama   : ";
            getline(cin, temp->data.nama);
            temp->data.umur = inputInteger("Masukkan Umur   : ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Alamat : ";
            getline(cin, temp->data.alamat);
            cout << "Keluhan: ";
            getline(cin, temp->data.keluhan);
            warnaTeks("Pasien berhasil diperbarui.", "biru");
            sleep();
            return;
        }
        temp = temp->next;
    }
    warnaTeks("Pasien tidak ditemukan.", "merah");
    sleep();
}

void hapusPasien(string nama)
{
    if (head == nullptr)
    {
        warnaTeks("Tidak ada pasien yang terdaftar.", "merah");
        sleep();
        return;
    }

    if (head->data.nama == nama)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        warnaTeks("Data pasien berhasil dihapus.", "biru");
        sleep();
        return;
    }

    Node *temp = head;
    while (temp->next != nullptr && temp->next->data.nama != nama)
    {
        temp = temp->next;
    }

    if (temp->next == nullptr)
    {
        warnaTeks("Pasien tidak ditemukan.", "merah");
        sleep();
        return;
    }

    Node *nodeHapus = temp->next;
    temp->next = temp->next->next;
    delete nodeHapus;
    warnaTeks("Data pasien berhasil dihapus.", "biru");
    sleep();
}

int main()
{
    int pilihan;
    do
    {
        clear();
        cout << "====================================" << endl;
        cout << "::      Manajemen Puskesmas       ::" << endl;
        cout << "====================================" << endl;
        cout << "::   1. Tambah Pasien             ::" << endl;
        cout << "::   2. Tampilkan Daftar Pasien   ::" << endl;
        cout << "::   3. Update Data Pasien        ::" << endl;
        cout << "::   4. Hapus Pasien              ::" << endl;
        cout << "::   5. Keluar                    ::" << endl;
        cout << "====================================" << endl;
        pilihan = inputInteger("Pilih Opsi : ");
        switch (pilihan)
        {
        case 1:
        {
            Pasien *pasienBaru = new Pasien;
            cin.ignore();
            cout << "Masukkan nama   : ";
            getline(cin, pasienBaru->nama);
            pasienBaru->umur = inputInteger("Masukkan Umur   : ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan alamat : ";
            getline(cin, pasienBaru->alamat);
            cout << "Masukkan keluhan: ";
            getline(cin, pasienBaru->keluhan);
            tambahPasien(pasienBaru);
            delete pasienBaru;
            break;
        }
        case 2:
            tampilkanDaftarPasien();
            break;
        case 3:
        {
            if (dataKosong())
                break;
            fflush(stdin);
            string nama;
            cout << "Masukkan nama pasien yang ingin diupdate: ";
            getline(cin, nama);
            updatePasien(nama);
            break;
        }
        case 4:
        {
            if (dataKosong())
                break;
            fflush(stdin);
            string nama;
            cout << "Masukkan nama pasien yang ingin dihapus: ";
            getline(cin, nama);
            hapusPasien(nama);
            break;
        }
        case 5:
            cout << "Terima kasih! Program selesai." << endl;
            break;
        default:
            warnaTeks("Pilihan tidak valid. Coba lagi.", "merah");
            sleep();
            break;
        }
    } while (pilihan != 5);
    return 0;
}
