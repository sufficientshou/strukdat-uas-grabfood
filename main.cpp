#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

struct Makanan {
    string nama;
    int harga;
    bool tersedia;
};

struct Restoran {
    string nama;
    float jarak;
    float rating;
    Makanan menu[10];
    int jumlahMenu;
};

Restoran daftarRestoran[5];
int jumlahRestoran = 0;

void isiDataRestoran() {
    daftarRestoran[0].nama = "Warung Padang Yapyap";
    daftarRestoran[0].jarak = 1.2;
    daftarRestoran[0].rating = 4.5;
    daftarRestoran[0].jumlahMenu = 5;
    
    daftarRestoran[0].menu[0] = {"Nasi Rendang", 25000, true};
    daftarRestoran[0].menu[1] = {"Nasi Gudeg", 20000, true};
    daftarRestoran[0].menu[2] = {"Ayam Pop", 22000, true};
    daftarRestoran[0].menu[3] = {"Sayur Nangka", 15000, true};
    daftarRestoran[0].menu[4] = {"Es Teh Manis", 5000, true};
    
    daftarRestoran[1].nama = "Bakso Malang Mas Celo";
    daftarRestoran[1].jarak = 2.1;
    daftarRestoran[1].rating = 4.2;
    daftarRestoran[1].jumlahMenu = 4;
    
    daftarRestoran[1].menu[0] = {"Bakso Jumbo", 18000, true};
    daftarRestoran[1].menu[1] = {"Mie Ayam Bakso", 16000, true};
    daftarRestoran[1].menu[2] = {"Bakso Urat", 20000, true};
    daftarRestoran[1].menu[3] = {"Es Jeruk", 6000, true};
    
    daftarRestoran[2].nama = "Ayam Geprek Mas Rusdi";
    daftarRestoran[2].jarak = 0.8;
    daftarRestoran[2].rating = 4.7;
    daftarRestoran[2].jumlahMenu = 6;
    
    daftarRestoran[2].menu[0] = {"Ayam Geprek Original", 17000, true};
    daftarRestoran[2].menu[1] = {"Ayam Geprek Keju", 20000, true};
    daftarRestoran[2].menu[2] = {"Ayam Geprek Sambal Matah", 19000, true};
    daftarRestoran[2].menu[3] = {"Nasi Putih", 3000, true};
    daftarRestoran[2].menu[4] = {"Teh Botol", 4000, true};
    daftarRestoran[2].menu[5] = {"Es Krim", 8000, true};
    
    jumlahRestoran = 3;
}

void tampilkanDaftarRestoran() {
    cout << "=== DAFTAR RESTORAN ===" << endl;
    for(int i = 0; i < jumlahRestoran; i++) {
        cout << i+1 << ". " << daftarRestoran[i].nama << endl;
        cout << "   Jarak: " << daftarRestoran[i].jarak << " km" << endl;
        cout << "   Rating: " << daftarRestoran[i].rating << "/5" << endl;
        cout << endl;
    }
}

void tampilkanMenuRestoran(int indeks) {
    if(indeks < 0 || indeks >= jumlahRestoran) {
        cout << "Restoran tidak ditemukan!" << endl;
        return;
    }
    
    cout << "=== MENU " << daftarRestoran[indeks].nama << " ===" << endl;
    for(int i = 0; i < daftarRestoran[indeks].jumlahMenu; i++) {
        cout << i+1 << ". " << daftarRestoran[indeks].menu[i].nama;
        cout << " - Rp " << daftarRestoran[indeks].menu[i].harga;
        if(!daftarRestoran[indeks].menu[i].tersedia) {
            cout << " (HABIS)";
        }
        cout << endl;
    }
}

void tampilkanMenuUtama() {
    cout << "=== SIMULASI GRABFOOD ===" << endl;
    cout << "Selamat datang di aplikasi pemesanan makanan!" << endl;
    cout << endl;
    cout << "1. Pelanggan" << endl;
    cout << "2. Mitra Restoran" << endl;
    cout << "3. Log Driver" << endl;
    cout << "4. Keluar" << endl;
    cout << endl;
    cout << "Pilih menu: ";
}

void menuPelanggan() {
    int pilihan;
    
    while(true) {
        system("cls");
        cout << "=== MENU PELANGGAN ===" << endl;
        cout << "1. Lihat Daftar Restoran" << endl;
        cout << "2. Cari Restoran" << endl;
        cout << "3. Keranjang Belanja" << endl;
        cout << "4. Kembali ke Menu Utama" << endl;
        cout << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                system("cls");
                tampilkanDaftarRestoran();
                cout << "Pilih restoran (1-" << jumlahRestoran << "): ";
                int pilihanRestoran;
                cin >> pilihanRestoran;
                
                if(pilihanRestoran >= 1 && pilihanRestoran <= jumlahRestoran) {
                    system("cls");
                    tampilkanMenuRestoran(pilihanRestoran - 1);
                    cout << endl;
                    cout << "Tekan Enter untuk kembali...";
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Pilihan tidak valid, coba lagi!" << endl;
                    cout << "Tekan Enter untuk kembali...";
                    cin.ignore();
                    cin.get();
                }
                break;
                
            case 2:
                system("cls");
                cout << "=== CARI RESTORAN ===" << endl;
                cout << "Fitur pencarian akan segera hadir!" << endl;
                cout << "Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
                
            case 3:
                system("cls");
                cout << "=== KERANJANG BELANJA ===" << endl;
                cout << "Keranjang masih kosong!" << endl;
                cout << "Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
                
            case 4:
                return;
                
            default:
                cout << "Pilihan tidak valid, coba lagi!" << endl;
                cout << "Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
        }
    }
}

void menuMitraRestoran() {
    system("cls");
    cout << "=== MENU MITRA RESTORAN ===" << endl;
    cout << "Fitur mitra restoran akan segera hadir!" << endl;
    cout << "Tekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

void menuLogDriver() {
    system("cls");
    cout << "=== LOG DRIVER ===" << endl;
    cout << "Belum ada pesanan yang perlu diantar!" << endl;
    cout << "Tekan Enter untuk kembali...";
    cin.ignore();
    cin.get();
}

int main() {
    isiDataRestoran();
    int pilihan;
    
    while(true) {
        system("cls");
        tampilkanMenuUtama();
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                menuPelanggan();
                break;
                
            case 2:
                menuMitraRestoran();
                break;
                
            case 3:
                menuLogDriver();
                break;
                
            case 4:
                system("cls");
                cout << "Terima kasih telah menggunakan GrabFood!" << endl;
                cout << "Program selesai." << endl;
                return 0;
                
            default:
                cout << "Pilihan tidak valid, coba lagi!" << endl;
                cout << "Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
        }
    }
    
    return 0;
}