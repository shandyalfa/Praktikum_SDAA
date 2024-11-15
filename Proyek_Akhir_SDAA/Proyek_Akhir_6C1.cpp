#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <limits>
#include <cmath>

using namespace std;

struct Pasien
{
    int id_pasien;
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
    string obat;
    QueueNode *next;
};

struct StackNode
{
    Pasien data;
    string obat;
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

string inputString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
          getline(cin, input);
        bool isEmpty = true;
        for (char c : input) {
            if (!isspace(c)) {
                isEmpty = false;
                break;
            }
        }

        if (isEmpty) {
        	warnaTeks("Input tidak boleh kosong atau hanya berisi spasi. Silakan coba lagi." , "merah");
        } else {
            return input;
        }
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


Node* merge(Node* left, Node* right, bool ascending) {
    if (!left) return right;
    if (!right) return left;

    Node* result = nullptr;

    if (ascending ? (left->data.nama <= right->data.nama) : (left->data.nama >= right->data.nama)) {
        result = left;
        result->next = merge(left->next, right, ascending);
    } else {
        result = right;
        result->next = merge(left, right->next, ascending);
    }
    return result;
}

void split(Node* source, Node** front, Node** back) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

void mergeSort(Node** headRef, bool ascending) {
    if (*headRef == nullptr || (*headRef)->next == nullptr) {
        return;
    }

    Node* head = *headRef;
    Node* left;
    Node* right;

    split(head, &left, &right);

    mergeSort(&left, ascending);
    mergeSort(&right, ascending);

    *headRef = merge(left, right, ascending);
}

void shellSort(Node** headRef, bool ascending) {
    int n = 0;
    Node *temp = *headRef;

    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    if (n < 2) return;

    Node **arr = new Node*[n];
    temp = *headRef;
    for (int i = 0; i < n; i++) {
        arr[i] = temp;
        temp = temp->next;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Node* temp = arr[i];
            int j;
            for (j = i; j >= gap && (ascending ? (arr[j - gap]->data.nama > temp->data.nama) : (arr[j - gap]->data.nama < temp->data.nama)); j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        arr[i]->next = arr[i + 1];
    }
    arr[n - 1]->next = nullptr;

    *headRef = arr[0];

    delete[] arr;
}



void tampilkanDaftarPasien() {
    if (head == nullptr) {
        warnaTeks("Tidak ada pasien yang terdaftar.", "merah");
        sleep();
        return;
    }

    ulang_algoritma:
    int pilihan_algoritma = inputInteger("Pilih algoritma pengurutan Untuk Nama (1. Merge Sort / 2. Shell Sort): ");

    if (pilihan_algoritma != 1 && pilihan_algoritma != 2) {
        warnaTeks("Pilihan tidak valid.", "merah");
        sleep();
        goto ulang_algoritma;
    }

    ulang_urutan:
    int pilihan_urutan = inputInteger("Pilih urutan (1. Ascending / 2. Descending): ");
    bool ascending;

    if (pilihan_urutan == 1) {
        ascending = true;
    } else if (pilihan_urutan == 2) {
        ascending = false;
    } else {
        warnaTeks("Pilihan tidak valid.", "merah");
        sleep();
        goto ulang_urutan;
    }

    if (pilihan_algoritma == 1) {
        mergeSort(&head, ascending);
    } else if (pilihan_algoritma == 2) {
        shellSort(&head, ascending);
    }

    Node* temp = head;
    int i = 1;
    while (temp != nullptr) {
        cout << "--------------------------" << endl;
        cout << "Pasien ke-" << i << ":" << endl;
        cout << "Id     : " << temp->data.id_pasien << endl;
        cout << "Nama   : " << temp->data.nama << endl;
        cout << "Umur   : " << temp->data.umur << endl;
        cout << "Alamat : " << temp->data.alamat << endl;
        cout << "Keluhan: " << temp->data.keluhan << endl;
        cout << "--------------------------" << endl;
        temp = temp->next;
        i++;
    }
    
}

void updatePasien(int id)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data.id_pasien == id)
        {
            cout << "Masukkan data baru untuk Id pasien " << id << ":" << endl;
            temp->data.nama = inputString("Nama   : ");
            temp->data.umur = inputInteger("Umur   : ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            temp->data.alamat = inputString("Alamat : ");
            temp->data.keluhan = inputString("Keluhan : ");
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
void tambahPasien() {
    Pasien *pasienBaru = new Pasien;
    cin.ignore();
    pasienBaru->id_pasien = inputInteger("Masukkan Id Pasien  : ");
    Node *temp = head;
    while (temp != nullptr) {
        if (temp->data.id_pasien == pasienBaru->id_pasien) {
            warnaTeks("Error: Id Pasien sudah ada. Harap masukkan Id Pasien yang berbeda.", "merah");
            delete pasienBaru;
            sleep();
            return;
        }
        temp = temp->next;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    pasienBaru->nama = inputString("Nama   : ");
    pasienBaru->umur = inputInteger("Umur   : ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    pasienBaru->alamat = inputString("Alamat : ");
    pasienBaru->keluhan= inputString("Keluhan : ");

    ulang:
    int pilihan;
    pilihan = inputInteger("Pilih Mode (1. First / 2. Last): ");

    if (pilihan == 1) {
        tambahPasienFirst(pasienBaru);
    } else if (pilihan == 2) {
        tambahPasienLast(pasienBaru);
    } else {
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
void enqueueObat()
{
    Pasien *pasienBaru = new Pasien;
    cin.ignore();

    pasienBaru->nama = inputString("Nama   : ");
    pasienBaru->keluhan= inputString("Keluhan : ");
    string obat;
    obat = inputString("Obat : ");

    QueueNode *nodeBaru = new QueueNode();
    nodeBaru->data = *pasienBaru;
    nodeBaru->obat = obat; 
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
    sleep();
    delete pasienBaru;
}

void dequeueObat_pushStackRiwayatObat()
{
    if (frontQueue == nullptr)
    {
        warnaTeks("Antrean kosong.", "merah");
        sleep();
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
    nodeBaru->obat = temp->obat;
    nodeBaru->next = topStack;
    topStack = nodeBaru;
    warnaTeks("Obat untuk " + temp->data.nama + " telah diproses.", "biru");
    sleep();
    delete temp;
}

void tampilkanAntreanObat()
{
    if (frontQueue == nullptr)
    {
        warnaTeks("Antrean obat kosong.", "merah");
        sleep();
        return;
    }

    QueueNode *temp = frontQueue;
    int i = 1;
    while (temp != nullptr)
    {
        cout << "Pasien ke-" << i << ": " << temp->data.nama << endl;
		cout << "Obat   : " << temp->obat << endl;  // Menampilkan obat
		cout << endl;
        temp = temp->next;
        i++;
    }
}

void tampilkanRiwayatObat()
{
    if (topStack == nullptr)
    {
        warnaTeks("Tidak ada riwayat pengambilan obat.", "merah");
        sleep();
        return;
    }
    StackNode *temp = topStack;
    int i = 1;
    while (temp != nullptr)
    {
        cout << "--------------------------" << endl;
        cout << "Riwayat ke-" << i << ":" << endl;
        cout << "Nama: " << temp->data.nama << endl;
        cout << "Keluhan: " << temp->data.keluhan << endl;
cout << "Obat    : " << temp->obat << endl;  // Menampilkan obat
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
        sleep();
        return;
    }
    StackNode *temp = topStack;
    topStack = topStack->next;
    
    delete temp;
}

void hapusSemuaRiwayat()
{
	if(topStack == nullptr){
		warnaTeks("Riwayat Kosong", "merah");
		return;
	}
    while (topStack != nullptr)
    {
        hapusRiwayatTerbaru_popStack();
    }
   warnaTeks("Semua riwayat pengambilan obat telah dihapus.", "biru");
}

void simpanPasienKeCSV(const string &filename) {
    ofstream file(filename);
    Node *temp = head;
    while (temp != nullptr) {
        file << temp->data.id_pasien << "," << temp->data.nama << "," << temp->data.umur << "," << temp->data.alamat << "," << temp->data.keluhan << endl;
        temp = temp->next;
    }
    file.close();
}

void muatPasienDariCSV(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Pasien pasienBaru;
        ss >> pasienBaru.id_pasien;
        ss.ignore();
        getline(ss, pasienBaru.nama, ',');
        ss >> pasienBaru.umur;
        ss.ignore();
        getline(ss, pasienBaru.alamat, ',');
        getline(ss, pasienBaru.keluhan);

        Node *nodeBaru = new Node();
        nodeBaru->data = pasienBaru;
        nodeBaru->next = head;
        head = nodeBaru;
    }
    file.close();
}

int fibonacciSearch(Node* head, int umur) {
    int fibMMm2 = 0;  // (m-2)'th Fibonacci number
    int fibMMm1 = 1;  // (m-1)'th Fibonacci number
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci number

    // Menghitung panjang linked list
    int n = 0;
    Node* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    if (n == 0) return -1;  // Jika list kosong, return -1

    Node* current = head;
    int offset = -1;

    // Mencari Fibonacci number yang lebih besar dari atau sama dengan n
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    // Fibonacci search loop
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        Node* nodeAtI = head;
        for (int j = 0; j < i && nodeAtI != nullptr; j++) {
            nodeAtI = nodeAtI->next;
        }

        // Pencocokan umur pasien
        if (nodeAtI == nullptr || nodeAtI->data.umur < umur) {
            // Jika umur pasien kurang dari umur yang dicari
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (nodeAtI->data.umur > umur) {
            // Jika umur pasien lebih besar dari umur yang dicari
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            // Jika umur pasien cocok dengan yang dicari
            // Tampilkan semua pasien dengan umur yang sama
            while (nodeAtI != nullptr && nodeAtI->data.umur == umur) {
                cout << "Pasien ditemukan!" << endl;
                cout << "--------------------------" << endl;
                cout << "Id     : " << nodeAtI->data.id_pasien << endl;
                cout << "Nama   : " << nodeAtI->data.nama << endl;
                cout << "Umur   : " << nodeAtI->data.umur << endl;
                cout << "Alamat : " << nodeAtI->data.alamat << endl;
                cout << "Keluhan: " << nodeAtI->data.keluhan << endl;
                cout << "--------------------------" << endl;
                nodeAtI = nodeAtI->next;  // Pindah ke pasien berikutnya dengan umur yang sama
            }
            return 0;  // Berhenti setelah menampilkan semua pasien dengan umur yang sama
        }
    }

    // Pemeriksaan terakhir jika fibMMm1 == 1
    if (fibMMm1 && current->data.umur == umur) {
        cout << "Pasien ditemukan!" << endl;
        cout << "--------------------------" << endl;
        cout << "Id     : " << current->data.id_pasien << endl;
        cout << "Nama   : " << current->data.nama << endl;
        cout << "Umur   : " << current->data.umur << endl;
        cout << "Alamat : " << current->data.alamat << endl;
        cout << "Keluhan: " << current->data.keluhan << endl;
        cout << "--------------------------" << endl;
        return offset + 1;
    }

    // Jika tidak ditemukan kecocokan
    cout << "Pasien dengan umur " << umur << " tidak ditemukan." << endl;
    return -1;
}



int jumpSearch(Node* head, int id) {
    int n = 0;
    Node* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    int step = sqrt(n);
    int prev = 0;
    temp = head;

    Node* last = head;
    for (int i = 0; i < step && last != nullptr; i++) {
        last = last->next;
    }

    while (last != nullptr && last->data.id_pasien < id) {
        prev += step;
        temp = last;
        for (int i = 0; i < step && last != nullptr; i++) {
            last = last->next;
        }
    }

    while (temp != nullptr && prev < n) {
        if (temp->data.id_pasien == id) {
            return prev;
        }
        temp = temp->next;
        prev++;
    }

    return -1;
}

void tampilkanPasienById(int id) {
    int index = jumpSearch(head, id);
    if (index != -1) {
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        cout << "--------------------------" << endl;
        cout << "Id     : " << temp->data.id_pasien << endl;
        cout << "Nama   : " << temp->data.nama << endl;
        cout << "Umur   : " << temp->data.umur << endl;
        cout << "Alamat : " << temp->data.alamat << endl;
        cout << "Keluhan: " << temp->data.keluhan << endl;
        cout << "--------------------------" << endl;
    } else {
        warnaTeks("Pasien tidak ditemukan.", "merah");
    }
}

void boyerMooreSearch(Node* head, string pattern) {
    int m = pattern.length();
    int badChar[256];

    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    Node* temp = head;
    bool found = false;
    int pos = 0;

    while (temp != nullptr) {
        string text = temp->data.nama;
        int n = text.length();
        int s = 0;

        while (s <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && pattern[j] == text[s + j]) {
                j--;
            }

            if (j < 0) {
                cout << "Pasien ditemukan!" << endl;
                cout << "--------------------------" << endl;
                cout << "Id     : " << temp->data.id_pasien << endl;
                cout << "Nama   : " << temp->data.nama << endl;
                cout << "Umur   : " << temp->data.umur << endl;
                cout << "Alamat : " << temp->data.alamat << endl;
                cout << "Keluhan: " << temp->data.keluhan << endl;
                cout << "--------------------------" << endl;
                found = true;
                break;
            } else {
                s += max(1, j - badChar[text[s + j]]);
            }
        }

        temp = temp->next;
        pos++;
    }

    if (!found) {
        cout << "Nama pasien tidak ditemukan." << endl;
    }
}


void opsi_Search() {
    int pilihan;
    do {
        clear();
        cout << "========================================================" << endl;
        cout << "::                    Pencarian Pasien                ::" << endl;
        cout << "========================================================" << endl;
        cout << "::   1. Cari Pasien Berdasarkan Umur (Fibonacci)      ::" << endl;
        cout << "::   2. Cari Pasien Berdasarkan Id (Jump)             ::" << endl;
        cout << "::   3. Cari Pasien Berdasarkan Nama (Boyer-Moore)    ::" << endl;
        cout << "::   4. Kembali                                       ::" << endl;
        cout << "========================================================" << endl;
        pilihan = inputInteger("Pilih Opsi: ");
        switch (pilihan) {
        case 1: {
        	cin.ignore();
            int umur = inputInteger("Masukkan umur pasien yang dicari: ");
            fibonacciSearch(head, umur);
            pause();
            break;
        }
        
        case 2: {
            int id = inputInteger("Masukkan Id pasien yang dicari: ");
            int index = jumpSearch(head, id);
            tampilkanPasienById(id);
            pause();
            break;
        }
        case 3: {   
        	cin.ignore();
            string nama;
            cout << "Masukkan nama pasien yang dicari: ";
            getline(cin, nama);
            boyerMooreSearch(head, nama);
           
            pause();
            break;
        }
        case 4:
            cout << "Kembali ke menu." << endl;
            sleep();
            break;
        default:
            warnaTeks("Pilihan tidak valid. Coba lagi.", "merah");
            sleep();
            break;
        }
    } while (pilihan != 4);
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

            enqueueObat();
            
            break;
        }
        case 2:
            dequeueObat_pushStackRiwayatObat();
            sleep();
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
            
            sleep();
            break;
        case 6:
        	
            hapusSemuaRiwayat();
            sleep();
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
        cout << "::   5. Cari Pasien               ::" << endl;
        cout << "::   6. Manajemen Obat            ::" << endl;
        cout << "::   7. Keluar                    ::" << endl;
        cout << "====================================" << endl;
        pilihan = inputInteger("Pilih Opsi: ");
        switch (pilihan)
        {
        case 1:
            tambahPasien();
            simpanPasienKeCSV("data_pasien.csv");
            break;
        case 2:
            tampilkanDaftarPasien();
            pause();
            break;
        case 3:
        {
        	tampilkanDaftarPasien();
            if (dataKosong())
                break;
            fflush(stdin);
            int id = inputInteger( "Masukkan id pasien yang ingin diupdate: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            updatePasien(id);
            simpanPasienKeCSV("data_pasien.csv");
            break;
        }
        case 4:
        	tampilkanDaftarPasien();
            hapusPasien();
            simpanPasienKeCSV("data_pasien.csv");
            break;
        case 5:
            opsi_Search();
            break;
        case 6:
            opsi_Obat();
            break;
        case 7:
            cout << "Terima kasih! Program selesai." << endl;
            exit(1);
            break;
        default:
            warnaTeks("Pilihan tidak valid. Coba lagi.", "merah");
            sleep();
            break;  
        }
    } while (pilihan != 7);
}

int main() {
    muatPasienDariCSV("data_pasien.csv");
    opsi_Pasien();
    
    return 0;
}