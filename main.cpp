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

struct NodeKeranjang {
    string namaRestoran;
    string namaMakanan;
    int harga;
    int jumlah;
    NodeKeranjang* next;
    NodeKeranjang* prev;
};

struct Pesanan {
    string namaPelanggan;
    string namaRestoran;
    string daftarMakanan;
    int totalHarga;
    string status;
    int nomorPesanan;
};

struct NodeAntrean {
    Pesanan pesanan;
    NodeAntrean* next;
};

Restoran daftarRestoran[5];
int jumlahRestoran = 0;
NodeKeranjang* kepalaDaftarKeranjang = nullptr;
NodeKeranjang* ekorDaftarKeranjang = nullptr;
NodeAntrean* depanAntrean = nullptr;
NodeAntrean* belakangAntrean = nullptr;
int nomorPesananTerakhir = 0;

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

void urutkanRestoranBerdasarkanJarak() {
    for(int i = 0; i < jumlahRestoran - 1; i++) {
        for(int j = 0; j < jumlahRestoran - i - 1; j++) {
            if(daftarRestoran[j].jarak > daftarRestoran[j + 1].jarak) {
                Restoran temp = daftarRestoran[j];
                daftarRestoran[j] = daftarRestoran[j + 1];
                daftarRestoran[j + 1] = temp;
            }
        }
    }
}

void urutkanRestoranBerdasarkanRating() {
    for(int i = 0; i < jumlahRestoran - 1; i++) {
        for(int j = 0; j < jumlahRestoran - i - 1; j++) {
            if(daftarRestoran[j].rating < daftarRestoran[j + 1].rating) {
                Restoran temp = daftarRestoran[j];
                daftarRestoran[j] = daftarRestoran[j + 1];
                daftarRestoran[j + 1] = temp;
            }
        }
    }
}

int cariRestoran(string namaRestoran) {
    for(int i = 0; i < jumlahRestoran; i++) {
        if(daftarRestoran[i].nama.find(namaRestoran) != string::npos) {
            return i;
        }
    }
    return -1;
}

int cariMakanan(int indeksRestoran, string namaMakanan) {
    if(indeksRestoran < 0 || indeksRestoran >= jumlahRestoran) {
        return -1;
    }
    
    for(int i = 0; i < daftarRestoran[indeksRestoran].jumlahMenu; i++) {
        if(daftarRestoran[indeksRestoran].menu[i].nama.find(namaMakanan) != string::npos) {
            return i;
        }
    }
    return -1;
}

void tambahKeKeranjang(string namaRestoran, string namaMakanan, int harga, int jumlah) {
    NodeKeranjang* nodeBaru = new NodeKeranjang;
    nodeBaru->namaRestoran = namaRestoran;
    nodeBaru->namaMakanan = namaMakanan;
    nodeBaru->harga = harga;
    nodeBaru->jumlah = jumlah;
    nodeBaru->next = nullptr;
    nodeBaru->prev = nullptr;
    
    if(kepalaDaftarKeranjang == nullptr) {
        kepalaDaftarKeranjang = nodeBaru;
        ekorDaftarKeranjang = nodeBaru;
    } else {
        ekorDaftarKeranjang->next = nodeBaru;
        nodeBaru->prev = ekorDaftarKeranjang;
        ekorDaftarKeranjang = nodeBaru;
    }
}

void hapusDariKeranjang(int urutan) {
    if(kepalaDaftarKeranjang == nullptr) {
        return;
    }
    
    NodeKeranjang* current = kepalaDaftarKeranjang;
    int hitungan = 1;
    
    while(current != nullptr && hitungan != urutan) {
        current = current->next;
        hitungan++;
    }
    
    if(current == nullptr) {
        return;
    }
    
    if(current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        kepalaDaftarKeranjang = current->next;
    }
    
    if(current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        ekorDaftarKeranjang = current->prev;
    }
    
    delete current;
}

void masukkanKeAntreanDapur(string namaPelanggan) {
    if(kepalaDaftarKeranjang == nullptr) {
        cout << "Keranjang kosong, tidak bisa checkout!" << endl;
        return;
    }
    
    NodeAntrean* pesananBaru = new NodeAntrean;
    pesananBaru->pesanan.namaPelanggan = namaPelanggan;
    pesananBaru->pesanan.nomorPesanan = ++nomorPesananTerakhir;
    pesananBaru->pesanan.status = "Sedang Dimasak";
    pesananBaru->pesanan.totalHarga = 0;
    pesananBaru->pesanan.daftarMakanan = "";
    pesananBaru->next = nullptr;
    
    NodeKeranjang* current = kepalaDaftarKeranjang;
    string restoranPertama = current->namaRestoran;
    pesananBaru->pesanan.namaRestoran = restoranPertama;
    
    while(current != nullptr) {
        if(current->namaRestoran == restoranPertama) {
            pesananBaru->pesanan.daftarMakanan += current->namaMakanan;
            pesananBaru->pesanan.daftarMakanan += " x" + to_string(current->jumlah);
            pesananBaru->pesanan.totalHarga += (current->harga * current->jumlah);
            
            if(current->next != nullptr && current->next->namaRestoran == restoranPertama) {
                pesananBaru->pesanan.daftarMakanan += ", ";
            }
        }
        current = current->next;
    }
    
    if(depanAntrean == nullptr) {
        depanAntrean = pesananBaru;
        belakangAntrean = pesananBaru;
    } else {
        belakangAntrean->next = pesananBaru;
        belakangAntrean = pesananBaru;
    }
    
    hapusSemuaKeranjang();
    
    cout << "Pesanan berhasil masuk ke antrean dapur!" << endl;
    cout << "Nomor pesanan: " << pesananBaru->pesanan.nomorPesanan << endl;
    cout << "Restoran: " << pesananBaru->pesanan.namaRestoran << endl;
}

void hapusSemuaKeranjang() {
    while(kepalaDaftarKeranjang != nullptr) {
        NodeKeranjang* temp = kepalaDaftarKeranjang;
        kepalaDaftarKeranjang = kepalaDaftarKeranjang->next;
        delete temp;
    }
    ekorDaftarKeranjang = nullptr;
}

void selesaikanPesananPertama() {
    if(depanAntrean == nullptr) {
        cout << "Tidak ada pesanan dalam antrean!" << endl;
        return;
    }
    
    NodeAntrean* pesananSelesai = depanAntrean;
    depanAntrean = depanAntrean->next;
    
    if(depanAntrean == nullptr) {
        belakangAntrean = nullptr;
    }
    
    cout << "Pesanan #" << pesananSelesai->pesanan.nomorPesanan;
    cout << " (" << pesananSelesai->pesanan.namaPelanggan << ") telah selesai!" << endl;
    
    delete pesananSelesai;
}

void tampilkanAntreanDapur() {
    if(depanAntrean == nullptr) {
        cout << "Antrean dapur kosong!" << endl;
        return;
    }
    
    cout << "=== ANTREAN DAPUR ===" << endl;
    NodeAntrean* current = depanAntrean;
    int urutan = 1;
    
    while(current != nullptr) {
        cout << urutan << ". Pesanan #" << current->pesanan.nomorPesanan << endl;
        cout << "   Pelanggan: " << current->pesanan.namaPelanggan << endl;
        cout << "   Restoran: " << current->pesanan.namaRestoran << endl;
        cout << "   Makanan: " << current->pesanan.daftarMakanan << endl;
        cout << "   Total: Rp " << current->pesanan.totalHarga << endl;
        cout << "   Status: " << current->pesanan.status << endl;
        cout << endl;
        
        current = current->next;
        urutan++;
    }
}

void tampilkanKeranjang() {
    if(kepalaDaftarKeranjang == nullptr) {
        cout << "Keranjang masih kosong!" << endl;
        return;
    }
    
    cout << "=== KERANJANG BELANJA ===" << endl;
    NodeKeranjang* current = kepalaDaftarKeranjang;
    int urutan = 1;
    int totalHarga = 0;
    
    while(current != nullptr) {
        cout << urutan << ". " << current->namaMakanan;
        cout << " (" << current->namaRestoran << ")";
        cout << " - Rp " << current->harga;
        cout << " x " << current->jumlah;
        cout << " = Rp " << (current->harga * current->jumlah) << endl;
        
        totalHarga += (current->harga * current->jumlah);
        current = current->next;
        urutan++;
    }
    
    cout << endl;
    cout << "Total: Rp " << totalHarga << endl;
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
    
    cout << endl;
    cout << "Pilih makanan untuk ditambah ke keranjang (0 untuk kembali): ";
    int pilihanMakanan;
    cin >> pilihanMakanan;
    
    if(pilihanMakanan >= 1 && pilihanMakanan <= daftarRestoran[indeks].jumlahMenu) {
        if(daftarRestoran[indeks].menu[pilihanMakanan - 1].tersedia) {
            cout << "Jumlah porsi: ";
            int jumlah;
            cin >> jumlah;
            
            if(jumlah > 0) {
                tambahKeKeranjang(
                    daftarRestoran[indeks].nama,
                    daftarRestoran[indeks].menu[pilihanMakanan - 1].nama,
                    daftarRestoran[indeks].menu[pilihanMakanan - 1].harga,
                    jumlah
                );
                cout << "Berhasil ditambahkan ke keranjang!" << endl;
            } else {
                cout << "Jumlah tidak valid!" << endl;
            }
        } else {
            cout << "Maaf, makanan ini sedang habis!" << endl;
        }
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
                cout << "1. Urutkan berdasarkan jarak terdekat" << endl;
                cout << "2. Urutkan berdasarkan rating tertinggi" << endl;
                cout << "3. Cari restoran berdasarkan nama" << endl;
                cout << "4. Kembali" << endl;
                cout << endl;
                cout << "Pilih menu: ";
                
                int pilihanCari;
                cin >> pilihanCari;
                
                switch(pilihanCari) {
                    case 1:
                        system("cls");
                        urutkanRestoranBerdasarkanJarak();
                        cout << "=== RESTORAN DIURUTKAN BERDASARKAN JARAK ===" << endl;
                        tampilkanDaftarRestoran();
                        cout << "Tekan Enter untuk kembali...";
                        cin.ignore();
                        cin.get();
                        break;
                        
                    case 2:
                        system("cls");
                        urutkanRestoranBerdasarkanRating();
                        cout << "=== RESTORAN DIURUTKAN BERDASARKAN RATING ===" << endl;
                        tampilkanDaftarRestoran();
                        cout << "Tekan Enter untuk kembali...";
                        cin.ignore();
                        cin.get();
                        break;
                        
                    case 3:
                        system("cls");
                        cout << "Masukkan nama restoran yang dicari: ";
                        string kataCari;
                        cin.ignore();
                        getline(cin, kataCari);
                        
                        int hasilCari = cariRestoran(kataCari);
                        if(hasilCari != -1) {
                            cout << "Restoran ditemukan!" << endl;
                            cout << "Nama: " << daftarRestoran[hasilCari].nama << endl;
                            cout << "Jarak: " << daftarRestoran[hasilCari].jarak << " km" << endl;
                            cout << "Rating: " << daftarRestoran[hasilCari].rating << "/5" << endl;
                        } else {
                            cout << "Restoran tidak ditemukan!" << endl;
                        }
                        cout << "Tekan Enter untuk kembali...";
                        cin.get();
                        break;
                        
                    case 4:
                        break;
                        
                    default:
                        cout << "Pilihan tidak valid!" << endl;
                        cout << "Tekan Enter untuk kembali...";
                        cin.ignore();
                        cin.get();
                        break;
                }
                break;
                
            case 3:
                system("cls");
                tampilkanKeranjang();
                
                if(kepalaDaftarKeranjang != nullptr) {
                    cout << endl;
                    cout << "1. Hapus item dari keranjang" << endl;
                    cout << "2. Checkout" << endl;
                    cout << "3. Kembali" << endl;
                    cout << "Pilih menu: ";
                    
                    int pilihanKeranjang;
                    cin >> pilihanKeranjang;
                    
                    switch(pilihanKeranjang) {
                        case 1:
                            cout << "Masukkan nomor item yang ingin dihapus: ";
                            int nomorHapus;
                            cin >> nomorHapus;
                            hapusDariKeranjang(nomorHapus);
                            cout << "Item berhasil dihapus!" << endl;
                            cout << "Tekan Enter untuk kembali...";
                            cin.ignore();
                            cin.get();
                            break;
                            
                        case 2:
                            cout << "Masukkan nama pelanggan: ";
                            string namaPelanggan;
                            cin.ignore();
                            getline(cin, namaPelanggan);
                            
                            masukkanKeAntreanDapur(namaPelanggan);
                            cout << "Tekan Enter untuk kembali...";
                            cin.get();
                            break;
                            
                        case 3:
                            break;
                            
                        default:
                            cout << "Pilihan tidak valid!" << endl;
                            cout << "Tekan Enter untuk kembali...";
                            cin.ignore();
                            cin.get();
                            break;
                    }
                } else {
                    cout << "Tekan Enter untuk kembali...";
                    cin.ignore();
                    cin.get();
                }
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
    int pilihan;
    
    while(true) {
        system("cls");
        cout << "=== MENU MITRA RESTORAN ===" << endl;
        cout << "1. Lihat Antrean Dapur" << endl;
        cout << "2. Selesaikan Pesanan Pertama" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                system("cls");
                tampilkanAntreanDapur();
                cout << "Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
                
            case 2:
                system("cls");
                selesaikanPesananPertama();
                cout << "Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
                break;
                
            case 3:
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

void menuLogDriver() {
    system("cls");
    cout << "=== LOG DRIVER ===" << endl;
    
    if(depanAntrean == nullptr) {
        cout << "Belum ada pesanan yang perlu diantar!" << endl;
    } else {
        cout << "Pesanan yang siap untuk diantar:" << endl;
        cout << "Silakan cek dengan mitra restoran untuk pesanan yang sudah selesai." << endl;
        cout << endl;
        tampilkanAntreanDapur();
    }
    
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