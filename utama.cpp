#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <windows.h>
#include <cctype>
using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void tampilkanLogoKecil()
{
    cout << "\n";
    cout << "====================================================\n";
    cout << "||               STUDIO PILATES MANIAK            ||\n";
    cout << "====================================================\n";
}

void loadingAnimation()
{
    setColor(14);
    cout << "\nLoading";
    for (int i = 0; i < 5; i++)
    {
        Sleep(200);
        cout << ".";
        cout.flush();
    }
    cout << "\n";
    setColor(7);
}

void countdown(int detik)
{
    setColor(12);
    cout << "\nTerlalu banyak percobaan gagal!\n";
    setColor(14);
    cout << "Silakan tunggu ";
    for (int i = detik; i > 0; i--)
    {
        cout << i << "...";
        cout.flush();
        Sleep(1000);
    }
    cout << "\n\n";
    setColor(7);
}

int inputInteger(const string &prompt)
{
    int nilai;
    cout << prompt;
    cin >> nilai;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        throw invalid_argument("Input tidak valid! Harus berupa angka.");
    }
    return nilai;
}

void validasiUsernameHuruf(const string &nama)
{
    if (nama.empty() || nama == " ")
        throw invalid_argument("Username tidak boleh kosong!");

    if (nama.length() < 4)
        throw invalid_argument("Username minimal 4 karakter!");
    for (int i = 0; i < nama.length(); i++)
    {
        if (!isalpha(nama[i]) && nama[i] != ' ')
        {
            throw invalid_argument("Username hanya boleh huruf dan spasi!");
        }
    }

    bool semuaSpasi = true;
    for (int i = 0; i < nama.length(); i++)
    {
        if (nama[i] != ' ')
        {
            semuaSpasi = false;
            break;
        }
    }

    if (semuaSpasi)
        throw invalid_argument("Username tidak boleh hanya berisi spasi!");
}

void validasiHari(const string &hari)
{
    if (hari.empty())
        throw invalid_argument("Hari tidak boleh kosong!");

    for (int i = 0; i < hari.length(); i++)
    {
        if (!isalpha(hari[i]) && hari[i] != ' ')
        {
            throw invalid_argument("Hari hanya boleh berisi huruf!");
        }
    }
}

void validasiJam(const string &jam)
{
    if (jam.empty())
        throw invalid_argument("Jam tidak boleh kosong!");

    for (int i = 0; i < jam.length(); i++)
    {
        if (!isdigit(jam[i]) && jam[i] != ':' && jam[i] != '-' && jam[i] != ' ')
        {
            throw invalid_argument("Format jam tidak valid! Gunakan format: 08:00 - 09:00");
        }
    }
}

void validasiTeksHuruf(const string &teks, const string &namaField)
{
    if (teks.empty())
        throw invalid_argument(namaField + " tidak boleh kosong!");

    for (int i = 0; i < teks.length(); i++)
    {
        if (!isalpha(teks[i]) && teks[i] != ' ')
        {
            throw invalid_argument(namaField + " hanya boleh berisi huruf dan spasi!");
        }
    }
}

void validasiPassword(const string &pw)
{
    if (pw.empty())
        throw invalid_argument("Password tidak boleh kosong!");
    if ((int)pw.length() < 3)
        throw length_error("Password terlalu pendek! Minimal 3 karakter.");
}

void validasiKapasitas(int jumlah, int maxKapasitas)
{
    if (jumlah >= maxKapasitas)
        throw length_error("Kapasitas penuh! Tidak dapat menambah data.");
}

void validasiID(int id)
{
    if (id <= 0)
        throw out_of_range("ID tidak valid! Harus berupa angka positif.");
}

string formatRupiah(int harga)
{
    stringstream ss;
    ss << "Rp " << harga;
    return ss.str();
}

struct Akun
{
    string nama;
    string pw;
    string role;
    int id;
    int saldo;
};

struct JadwalKelas
{
    int jadwalID;
    string hari;
    string jam;
    string jenisKelas;
    string kategori;
    string instruktur;
    int harga;
    int kapasitas;
    int terisi;
};

struct Booking
{
    int bookingID;
    string namaMember;
    int memberID;
    int jadwalID;
    string jenisKelas;
    int harga;
    string status;
};

struct TopUp
{
    string namaMember;
    int nominal;
};

int cariusername(Akun *data, int jumlah, string targetNama, int index = 0)
{
    if (index >= jumlah)
        return -1;
    if (data[index].nama == targetNama)
        return index;
    return cariusername(data, jumlah, targetNama, index + 1);
}

int cariID(Akun *data, int jumlah, int targetID)
{
    for (int i = 0; i < jumlah; i++)
        if (data[i].role == "member" && data[i].id == targetID)
            return i;
    return -1;
}

void tampilkanDaftarMember(Akun *data, int jumlah)
{

    int wID = 2, wNama = 4, wSaldo = 5; 
    int jmlMember = 0;

    for (int i = 0; i < jumlah; i++)
    {
        if (data[i].role == "member")
        {
            jmlMember++;
            string idStr = to_string(data[i].id);
            string namaStr = data[i].nama;
            string saldoStr = formatRupiah(data[i].saldo);

            if (idStr.length() > wID) wID = idStr.length();
            if (namaStr.length() > wNama) wNama = namaStr.length();
            if (saldoStr.length() > wSaldo) wSaldo = saldoStr.length();
        }
    }
    wID += 2; wNama += 2; wSaldo += 2; 
    int totalLebar = wID + wNama + wSaldo;

    cout << "\n";
    cout << string(totalLebar, '=') << "\n";
    cout << "||" << setw(totalLebar - 4) << setfill(' ') << left << " DAFTAR MEMBER TERDAFTAR " << "||\n";
    cout << string(totalLebar, '=') << "\n";

    cout << left << setfill(' ')
         << setw(wID) << "ID"
         << setw(wNama) << "Nama"
         << setw(wSaldo) << "Saldo" << "\n";
    cout << string(totalLebar, '-') << "\n";

    if (jmlMember == 0)
    {
        cout << setw(totalLebar) << "Belum ada data member terdaftar !" << "\n";
    }
    else
    {
        for (int i = 0; i < jumlah; i++)
        {
            if (data[i].role == "member")
            {
                cout << left
                     << setw(wID) << data[i].id
                     << setw(wNama) << data[i].nama
                     << setw(wSaldo) << formatRupiah(data[i].saldo) << "\n";
            }
        }
    }
    cout << string(totalLebar, '=') << "\n";
}

void tampilkanDaftarJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    // Lebar inisialisasi dari judul kolom
    int wID=2, wHari=4, wJam=3, wJenis=5, wKategori=8, wInstruktur=10, wHarga=5, wKapas=9;
    
    // Pass 1: Hitung lebar maksimal
    for (int i = 0; i < jumlahJadwal; i++)
    {
        string idStr = to_string(dataJadwal[i].jadwalID);
        string kapStr = to_string(dataJadwal[i].terisi) + "/" + 
                        to_string(dataJadwal[i].kapasitas) + 
                        " (sisa " + to_string(dataJadwal[i].kapasitas - dataJadwal[i].terisi) + ")";
        
        if (idStr.length() > wID) wID = idStr.length();
        if (dataJadwal[i].hari.length() > wHari) wHari = dataJadwal[i].hari.length();
        if (dataJadwal[i].jam.length() > wJam) wJam = dataJadwal[i].jam.length();
        if (dataJadwal[i].jenisKelas.length() > wJenis) wJenis = dataJadwal[i].jenisKelas.length();
        if (dataJadwal[i].kategori.length() > wKategori) wKategori = dataJadwal[i].kategori.length();
        if (dataJadwal[i].instruktur.length() > wInstruktur) wInstruktur = dataJadwal[i].instruktur.length();
        string hargaStr = formatRupiah(dataJadwal[i].harga);
        if (hargaStr.length() > wHarga) wHarga = hargaStr.length();
        if (kapStr.length() > wKapas) wKapas = kapStr.length();
    }
    
    // Padding +2 tiap kolom
    wID+=2; wHari+=2; wJam+=2; wJenis+=2; wKategori+=2; wInstruktur+=2; wHarga+=2; wKapas+=2;
    int totalLebar = wID + wHari + wJam + wJenis + wKategori + wInstruktur + wHarga + wKapas;

    cout << "\n";
    cout << string(totalLebar, '=') << "\n";
    cout << "||" << setw(totalLebar - 4) << setfill(' ') << left << " DAFTAR JADWAL KELAS " << "||\n";
    cout << string(totalLebar, '=') << "\n";

    cout << left << setfill(' ')
         << setw(wID) << "ID"
         << setw(wHari) << "Hari"
         << setw(wJam) << "Jam"
         << setw(wJenis) << "Jenis"
         << setw(wKategori) << "Kategori"
         << setw(wInstruktur) << "Instruktur"
         << setw(wHarga) << "Harga"
         << setw(wKapas) << "Kapasitas" << "\n";
    cout << string(totalLebar, '-') << "\n";

    if (jumlahJadwal == 0)
    {
        cout << setw(totalLebar) << "Belum ada data jadwal !" << "\n";
    }
    else
    {
        for (int i = 0; i < jumlahJadwal; i++)
        {
            string infoKapasitas = to_string(dataJadwal[i].terisi) + "/" + 
                                   to_string(dataJadwal[i].kapasitas) + 
                                   " (sisa " + to_string(dataJadwal[i].kapasitas - dataJadwal[i].terisi) + ")";
            cout << left
                 << setw(wID) << dataJadwal[i].jadwalID
                 << setw(wHari) << dataJadwal[i].hari
                 << setw(wJam) << dataJadwal[i].jam
                 << setw(wJenis) << dataJadwal[i].jenisKelas
                 << setw(wKategori) << dataJadwal[i].kategori
                 << setw(wInstruktur) << dataJadwal[i].instruktur
                 << setw(wHarga) << formatRupiah(dataJadwal[i].harga)
                 << setw(wKapas) << infoKapasitas << "\n";
        }
    }
    cout << string(totalLebar, '=') << "\n";
}

void login(Akun *data, int jumlah, bool &statusLogin, string &namaLogin, string &roleLogin)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||                >> LOGIN SYSTEM <<              ||\n";
    cout << "====================================================\n";
    string inputNama, inputpw;
    int kesempatan = 3;
    cin.ignore(1000, '\n');

    while (kesempatan > 0)
    {
        try
        {
            bool usernameValid = false;
            while (!usernameValid)
            {
                try
                {
                    cout << "Masukkan Username : ";
                    getline(cin, inputNama);
                    validasiUsernameHuruf(inputNama);
                    usernameValid = true;
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << "\n";
                    cout << "Silakan masukkan username kembali.\n\n";
                }
            }

            cout << "Masukkan Password : ";
            cin >> inputpw;
            int index = cariusername(data, jumlah, inputNama);
            if (index != -1 && data[index].pw == inputpw)
            {
                statusLogin = true;
                namaLogin = data[index].nama;
                roleLogin = data[index].role;

                loadingAnimation();
                cout << "Login berhasil!\n";
                cout << "Selamat datang, " << namaLogin << " (" << roleLogin << ")!\n\n";
                system("pause");
                return;
            }
            else
            {
                kesempatan--;
                cout << "\nLogin Gagal! Username atau Password salah.\n";
                if (kesempatan > 0)
                {
                    cout << "Sisa kesempatan: " << kesempatan << "\n\n";
                }
                else
                {
                    cout << "\nKesempatan Anda Habis!\n";
                    countdown(5);
                    system("pause");
                }
            }
        }
        catch (const exception &e)
        {
            cout << endl
                 << e.what() << "\n";
            kesempatan--;
            if (kesempatan > 0)
                cout << "Sisa kesempatan: " << kesempatan << "\n";
            else
            {
                cout << "Kesempatan Habis.\n";
                countdown(5);
                system("pause");
            }
        }
    }
}

void registrasi(Akun *data, int &jumlah, int maxKapasitas)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||            >> REGISTRASI AKUN BARU <<          ||\n";
    cout << "====================================================\n";
    cin.ignore(1000, '\n');
    try
    {
        validasiKapasitas(jumlah, maxKapasitas);
        string namaBaru, pwBaru;

        cout << "Masukkan Username : ";
        getline(cin, namaBaru);

        validasiUsernameHuruf(namaBaru);

        if (cariusername(data, jumlah, namaBaru) != -1)
            throw runtime_error("Username sudah terdaftar. Gunakan username lain.");

        cout << "Masukkan Password : ";
        cin >> pwBaru;
        validasiPassword(pwBaru);

        int newID = 1;
        for (int i = 0; i < jumlah; i++)
            if (data[i].role == "member" && data[i].id >= newID)
                newID = data[i].id + 1;

        data[jumlah].nama = namaBaru;
        data[jumlah].pw = pwBaru;
        data[jumlah].role = "member";
        data[jumlah].id = newID;
        data[jumlah].saldo = 0;
        jumlah++;

        loadingAnimation();
        cout << "Registrasi Berhasil! Silakan Login.\n";
        cout << "ID Anda: " << newID << "\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void tambahMember(Akun *data, int &jumlah, int maxKapasitas)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||             >> TAMBAH MEMBER BARU <<           ||\n";
    cout << "====================================================\n";
    cin.ignore(1000, '\n');
    try
    {
        validasiKapasitas(jumlah, maxKapasitas);
        string namaBaru, pwBaru;
        cout << "Masukkan Nama Member : ";
        getline(cin, namaBaru);

        validasiUsernameHuruf(namaBaru);

        if (cariusername(data, jumlah, namaBaru) != -1)
            throw runtime_error("Username sudah terdaftar.");

        cout << "Masukkan Password Member : ";
        cin >> pwBaru;
        validasiPassword(pwBaru);

        int newID = 1;
        for (int i = 0; i < jumlah; i++)
            if (data[i].role == "member" && data[i].id >= newID)
                newID = data[i].id + 1;

        data[jumlah].nama = namaBaru;
        data[jumlah].pw = pwBaru;
        data[jumlah].role = "member";
        data[jumlah].id = newID;
        data[jumlah].saldo = 0;
        jumlah++;

        loadingAnimation();
        cout << "Member Berhasil Ditambahkan!\n";
        cout << "ID Member: " << newID << "\n\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void lihatMember(Akun *data, int jumlah)
{
    bool kembali = false;
    while (!kembali)
    {
        system("cls");
        tampilkanLogoKecil();
        cout << "====================================================\n";
        cout << "||             >> LIHAT DATA MEMBER <<            ||\n";
        cout << "====================================================\n";
        cout << "1. Urutkan Nama (Selection Sort)\n";
        cout << "2. Cari Member Berdasarkan ID (Linear Search)\n";
        cout << "0. Kembali\n";
        cout << "----------------------------------------------------\n";

        try
        {
            int pilihan = inputInteger("Pilih menu (0-2): ");

            if (pilihan == 0)
            {
                kembali = true;
                continue;
            }
            Akun temp[20];
            int memberCount = 0;
            for (int i = 0; i < jumlah; i++)
                if (data[i].role == "member")
                    temp[memberCount++] = data[i];

            if (memberCount == 0)
                throw runtime_error("Belum ada data member.");

            system("cls");
            if (pilihan == 1)
            {
                for (int i = 0; i < memberCount - 1; i++)
                {
                    int minIndex = i;
                    for (int j = i + 1; j < memberCount; j++)
                        if (temp[j].nama < temp[minIndex].nama)
                            minIndex = j;

                    if (minIndex != i)
                        swap(temp[i], temp[minIndex]);
                }
                tampilkanLogoKecil();
                cout << "\n===========================================================\n";
                cout << "||            >> DAFTAR MEMBER (TERURUT) <<              ||\n";
                cout << "===========================================================\n";
                cout << left << setw(8) << "ID" << setw(20) << "Nama" << setw(20) << "Saldo" << endl;
                cout << "-----------------------------------------------------------\n";

                for (int i = 0; i < memberCount; i++)
                    cout << left << setw(8) << temp[i].id
                         << setw(20) << temp[i].nama
                         << setw(20) << formatRupiah(temp[i].saldo) << "\n";

                cout << "===========================================================\n\n";
            }

            else if (pilihan == 2)
            {
                tampilkanLogoKecil();
                cout << "====================================================\n";
                cout << "||         >> CARI MEMBER BERDASARKAN ID <<       ||\n";
                cout << "====================================================\n";

                tampilkanDaftarMember(data, jumlah);

                int targetID;
                while (true)
                {
                    try
                    {
                        targetID = inputInteger("\nMasukkan ID yang dicari: ");
                        validasiID(targetID);
                        break;
                    }
                    catch (const exception &e)
                    {
                        cout << endl
                             << e.what() << " Silakan coba lagi.\n";
                    }
                }
                cout << "\nTarget ID: " << targetID << endl;
                cout << "-----------------------------------\n";

                int hasil = -1, jumlahCek = 0;
                for (int i = 0; i < jumlah && hasil == -1; i++)
                {
                    if (data[i].role == "member")
                    {
                        jumlahCek++;
                        cout << "Cek member ke-" << jumlahCek << ": ID " << data[i].id;

                        if (data[i].id == targetID)
                        {
                            cout << " >>> COCOK!\n";
                            hasil = i;
                        }
                        else
                            cout << " (tidak cocok)\n";
                    }
                }
                cout << "-----------------------------------\n";

                if (hasil != -1)
                {
                    cout << "Ditemukan setelah " << jumlahCek << " pengecekan!\n\n";
                    cout << "====================================================\n";
                    cout << "||             >> MEMBER DITEMUKAN! <<            ||\n";
                    cout << "====================================================\n";
                    cout << "ID       : " << data[hasil].id << endl;
                    cout << "Nama     : " << data[hasil].nama << endl;
                    cout << "Saldo    : " << formatRupiah(data[hasil].saldo) << endl;
                    cout << "====================================================\n";
                }
                else
                    cout << "Member dengan ID " << targetID << " tidak ditemukan!\n";

                cout << "\n";
            }
            else
                throw out_of_range("Pilihan tidak valid!");

            system("pause");
        }
        catch (const exception &e)
        {
            cout << endl
                 << e.what() << "\n\n";
            system("pause");
        }
    }
}

void hapusMember(Akun *data, int &jumlah)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||               >> HAPUS MEMBER <<               ||\n";
    cout << "====================================================\n";
    tampilkanDaftarMember(data, jumlah);

    try
    {
        int IDHapus = inputInteger("\nMasukkan ID member yang ingin dihapus: ");
        validasiID(IDHapus);

        int index = cariID(data, jumlah, IDHapus);
        if (index == -1)
            throw runtime_error("Member dengan ID tersebut tidak ditemukan!");
        cout << "\nMenghapus member: " << data[index].nama << "\n";

        for (int j = index; j < jumlah - 1; j++)
            data[j] = data[j + 1];
        jumlah--;

        loadingAnimation();
        cout << "Data member berhasil dihapus!\n\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void tambahJadwal(JadwalKelas *dataJadwal, int &jumlahJadwal, int maxJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||            >> TAMBAH JADWAL KELAS <<           ||\n";
    cout << "====================================================\n";

    if (jumlahJadwal >= maxJadwal)
    {
        cout << "Kuota penyimpanan jadwal penuh!\n\n";
        return;
    }

    try
    {
        cin.ignore(1000, '\n');

        string hariInput;
        cout << "\nHari (Senin/Selasa/Rabu/Kamis/Jumat/Sabtu/Minggu): ";
        getline(cin, hariInput);
        validasiHari(hariInput);

        string jamInput;
        cout << "Jam (contoh: 08:00 - 09:00): ";
        getline(cin, jamInput);
        validasiJam(jamInput);

        string jenisInput;
        cout << "Jenis Kelas (contoh: Mat Pilates, Reformer, dll): ";
        getline(cin, jenisInput);
        validasiTeksHuruf(jenisInput, "Jenis kelas");

        string kategoriInput;
        cout << "Kategori (Private/Reguler): ";
        getline(cin, kategoriInput);
        validasiTeksHuruf(kategoriInput, "Kategori");

        string instrukturInput;
        cout << "Instruktur: ";
        getline(cin, instrukturInput);
        validasiTeksHuruf(instrukturInput, "Instruktur");

        int hargaInput;
        bool validHarga = false;
        while (!validHarga)
        {
            try
            {
                cout << "Harga Kelas: Rp ";
                cin >> hargaInput;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    throw invalid_argument("Input harga tidak valid!");
                }
                if (hargaInput <= 0)
                    throw invalid_argument("Harga harus lebih dari 0!");
                validHarga = true;
            }
            catch (const exception &e)
            {
                cout << endl
                     << e.what() << " Silakan coba lagi.\n";
            }
        }

        int kapasitasInput = inputInteger("Kapasitas Peserta: ");
        if (kapasitasInput <= 0)
            throw invalid_argument("Kapasitas harus lebih dari 0!");

        int newID = 1;
        for (int i = 0; i < jumlahJadwal; i++)
            if (dataJadwal[i].jadwalID >= newID)
                newID = dataJadwal[i].jadwalID + 1;

        dataJadwal[jumlahJadwal].jadwalID = newID;
        dataJadwal[jumlahJadwal].hari = hariInput;
        dataJadwal[jumlahJadwal].jam = jamInput;
        dataJadwal[jumlahJadwal].jenisKelas = jenisInput;
        dataJadwal[jumlahJadwal].kategori = kategoriInput;
        dataJadwal[jumlahJadwal].instruktur = instrukturInput;
        dataJadwal[jumlahJadwal].harga = hargaInput;
        dataJadwal[jumlahJadwal].kapasitas = kapasitasInput;
        dataJadwal[jumlahJadwal].terisi = 0;
        jumlahJadwal++;

        loadingAnimation();
        cout << "Jadwal berhasil ditambahkan!\n";
        cout << "ID Jadwal: " << newID << "\n\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void lihatJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||            >> LIHAT JADWAL KELAS <<            ||\n";
    cout << "====================================================\n";

    tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);
}

void updateJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||            >> UPDATE JADWAL KELAS <<           ||\n";
    cout << "====================================================\n";

    if (jumlahJadwal == 0)
    {
        cout << "Data jadwal masih kosong!\n\n";
        return;
    }

    tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);
    cout << "\n";

    int idCari = inputInteger("Masukkan ID Jadwal yang ingin diubah: ");
    bool ditemukan = false;

    for (int i = 0; i < jumlahJadwal; i++)
    {
        if (dataJadwal[i].jadwalID == idCari)
        {
            ditemukan = true;
            cout << "\n    --- MASUKKAN DATA BARU ---\n";
            cin.ignore(1000, '\n');
            string inputBaru;

            cout << "Hari (sekarang: " << dataJadwal[i].hari << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiHari(inputBaru);
                dataJadwal[i].hari = inputBaru;
            }

            cout << "Jam (sekarang: " << dataJadwal[i].jam << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiJam(inputBaru);
                dataJadwal[i].jam = inputBaru;
            }

            cout << "Jenis Kelas (sekarang: " << dataJadwal[i].jenisKelas << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiTeksHuruf(inputBaru, "Jenis kelas");
                dataJadwal[i].jenisKelas = inputBaru;
            }

            cout << "Kategori (sekarang: " << dataJadwal[i].kategori << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiTeksHuruf(inputBaru, "Kategori");
                dataJadwal[i].kategori = inputBaru;
            }

            cout << "Instruktur (sekarang: " << dataJadwal[i].instruktur << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiTeksHuruf(inputBaru, "Instruktur");
                dataJadwal[i].instruktur = inputBaru;
            }

            cout << "Harga (sekarang: " << formatRupiah(dataJadwal[i].harga) << "): Rp ";
            string hargaStr;
            getline(cin, hargaStr);
            if (!hargaStr.empty())
            {
                int hargaBaru = stoi(hargaStr);
                if (hargaBaru > 0)
                    dataJadwal[i].harga = hargaBaru;
            }

            cout << "Kapasitas (sekarang: " << dataJadwal[i].kapasitas << "): ";
            string kapasitasStr;
            getline(cin, kapasitasStr);
            if (!kapasitasStr.empty())
            {
                int kapasitasBaru = stoi(kapasitasStr);
                if (kapasitasBaru > 0)
                    dataJadwal[i].kapasitas = kapasitasBaru;
            }

            loadingAnimation();
            cout << "Data Jadwal Berhasil Diperbarui!\n\n";
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "\nID Jadwal tidak ditemukan.\n\n";
    }
}

void hapusJadwal(JadwalKelas *dataJadwal, int &jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||            >> HAPUS JADWAL KELAS <<            ||\n";
    cout << "====================================================\n";

    if (jumlahJadwal == 0)
    {
        cout << "Data jadwal masih kosong!\n\n";
        return;
    }

    tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);
    cout << "\n";

    int idCari = inputInteger("Masukkan ID Jadwal yang ingin dihapus: ");
    int indexKetemu = -1;

    for (int i = 0; i < jumlahJadwal; i++)
    {
        if (dataJadwal[i].jadwalID == idCari)
        {
            indexKetemu = i;
            break;
        }
    }

    if (indexKetemu != -1)
    {
        cout << "\nMenghapus jadwal: " << dataJadwal[indexKetemu].jenisKelas
             << " (" << dataJadwal[indexKetemu].kategori << ")"
             << " - " << dataJadwal[indexKetemu].hari
             << " " << dataJadwal[indexKetemu].jam << "\n";

        for (int i = indexKetemu; i < jumlahJadwal - 1; i++)
            dataJadwal[i] = dataJadwal[i + 1];
        jumlahJadwal--;

        loadingAnimation();
        cout << "Jadwal Berhasil Dihapus!\n\n";
    }
    else
    {
        cout << "\nID tidak ditemukan.\n\n";
    }
}

void approvalBooking(Booking *dataBooking, int jumlahBooking, Akun *dataAkun, int jumlahAkun)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||              >> APPROVAL BOOKING <<            ||\n";
    cout << "====================================================\n";

    if (jumlahBooking == 0)
    {
        cout << "Belum ada data booking.\n\n";
        return;
    }

    // HITUNG LEBAR KOLOM DINAMIS (Pass 1)
    int wBid = 9, wNama = 11, wMid = 8, wKelas = 5, wHarga = 5, wStatus = 6;
    bool adaPending = false;  // <-- DECLARE DI SINI SAJA (jangan duplikat!)
    
    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].status == "pending")
        {
            adaPending = true;
            string bid = to_string(dataBooking[i].bookingID);
            string mid = to_string(dataBooking[i].memberID);
            string harga = formatRupiah(dataBooking[i].harga);
            
            if (bid.length() > wBid) wBid = bid.length();
            if (dataBooking[i].namaMember.length() > wNama) wNama = dataBooking[i].namaMember.length();
            if (mid.length() > wMid) wMid = mid.length();
            if (dataBooking[i].jenisKelas.length() > wKelas) wKelas = dataBooking[i].jenisKelas.length();
            if (harga.length() > wHarga) wHarga = harga.length();
            if (dataBooking[i].status.length() > wStatus) wStatus = dataBooking[i].status.length();
        }
    }
    
    wBid += 2; wNama += 2; wMid += 2; wKelas += 2; wHarga += 2; wStatus += 2;
    int totalLebar = wBid + wNama + wMid + wKelas + wHarga + wStatus;

    cout << "\n";
    cout << string(totalLebar, '=') << "\n";
    cout << left << setfill(' ')
         << setw(wBid) << "BookingID"
         << setw(wNama) << "Nama Member"
         << setw(wMid) << "MemberID"
         << setw(wKelas) << "Kelas"
         << setw(wHarga) << "Harga"
         << setw(wStatus) << "Status" << "\n";
    cout << string(totalLebar, '-') << "\n";

    if (!adaPending)
    {
        cout << setw(totalLebar) << "Tidak ada booking yang menunggu approval" << "\n";
        cout << string(totalLebar, '=') << "\n";
        return;
    }

    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].status == "pending")
        {
            cout << left
                 << setw(wBid) << dataBooking[i].bookingID
                 << setw(wNama) << dataBooking[i].namaMember
                 << setw(wMid) << dataBooking[i].memberID
                 << setw(wKelas) << dataBooking[i].jenisKelas
                 << setw(wHarga) << formatRupiah(dataBooking[i].harga)
                 << setw(wStatus) << dataBooking[i].status << "\n";
        }
    }
    cout << string(totalLebar, '=') << "\n";

    try
    {
        int bookingID = inputInteger("\nMasukkan Booking ID yang ingin diproses: ");

        int index = -1;
        for (int i = 0; i < jumlahBooking; i++)
        {
            if (dataBooking[i].bookingID == bookingID && dataBooking[i].status == "pending")
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            throw runtime_error("Booking ID tidak ditemukan atau sudah diproses!");

        cout << "\n    --- Detail Booking ---\n";
        cout << "----------------------------------------\n";
        cout << left << setw(15) << "Booking ID" << ": " << dataBooking[index].bookingID << "\n";
        cout << left << setw(15) << "Nama Member" << ": " << dataBooking[index].namaMember << "\n";
        cout << left << setw(15) << "Kelas" << ": " << dataBooking[index].jenisKelas << "\n";
        cout << left << setw(15) << "Harga" << ": " << formatRupiah(dataBooking[index].harga) << "\n";
        cout << "----------------------------------------\n";
        cout << "1. Approve\n";
        cout << "2. Reject\n";

        int pilihan = inputInteger("\nPilihan (1/2): ");

        if (pilihan == 1)
        {
            dataBooking[index].status = "approved";
            loadingAnimation();
            cout << "Booking berhasil di-approve!\n\n";
        }
        else if (pilihan == 2)
        {
            dataBooking[index].status = "rejected";

            int indexMember = cariusername(dataAkun, jumlahAkun, dataBooking[index].namaMember);
            if (indexMember != -1)
            {
                dataAkun[indexMember].saldo += dataBooking[index].harga;
            }
            loadingAnimation();
            cout << "Booking di-reject! Saldo member dikembalikan.\n\n";
        }
        else
            throw out_of_range("Pilihan tidak valid!");
    }
    catch (const exception &e)
    {
        cout << endl << e.what() << "\n\n";
    }
}

void ProfilSaya(Akun *data, int jumlah, string namaLogin)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||                >> PROFIL SAYA <<               ||\n";
    cout << "====================================================\n";
    try
    {
        int index = cariusername(data, jumlah, namaLogin);
        if (index == -1)
            throw runtime_error("Profil tidak ditemukan.");

        cout << "\n";
        cout << left << setw(12) << "ID" << ": " << data[index].id << "\n";
        cout << left << setw(12) << "Nama" << ": " << data[index].nama << "\n";
        cout << left << setw(12) << "Password" << ": " << data[index].pw << "\n";
        cout << left << setw(12) << "Saldo" << ": " << formatRupiah(data[index].saldo) << "\n";
        cout << "====================================================\n";

        cout << "\nIngin mengubah password ?\n";
        cout << "1. Ya, ganti password\n";
        cout << "0. Tidak, kembali\n";

        int pilihan;
        bool validInput = false;
        while (!validInput)
        {
            try
            {
                pilihan = inputInteger("Pilihan (1/0): ");
                if (pilihan != 1 && pilihan != 0)
                    throw out_of_range("Pilihan harus 1 atau 0!");
                validInput = true;
            }
            catch (const exception &e)
            {
                cout << "[X] " << e.what() << " Silakan coba lagi.\n";
            }
        }

        if (pilihan == 1)
        {
            string pwBaru;
            cin.ignore(1000, '\n');
            cout << "Masukkan password baru: ";
            cin >> pwBaru;
            validasiPassword(pwBaru);
            data[index].pw = pwBaru;
            loadingAnimation();
            cout << "Password berhasil diubah!\n\n";
        }
        else if (pilihan == 0)
        {
            cout << "\nKembali ke menu member...\n\n";
        }
    }
    catch (const exception &e)
    {
        cout << "\n[X] " << e.what() << "\n\n";
    }
}

void topUpSaldo(Akun *data, int jumlah, string namaLogin, TopUp *dataTopUp, int &jumlahTopUp, int maxTopUp)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||                 >> TOP UP SALDO <<             ||\n";
    cout << "====================================================\n";

    try
    {
        int index = cariusername(data, jumlah, namaLogin);
        if (index == -1)
            throw runtime_error("Akun tidak ditemukan!");
        cout << "Saldo saat ini: ";
        cout << formatRupiah(data[index].saldo) << endl;
        cout << "----------------------------------------------------\n";

        int nominal = inputInteger("Nominal top up: Rp ");
        if (nominal <= 0)
            throw invalid_argument("Nominal harus lebih dari 0!");

        data[index].saldo += nominal;

        if (jumlahTopUp < maxTopUp)
        {
            dataTopUp[jumlahTopUp].namaMember = namaLogin;
            dataTopUp[jumlahTopUp].nominal = nominal;
            jumlahTopUp++;
        }

        loadingAnimation();
        cout << "Top up berhasil!\n";
        cout << "Saldo baru: ";
        cout << formatRupiah(data[index].saldo) << endl
             << endl;
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void bookingKelas(Akun *data, int jumlahAkun, string namaLogin, Booking *dataBooking, int &jumlahBooking, int maxBooking, JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||               >> BOOKING KELAS <<              ||\n";
    cout << "====================================================\n";

    try
    {
        validasiKapasitas(jumlahBooking, maxBooking);

        int indexMember = cariusername(data, jumlahAkun, namaLogin);
        if (indexMember == -1)
            throw runtime_error("Akun tidak ditemukan!");

        if (jumlahJadwal == 0)
        {
            cout << "Belum ada jadwal kelas tersedia.\n\n";
            return;
        }

        cout << "Saldo Anda: ";
        cout << formatRupiah(data[indexMember].saldo) << endl;
        cout << "----------------------------------------------------\n";
        tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);

        int jadwalID = inputInteger("\nMasukkan ID Jadwal yang ingin dibooking: ");
        int indexJadwal = -1;
        for (int i = 0; i < jumlahJadwal; i++)
        {
            if (dataJadwal[i].jadwalID == jadwalID)
            {
                indexJadwal = i;
                break;
            }
        }

        if (indexJadwal == -1)
            throw runtime_error("ID Jadwal tidak ditemukan!");

        if (dataJadwal[indexJadwal].terisi >= dataJadwal[indexJadwal].kapasitas)
            throw runtime_error("Kelas sudah penuh!");

        int harga = dataJadwal[indexJadwal].harga;

        if (data[indexMember].saldo < harga)
            throw runtime_error("Saldo tidak cukup! Silakan top up terlebih dahulu.");

        int newBookingID = 1;
        for (int i = 0; i < jumlahBooking; i++)
            if (dataBooking[i].bookingID >= newBookingID)
                newBookingID = dataBooking[i].bookingID + 1;

        data[indexMember].saldo -= harga;
        dataBooking[jumlahBooking].bookingID = newBookingID;
        dataBooking[jumlahBooking].namaMember = namaLogin;
        dataBooking[jumlahBooking].memberID = data[indexMember].id;
        dataBooking[jumlahBooking].jadwalID = jadwalID;
        dataBooking[jumlahBooking].jenisKelas = dataJadwal[indexJadwal].jenisKelas + " - " + dataJadwal[indexJadwal].kategori;
        dataBooking[jumlahBooking].harga = harga;
        dataBooking[jumlahBooking].status = "pending";
        jumlahBooking++;
        dataJadwal[indexJadwal].terisi++;

        loadingAnimation();
        cout << "Booking berhasil dibuat!\n\n";

        cout << "=============================================\n";
        cout << "||           >> DETAIL BOOKING <<          ||\n";
        cout << "=============================================\n\n";
        cout << "ID Booking   : " << newBookingID << endl;
        cout << "Jadwal       : " << dataJadwal[indexJadwal].hari << ", " << dataJadwal[indexJadwal].jam << endl;
        cout << "Kelas        : " << dataJadwal[indexJadwal].jenisKelas << " (" << dataJadwal[indexJadwal].kategori << ")" << endl;
        cout << "Instruktur   : " << dataJadwal[indexJadwal].instruktur << endl;
        cout << "Harga        : " << formatRupiah(harga) << endl;
        cout << "Status       : Menunggu Approval Admin" << endl;
        cout << "Saldo Tersisa: " << formatRupiah(data[indexMember].saldo) << endl;
        cout << "=============================================\n";
        cout << "\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void batalkanBooking(Booking *dataBooking, string namaLogin, int &jumlahBooking, Akun *dataAkun, int jumlahAkun)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "========================================================================\n";
    cout << "||                    >> BATALKAN BOOKING KELAS <<                    ||\n";
    cout << "========================================================================\n";

    int wID     = 10; 
    int wKelas  = 5;  
    int wHarga  = 5;  
    int wStatus = 6;  
    int jmlPending = 0;

    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].namaMember == namaLogin && dataBooking[i].status == "pending")
        {
            jmlPending++;
            
            string idStr   = to_string(dataBooking[i].bookingID);
            string kelasStr = dataBooking[i].jenisKelas;
            string hargaStr = formatRupiah(dataBooking[i].harga); 
            string statusStr = dataBooking[i].status;

            if (idStr.length()   > wID)     wID     = idStr.length();
            if (kelasStr.length() > wKelas)  wKelas  = kelasStr.length();
            if (hargaStr.length() > wHarga)  wHarga  = hargaStr.length();
            if (statusStr.length() > wStatus)wStatus = statusStr.length();
        }
    }

    wID += 2; wKelas += 2; wHarga += 2; wStatus += 2;
    int totalLebar = wID + wKelas + wHarga + wStatus;

    cout << string(totalLebar, '=') << "\n";
    cout << left << setfill(' ')
         << setw(wID)     << "ID Booking"
         << setw(wKelas)  << "Kelas"
         << setw(wHarga)  << "Harga"
         << setw(wStatus) << "Status" << "\n";
    cout << string(totalLebar, '-') << "\n";


    if (jmlPending == 0)
    {
        cout << " Tidak ada booking pending! \n";
        cout << string(totalLebar, '=') << "\n";
        cout << "\nTekan ENTER untuk kembali...";
        cin.ignore(); cin.get();
        return; 
    }

    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].namaMember == namaLogin && dataBooking[i].status == "pending")
        {
            cout << left
                 << setw(wID)     << dataBooking[i].bookingID
                 << setw(wKelas)  << dataBooking[i].jenisKelas
                 << setw(wHarga)  << formatRupiah(dataBooking[i].harga)
                 << setw(wStatus) << dataBooking[i].status << "\n";
        }
    }
    cout << string(totalLebar, '=') << "\n";

    try
    {
        int bookingID = inputInteger("\nMasukkan Booking ID yang ingin dibatalkan: ");
        int index = -1;

        for (int i = 0; i < jumlahBooking; i++)
        {
            if (dataBooking[i].bookingID == bookingID &&
                dataBooking[i].namaMember == namaLogin &&
                dataBooking[i].status == "pending")
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            throw runtime_error("Booking tidak ditemukan atau sudah diproses admin!");

        cout << "\nDetail Booking!\n";
        cout << "Booking ID  : " << dataBooking[index].bookingID << "\n";
        cout << "Kelas       : " << dataBooking[index].jenisKelas << "\n";
        cout << "Harga       : " << formatRupiah(dataBooking[index].harga) << "\n";
        cout << "Status      : " << dataBooking[index].status << "\n";
        cout << "----------------------------------------------------\n";

        dataBooking[index].status = "canceled";
        int indexMember = cariusername(dataAkun, jumlahAkun, namaLogin);
        if (indexMember != -1)
        {
            dataAkun[indexMember].saldo += dataBooking[index].harga;
            cout << "\n[OK] Booking berhasil dibatalkan! Saldo dikembalikan.\n";
        }
    }
    catch (const exception &e)
    {
        cout << "\n[Error] " << e.what() << "\n";
    }
}

void riwayatTransaksi(Booking *dataBooking, int jumlahBooking, TopUp *dataTopUp, int jumlahTopUp, string namaLogin)
{
    system("cls");
    tampilkanLogoKecil();
    
    int wJenis=15, wKet=11, wNom=7, wStat=6;
    bool AdaData = false;
    
    for (int i = 0; i < jumlahTopUp; i++)
    {
        if (dataTopUp[i].namaMember == namaLogin)
        {
            AdaData = true;
            string nom = "+ " + formatRupiah(dataTopUp[i].nominal);
            if (nom.length() > wNom) wNom = nom.length();
        }
    }

    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].namaMember == namaLogin)
        {
            AdaData = true;
            string ket = "Booking " + dataBooking[i].jenisKelas;
            string nom, stat;
            if (dataBooking[i].status == "approved" || dataBooking[i].status == "pending")
                nom = "- " + formatRupiah(dataBooking[i].harga);
            else
                nom = "+ " + formatRupiah(dataBooking[i].harga);
            
            if (dataBooking[i].status == "approved") stat = "Approved";
            else if (dataBooking[i].status == "pending") stat = "Pending";
            else if (dataBooking[i].status == "canceled") stat = "Canceled";
            else stat = "Rejected";
            
            if (ket.length() > wKet) wKet = ket.length();
            if (nom.length() > wNom) wNom = nom.length();
            if (stat.length() > wStat) wStat = stat.length();
        }
    }
    
    wJenis+=2; wKet+=2; wNom+=2; wStat+=2;
    int totalLebar = wJenis + wKet + wNom + wStat;

    cout << string(totalLebar, '=') << "\n";


    string judul = " >> RIWAYAT TRANSAKSI << ";
    int ruangTersedia = totalLebar - 4;
    int panjangJudul = judul.length();
    int paddingKiri = (ruangTersedia - panjangJudul) / 2;
    int paddingKanan = ruangTersedia - panjangJudul - paddingKiri;

    cout << "||" << string(paddingKiri, ' ') << judul << string(paddingKanan, ' ') << "||\n";

    cout << string(totalLebar, '=') << "\n";

    cout << left << setfill(' ')
         << setw(wJenis) << "Jenis Transaksi"
         << setw(wKet) << "Keterangan"
         << setw(wNom) << "Nominal"
         << setw(wStat) << "Status" << "\n";
    cout << string(totalLebar, '-') << "\n";

    if (!AdaData)
    {
        cout << setw(totalLebar) << "Belum ada riwayat transaksi." << "\n";
    }
    else
    {
        for (int i = 0; i < jumlahTopUp; i++)
        {
            if (dataTopUp[i].namaMember == namaLogin)
            {
                string nom = "+ " + formatRupiah(dataTopUp[i].nominal);
                cout << left
                     << setw(wJenis) << "Top Up"
                     << setw(wKet) << "Saldo ditambah"
                     << setw(wNom) << nom
                     << setw(wStat) << "Berhasil" << "\n";
            }
        }

        for (int i = 0; i < jumlahBooking; i++)
        {
            if (dataBooking[i].namaMember == namaLogin)
            {
                string ket = "Booking " + dataBooking[i].jenisKelas;
                string nom, stat;
                if (dataBooking[i].status == "approved" || dataBooking[i].status == "pending")
                    nom = "- " + formatRupiah(dataBooking[i].harga);
                else
                    nom = "+ " + formatRupiah(dataBooking[i].harga);
                
                if (dataBooking[i].status == "approved") stat = "Approved";
                else if (dataBooking[i].status == "pending") stat = "Pending";
                else if (dataBooking[i].status == "canceled") stat = "Canceled";
                else stat = "Rejected";
                
                cout << left
                     << setw(wJenis) << "Booking"
                     << setw(wKet) << ket
                     << setw(wNom) << nom
                     << setw(wStat) << stat << "\n";
            }
        }
    }
    cout << string(totalLebar, '=') << "\n";
}

int main()
{
    const int MAX = 20;
    const int MAX_BOOKING = 50;
    const int MAX_JADWAL = 30;
    const int MAX_TOPUP = 100;

    Akun dataAkun[MAX];
    int jumlah = 2;
    dataAkun[0] = {"annisa", "078", "admin", 0, 0};
    dataAkun[1] = {"juun", "0412", "member", 1, 0};

    Booking dataBooking[MAX_BOOKING];
    int jumlahBooking = 0;

    JadwalKelas dataJadwal[MAX_JADWAL];
    int jumlahJadwal = 0;

    TopUp dataTopUp[MAX_TOPUP];
    int jumlahTopUp = 0;

    Akun *ptrAkun = dataAkun;
    bool programAktif = true;
    bool statusLogin = false;
    string namaLogin = "";
    string roleLogin = "";

    while (programAktif)
    {
        if (!statusLogin)
        {
            system("cls");
            setColor(11);
            cout << "\n";
            cout << "================================================================\n";
            cout << "||                                                            ||\n";
            cout << "||     ######   ##  ##       ###   ######  #####  #####       ||\n";
            cout << "||     ##  ##   ##  ##      ## ##    ##    ##     ##          ||\n";
            cout << "||     #####    ##  ##      ######   ##    ####   ####        ||\n";
            cout << "||     ##       ##  ##      ##  ##   ##    ##        ##       ||\n";
            cout << "||     ##       ##  ### ##  ##  ##   ##    #####  ####        ||\n";
            cout << "||                                                            ||\n";
            cout << "||     ##   ##   ###   ##  ##   ##   ###   ##  ##             ||\n";
            cout << "||     ### ###  ## ##  ### ##   ##  ## ##  ## ##              ||\n";
            cout << "||     ## # ##  #####  ## ###   ##  #####  ####               ||\n";
            cout << "||     ##   ##  ## ##  ##  ##   ##  ## ##  ## ##              ||\n";
            cout << "||     ##   ##  ## ##  ##  ##   ##  ## ##  ##  ##             ||\n";
            cout << "||                                                            ||\n";
            cout << "================================================================\n";
            setColor(14);
            cout << "                  >> STUDIO PILATES MANAGEMENT <<\n";
            setColor(10);
            cout << "                    Your Health, Our Priority!\n";
            setColor(7);
            cout << endl;

            cout << "============================================\n";
            cout << "||            >> MENU UTAMA <<            ||\n";
            cout << "============================================\n";
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "0. Keluar\n";
            cout << "--------------------------------------------\n";

            try
            {
                int pilihan = inputInteger("Pilih menu (1/2/3): ");
                if (pilihan == 1)
                    login(ptrAkun, jumlah, statusLogin, namaLogin, roleLogin);
                else if (pilihan == 2)
                {
                    registrasi(ptrAkun, jumlah, MAX);
                    system("pause");
                }
                else if (pilihan == 0)
                {
                    system("cls");
                    setColor(11);
                    cout << "\n";
                    cout << "    ================================================================\n";
                    cout << "    ||                                                            ||\n";
                    cout << "    ||         #####  #####  ####    ##   ##   ##   ###           ||\n";
                    cout << "    ||           ##   ##     ##  ##  ##   ### ###  ## ##          ||\n";
                    cout << "    ||           ##   ####   ####    ##   ## # ##  #####          ||\n";
                    cout << "    ||           ##   ##     ##  ##  ##   ##   ##  ## ##          ||\n";
                    cout << "    ||           ##   #####  ##  ##  ##   ##   ##  ## ##          ||\n";
                    cout << "    ||                                                            ||\n";
                    cout << "    ||             ##  ##   ###    ####   ##  ##  ##              ||\n";
                    cout << "    ||             ## ##   ## ##  ##      ##  ##  ##              ||\n";
                    cout << "    ||             ####    #####   ####   ##  ######              ||\n";
                    cout << "    ||             ## ##   ## ##      ##  ##  ##  ##              ||\n";
                    cout << "    ||             ##  ##  ## ##  ####    ##  ##  ##              ||\n";
                    cout << "    ||                                                            ||\n";
                    cout << "    ================================================================\n";
                    setColor(10);
                    cout << "                    Stay Healthy, Stay Strong!\n\n";
                    programAktif = false;
                }
                else
                    throw out_of_range("Pilihan tidak valid!");
            }
            catch (const exception &e)
            {
                cout << endl
                     << e.what() << "\n\n";
                system("pause");
            }
        }
        else
        {
            if (roleLogin == "admin")
            {
                system("cls");
                tampilkanLogoKecil();

                cout << "============================================\n";
                cout << "||             >> MENU ADMIN <<           ||\n";
                cout << "============================================\n";
                cout << "1. Tambah Member (Create)\n";
                cout << "2. Lihat Member (Read)\n";
                cout << "3. Hapus Member (Delete)\n";
                cout << "4. Tambah Jadwal (Create)\n";
                cout << "5. Lihat Jadwal (Read)\n";
                cout << "6. Update Jadwal (Update)\n";
                cout << "7. Hapus Jadwal (Delete)\n";
                cout << "8. Approval Booking\n";
                cout << "0. Logout\n";
                cout << "--------------------------------------------\n";

                try
                {
                    int pilihan = inputInteger("Pilih menu (0-8): ");
                    if (pilihan == 1)
                    {
                        tambahMember(ptrAkun, jumlah, MAX);
                        system("pause");
                    }
                    else if (pilihan == 2)
                        lihatMember(ptrAkun, jumlah);
                    else if (pilihan == 3)
                    {
                        hapusMember(ptrAkun, jumlah);
                        system("pause");
                    }
                    else if (pilihan == 4)
                    {
                        tambahJadwal(dataJadwal, jumlahJadwal, MAX_JADWAL);
                        system("pause");
                    }
                    else if (pilihan == 5)
                    {
                        lihatJadwal(dataJadwal, jumlahJadwal);
                        system("pause");
                    }
                    else if (pilihan == 6)
                    {
                        updateJadwal(dataJadwal, jumlahJadwal);
                        system("pause");
                    }
                    else if (pilihan == 7)
                    {
                        hapusJadwal(dataJadwal, jumlahJadwal);
                        system("pause");
                    }
                    else if (pilihan == 8)
                    {
                        approvalBooking(dataBooking, jumlahBooking, ptrAkun, jumlah);
                        system("pause");
                    }
                    else if (pilihan == 0)
                    {
                        statusLogin = false;
                        namaLogin = "";
                        roleLogin = "";
                        loadingAnimation();
                        cout << "Berhasil Logout!\n\n";
                        system("pause");
                    }
                    else
                        throw out_of_range("Pilihan tidak valid!");
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << "\n\n";
                    system("pause");
                }
            }
            else if (roleLogin == "member")
            {
                system("cls");
                tampilkanLogoKecil();

                cout << "============================================\n";
                cout << "||          >> MENU MEMBER <<             ||\n";
                cout << "============================================\n";
                cout << "1. Lihat Profil Saya\n";
                cout << "2. Top Up Saldo\n";
                cout << "3. Booking Kelas\n";
                cout << "4. Batalkan Booking Kelas\n";
                cout << "5. Riwayat Transaksi\n";
                cout << "0. Logout\n";
                cout << "--------------------------------------------\n";

                try
                {
                    int pilihan = inputInteger("Pilih menu: ");
                    if (pilihan == 1)
                    {
                        ProfilSaya(ptrAkun, jumlah, namaLogin);
                        system("pause");
                    }
                    else if (pilihan == 2)
                    {
                        topUpSaldo(ptrAkun, jumlah, namaLogin, dataTopUp, jumlahTopUp, MAX_TOPUP);
                        system("pause");
                    }
                    else if (pilihan == 3)
                    {
                        bookingKelas(ptrAkun, jumlah, namaLogin, dataBooking, jumlahBooking, MAX_BOOKING, dataJadwal, jumlahJadwal);
                        system("pause");
                    }
                    else if (pilihan == 4)
                    {
                        batalkanBooking(dataBooking, namaLogin, jumlahBooking, ptrAkun, jumlah);
                        system("pause");
                    }
                    else if (pilihan == 5)
                    {
                        riwayatTransaksi(dataBooking, jumlahBooking, dataTopUp, jumlahTopUp, namaLogin);
                        system("pause");
                    }
                    else if (pilihan == 0)
                    {
                        statusLogin = false;
                        namaLogin = "";
                        roleLogin = "";
                        loadingAnimation();
                        cout << "Berhasil Logout!\n\n";
                        system("pause");
                    }
                    else
                        throw out_of_range("Pilihan tidak valid!");
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << "\n\n";
                    system("pause");
                }
            }
        }
    }
    return 0;
}