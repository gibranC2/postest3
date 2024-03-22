#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;

struct Book {
    string title;
    string author;
    int year;
};

struct User {
    string name;
    int nim;
};

void displayMenu() {
    cout << "\nMenu Perpustakaan:\n";
    cout << "1. Tambah Data Buku\n";
    cout << "2. Tampilkan Data Buku\n";
    cout << "3. Ubah Data Buku\n";
    cout << "4. Hapus Data Buku\n";
    cout << "5. Keluar\n";
}

// Fungsi untuk mengecek apakah user adalah admin
bool isAdmin(User user) {
    return (user.name == "gibran" && user.nim == 139);
}

// Fungsi rekursif untuk mencari indeks buku berdasarkan judul
int findBookIndex(Book books[], int numBooks, string title, int index = 0) {
    if (index >= numBooks) {
        return -1; // Buku tidak ditemukan
    }
    if (books[index].title == title) {
        return index; // Buku ditemukan
    }
    return findBookIndex(books, numBooks, title, index + 1); // Panggil rekursif untuk pencarian di indeks selanjutnya
}

int main() {
    User user;
    int loginAttempt = 0;

    // Login
    do {
        cout << "Masukkan Nama: ";
        cin >> user.name;
        cout << "Masukkan NIM: ";
        cin >> user.nim;
        loginAttempt++;
    } while (!isAdmin(user) && loginAttempt < 3);

    if (loginAttempt >= 3) {
        cout << "Anda telah salah login sebanyak 3 kali. Program berhenti.\n";
        return 0;
    }

    // Data buku
    Book books[MAX_BOOKS];
    int numBooks = 0;

    int choice;
    do {
        displayMenu();
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (numBooks < MAX_BOOKS) {
                    cout << "Masukkan judul buku: ";
                    cin.ignore();
                    getline(cin, books[numBooks].title);
                    cout << "Masukkan penulis buku: ";
                    getline(cin, books[numBooks].author);
                    cout << "Masukkan tahun terbit: ";
                    cin >> books[numBooks].year;
                    numBooks++;
                    cout << "Data buku berhasil ditambahkan.\n";
                } else {
                    cout << "Maaf, sudah mencapai batas maksimum data buku.\n";
                }
                break;
            case 2:
                if (numBooks > 0) {
                    cout << "Daftar Buku:\n";
                    for (int i = 0; i < numBooks; ++i) {
                        cout << i + 1 << ". " << books[i].title << " oleh " << books[i].author << " (" << books[i].year << ")\n";
                    }
                } else {
                    cout << "Belum ada data buku.\n";
                }
                break;
            case 3:
                // Ubah Data Buku
                if (numBooks > 0) {
                    string titleToModify;
                    cout << "Masukkan judul buku yang ingin diubah: ";
                    cin.ignore();
                    getline(cin, titleToModify);
                    int bookIndex = findBookIndex(books, numBooks, titleToModify);
                    if (bookIndex != -1) {
                        cout << "Masukkan judul baru: ";
                        getline(cin, books[bookIndex].title);
                        cout << "Masukkan penulis baru: ";
                        getline(cin, books[bookIndex].author);
                        cout << "Masukkan tahun terbit baru: ";
                        cin >> books[bookIndex].year;
                        cout << "Data buku berhasil diubah.\n";
                    } else {
                        cout << "Buku dengan judul tersebut tidak ditemukan.\n";
                    }
                } else {
                    cout << "Belum ada data buku.\n";
                }
                break;
            case 4:
                // Hapus Data Buku
                if (numBooks > 0) {
                    string titleToDelete;
                    cout << "Masukkan judul buku yang ingin dihapus: ";
                    cin.ignore();
                    getline(cin, titleToDelete);
                    int bookIndex = findBookIndex(books, numBooks, titleToDelete);
                    if (bookIndex != -1) {
                        // Geser semua buku setelah buku yang dihapus
                        for (int i = bookIndex; i < numBooks - 1; ++i) {
                            books[i] = books[i + 1];
                        }
                        numBooks--;
                        cout << "Data buku berhasil dihapus.\n";
                    } else {
                        cout << "Buku dengan judul tersebut tidak ditemukan.\n";
                    }
                } else {
                    cout << "Belum ada data buku.\n";
                }
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program perpustakaan.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 5);

    return 0;
}