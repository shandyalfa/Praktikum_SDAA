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

struct QueueNode
{
    Pasien data;
    QueueNode *next;
};

struct StackNode
{
    Pasien data;
    StackNode *next;
};

Node *head = nullptr;

QueueNode *frontQueue = nullptr;
QueueNode *rearQueue = nullptr;

StackNode *topStack = nullptr;

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

void tambahPasienFirst(Pasien *pasienBaru)
{
    Node *nodeBaru = new Node();
    nodeBaru->data = *pasienBaru;
    nodeBaru->next = head;
    head = nodeBaru;
    warnaTeks("Pasien berhasil ditambahkan di awal.", "biru");
    sleep();
}

void tambahPasienLast(Pasien *pasienBaru)
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
    warnaTeks("Pasien berhasil ditambahkan di akhir.", "biru");
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

void hapusPasienFirst()
{
    if (head == nullptr)
    {
        warnaTeks("Tidak ada pasien yang terdaftar.", "merah");
        sleep();
        return;
    }
    Node *temp = head;
    head = head->next;
    delete temp;
    warnaTeks("Data pasien di awal berhasil dihapus.", "biru");
    sleep();
}

void hapusPasienLast()
{
    if (head == nullptr)
    {
        warnaTeks("Tidak ada pasien yang terdaftar.", "merah");
        sleep();
        return;
    }

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node *temp = head;
        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
    warnaTeks("Data pasien di akhir berhasil dihapus.", "biru");
    sleep();
}

void tambahPasien()
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
    ulang:
    int pilihan;
    pilihan = inputInteger("Pilih Mode (1. First / 2. Last): ");

    if (pilihan == 1)
    {
        tambahPasienFirst(pasienBaru);
    }
    else if (pilihan == 2)
    {
        tambahPasienLast(pasienBaru);
    }
    else
    {
        warnaTeks("Pilihan tidak valid.", "merah");
        sleep();
        goto ulang;
    }
    delete pasienBaru;
}

void hapusPasien()
{
    ulang:
    if (dataKosong())
        return;

    int pilihan;
    pilihan = inputInteger("Pilih Mode (1. First / 2. Last): ");

    if (pilihan == 1)
    {
        hapusPasienFirst();
    }
    else if (pilihan == 2)
    {
        hapusPasienLast();
    }
    else
    {
        warnaTeks("Pilihan tidak valid.", "merah");
        goto ulang;
    }
}

void enqueueObat(Pasien *pasien)
{
    QueueNode *nodeBaru = new QueueNode();
    nodeBaru->data = *pasien;
    nodeBaru->next = nullptr;

    if (rearQueue == nullptr)
    {
        frontQueue = rearQueue = nodeBaru;
    }
    else
    {
        rearQueue->next = nodeBaru;
        rearQueue = nodeBaru;
    }
    warnaTeks("Pasien ditambahkan ke antrean obat.", "biru");
}

void dequeueObat_pushStackRiwayatObat()
{
    if (frontQueue == nullptr)
    {
        warnaTeks("Antrean kosong.", "merah");
        return;
    }
    QueueNode *temp = frontQueue;
    frontQueue = frontQueue->next;
    if (frontQueue == nullptr)
    {
        rearQueue = nullptr;
    }
    StackNode *nodeBaru = new StackNode();
    nodeBaru->data = temp->data;
    nodeBaru->next = topStack;
    topStack = nodeBaru;
    warnaTeks("Obat untuk " + temp->data.nama + " telah diproses.", "biru");
    delete temp;
}

void tampilkanAntreanObat()
{
    if (frontQueue == nullptr)
    {
        warnaTeks("Antrean obat kosong.", "merah");
        return;
    }

    QueueNode *temp = frontQueue;
    int i = 1;
    while (temp != nullptr)
    {
        cout << "Pasien ke-" << i << ": " << temp->data.nama << endl;
        temp = temp->next;
        i++;
    }
}

void tampilkanRiwayatObat()
{
    if (topStack == nullptr)
    {
        warnaTeks("Tidak ada riwayat pengambilan obat.", "merah");
        return;
    }
    StackNode *temp = topStack;
    int i = 1;
    while (temp != nullptr)
    {
        cout << "--------------------------" << endl;
        cout << "Riwayat ke-" << i << ":" << endl;
        cout << "Nama: " << temp->data.nama << endl;
        cout << "Umur: " << temp->data.umur << endl;
        cout << "Alamat: " << temp->data.alamat << endl;
        cout << "Keluhan: " << temp->data.keluhan << endl;
        cout << "--------------------------" << endl;
        temp = temp->next;
        i++;
    }
}

void hapusRiwayatTerbaru_popStack()
{ 
    if (topStack == nullptr)
    {
        warnaTeks("Tidak ada riwayat untuk dihapus.", "merah");
        return;
    }
    StackNode *temp = topStack;
    topStack = topStack->next;
    warnaTeks("Menghapus riwayat pengambilan obat: " + temp->data.nama, "biru");
    delete temp;
}

void hapusSemuaRiwayat()
{
    while (topStack != nullptr)
    {
        hapusRiwayatTerbaru_popStack();
    }
    warnaTeks("Semua riwayat pengambilan obat telah dihapus.", "biru");
}

void opsi_Obat()
{
    int pilihan;
    do
    {
        clear();
        cout << "=============================================================" << endl;
        cout << "::                     Manajemen Obat                      ::" << endl;
        cout << "=============================================================" << endl;
        cout << "::       1. Tambah ke Antrean Obat [ Enqueue ]             ::" << endl;
        cout << "::       2. Proses Pengambilan Obat [ Dequeue & PUSH ]     ::" << endl;
        cout << "::       3. Tampilkan Antrean Obat                         ::" << endl;
        cout << "::       4. Tampilkan Riwayat Obat                         ::" << endl;
        cout << "::       5. Hapus Riwayat Terbaru [ POP ]                  ::" << endl;
        cout << "::       6. Hapus Semua Riwayat                            ::" << endl;
        cout << "::       7. Kembali                                        ::" << endl;
        cout << "=============================================================" << endl;
        pilihan = inputInteger("Pilih Opsi: ");
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
            enqueueObat(pasienBaru);
            delete pasienBaru;
            break;
        }
        case 2:
            dequeueObat_pushStackRiwayatObat();
            break;
        case 3:
            tampilkanAntreanObat();
            pause();
            break;
        case 4:
            tampilkanRiwayatObat();
            pause();
            break;
        case 5:
            hapusRiwayatTerbaru_popStack();
            break;
        case 6:
            hapusSemuaRiwayat();
            break;
        case 7:
            cout << "Kembali ke menu utama." << endl;
            break;
        default:
            warnaTeks("Pilihan tidak valid. Coba lagi.", "merah");
            sleep();
            break;
        }
    } while (pilihan != 7);
}

void opsi_Pasien()
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
        cout << "::   5. Manajemen Obat            ::" << endl;
        cout << "::   6. Keluar                    ::" << endl;
        cout << "====================================" << endl;
        pilihan = inputInteger("Pilih Opsi: ");
        switch (pilihan)
        {
        case 1:
            tambahPasien();
            break;
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
            hapusPasien();
            break;
        case 5:
            opsi_Obat();
            break;
        case 6:
            cout << "Terima kasih! Program selesai." << endl;
            break;
        default:
            warnaTeks("Pilihan tidak valid. Coba lagi.", "merah");
            sleep();
            break;
        }
    } while (pilihan != 6);
}

int main()
{
    opsi_Pasien();
    return 0;
}