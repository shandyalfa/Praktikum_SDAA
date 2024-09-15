#include <iostream>
using namespace std;


int angka_pascal(int i, int j) {
    if (j == 0 || j == i) {
        return 1;
    }
    else {
        return angka_pascal(i - 1, j - 1) + angka_pascal(i - 1, j);
    }
}

void cetak_segitiga_pascal(int tingkat) {
    for (int i = 0; i < tingkat; i++) {
        for (int j = 0; j <= i; j++) {
            cout << angka_pascal(i, j) << " ";  
        }
        cout << endl;  
    }
}

int main() {
    int tingkat = 3;  
    cetak_segitiga_pascal(tingkat);  
    return 0;
}
