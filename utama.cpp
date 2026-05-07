#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <windows.h>
#include <cctype>
#include <fstream>
using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void tampilkanLogoKecil()
{
    cout << "\n";
    cout << "====================================================\n";
    cout << "||           💪 STUDIO PILATES MANIAK 💪          ||\n";
    cout << "====================================================\n";
}

void loadingAnimation()
{
    setColor(14);
    cout << "\n⏳ Loading";
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
    cout << "\n❌ Terlalu banyak percobaan gagal!\n";
    setColor(14);
    cout << "⏰ Silakan tunggu ";
    for (int i = detik; i > 0; i--)
    {
        cout << i << "....";
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
        throw invalid_argument("❌ Input Harus berupa angka.");
    }
    return nilai;
}

void validasiHurufSpasi(const string &teks, const string &namaField, int minLen = 0)
{
    if (teks.empty() || teks == " ")
        throw invalid_argument("❌ " + namaField + " tidak boleh kosong!");
    if ((int)teks.length() < minLen)
        throw invalid_argument("❌ " + namaField + " minimal " + to_string(minLen) + " karakter!");

    bool semuaSpasi = true;
    for (char c : teks)
    {
        if (!isalpha(c) && c != ' ')
            throw invalid_argument("❌ " + namaField + " hanya boleh huruf dan spasi!");
        if (c != ' ')
            semuaSpasi = false;
    }
    if (semuaSpasi)
        throw invalid_argument("❌ " + namaField + " tidak boleh hanya berisi spasi!");
}

void validasiHari(const string &hari)
{
    if (hari.empty())
        throw invalid_argument("❌ Hari tidak boleh kosong!");

    for (int i = 0; i < hari.length(); i++)
    {
        if (!isalpha(hari[i]) && hari[i] != ' ')
        {
            throw invalid_argument("❌ Hari hanya boleh berisi huruf!");
        }
    }
}

void validasiJam(const string &jam)
{
    if (jam.empty())
        throw invalid_argument("❌ Jam tidak boleh kosong!");

    for (int i = 0; i < jam.length(); i++)
    {
        if (!isdigit(jam[i]) && jam[i] != ':' && jam[i] != '-' && jam[i] != ' ')
        {
            throw invalid_argument("❌ Format jam tidak valid!");
        }
    }
}

void validasiPassword(const string &pw)
{
    if (pw.empty())
        throw invalid_argument("❌ Password tidak boleh kosong!");
    if ((int)pw.length() < 3)
        throw length_error("❌ Password terlalu pendek! Minimal 3 karakter.");
}

void validasiKapasitas(int jumlah, int maxKapasitas)
{
    if (jumlah >= maxKapasitas)
        throw length_error("⚠️ Kapasitas penuh! Tidak dapat menambah data.");
}

void validasiID(int id)
{
    if (id <= 0)
        throw out_of_range("❌ ID tidak valid! Harus berupa angka positif.");
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

// Database

void simpanAkun(Akun *data, int jumlah)
{
    ofstream file("akun.csv");
    file << "nama,pw,role,id,saldo\n";
    for (int i = 0; i < jumlah; i++)
    {
        file << data[i].nama << ","
             << data[i].pw << ","
             << data[i].role << ","
             << data[i].id << ","
             << data[i].saldo << "\n";
    }
    file.close();
}

void muatAkun(Akun *data, int &jumlah)
{
    ifstream file("akun.csv");
    if (!file.is_open())
    {
        data[0] = {"annisa", "078", "admin", 0, 0};
        data[1] = {"juun", "0412", "member", 1, 0};
        jumlah = 2;
        simpanAkun(data, jumlah);
        return;
    }

    string baris;
    getline(file, baris);
    jumlah = 0;

    while (getline(file, baris) && jumlah < 20)
    {
        stringstream ss(baris);
        string token;

        getline(ss, token, ',');
        data[jumlah].nama = token;
        getline(ss, token, ',');
        data[jumlah].pw = token;
        getline(ss, token, ',');
        data[jumlah].role = token;
        getline(ss, token, ',');
        data[jumlah].id = stoi(token);
        getline(ss, token, ',');
        data[jumlah].saldo = stoi(token);
        jumlah++;
    }
    file.close();
}

void simpanJadwal(JadwalKelas *data, int jumlah)
{
    ofstream file("jadwal.csv");
    file << "jadwalID,hari,jam,jenisKelas,kategori,instruktur,harga,kapasitas,terisi\n";
    for (int i = 0; i < jumlah; i++)
    {
        file << data[i].jadwalID << ","
             << data[i].hari << ","
             << data[i].jam << ","
             << data[i].jenisKelas << ","
             << data[i].kategori << ","
             << data[i].instruktur << ","
             << data[i].harga << ","
             << data[i].kapasitas << ","
             << data[i].terisi << "\n";
    }
    file.close();
}

void muatJadwal(JadwalKelas *data, int &jumlah)
{
    ifstream file("jadwal.csv");
    if (!file.is_open())
    {
        jumlah = 0;
        return;
    }

    string baris;
    getline(file, baris);
    jumlah = 0;

    while (getline(file, baris) && jumlah < 30)
    {
        stringstream ss(baris);
        string token;

        getline(ss, token, ',');
        data[jumlah].jadwalID = stoi(token);
        getline(ss, token, ',');
        data[jumlah].hari = token;
        getline(ss, token, ',');
        data[jumlah].jam = token;
        getline(ss, token, ',');
        data[jumlah].jenisKelas = token;
        getline(ss, token, ',');
        data[jumlah].kategori = token;
        getline(ss, token, ',');
        data[jumlah].instruktur = token;
        getline(ss, token, ',');
        data[jumlah].harga = stoi(token);
        getline(ss, token, ',');
        data[jumlah].kapasitas = stoi(token);
        getline(ss, token, ',');
        data[jumlah].terisi = stoi(token);
        jumlah++;
    }
    file.close();
}

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
    cout << "\n";
    cout << "====================================================\n";
    cout << "||          👥 DAFTAR MEMBER TERDAFTAR 👥         ||\n";
    cout << "====================================================\n";

    cout << left << setw(8) << "ID" << setw(20) << "Nama" << setw(20) << "Saldo" << endl;
    cout << "----------------------------------------------------\n";

    bool ada = false;
    for (int i = 0; i < jumlah; i++)
    {
        if (data[i].role == "member")
        {
            ada = true;
            cout << left << setw(8) << data[i].id;
            cout << setw(20) << data[i].nama;
            cout << setw(20) << "💰 " + formatRupiah(data[i].saldo) << "\n";
        }
    }
    if (!ada)
    {
        cout << "❌ Belum ada data member terdaftar !\n";
    }
    cout << "====================================================\n";
}

void tampilkanDaftarJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    cout << "\n";
    cout << "==========================================================================================================\n";
    cout << "||                                     📅 DAFTAR JADWAL KELAS 📅                                        ||\n";
    cout << "==========================================================================================================\n";

    cout << left
         << setw(5) << "ID"
         << setw(10) << "Hari"
         << setw(15) << "Jam"
         << setw(18) << "Jenis"
         << setw(15) << "Kategori"
         << setw(15) << "Instruktur"
         << setw(12) << "Harga"
         << "Kapasitas" << endl;
    cout << "----------------------------------------------------------------------------------------------------------\n";

    if (jumlahJadwal == 0)
    {
        cout << "❌ Belum ada data jadwal !\n";
    }
    else
    {
        for (int i = 0; i < jumlahJadwal; i++)
        {
            int sisa = dataJadwal[i].kapasitas - dataJadwal[i].terisi;

            cout << left << setw(5) << dataJadwal[i].jadwalID;
            cout << setw(10) << dataJadwal[i].hari;
            cout << setw(15) << dataJadwal[i].jam;
            cout << setw(18) << dataJadwal[i].jenisKelas;
            cout << setw(15) << dataJadwal[i].kategori;
            cout << setw(15) << dataJadwal[i].instruktur;
            cout << setw(12) << formatRupiah(dataJadwal[i].harga);
            cout << dataJadwal[i].terisi << "/" << dataJadwal[i].kapasitas
                 << " (sisa " << sisa << ")" << endl;
        }
    }

    cout << "==========================================================================================================\n";
}

void login(Akun *data, int jumlah, bool &statusLogin, string &namaLogin, string &roleLogin)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||              🔐 LOGIN SYSTEM 🔐                ||\n";
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
                    cout << "👤 Masukkan Username : ";
                    getline(cin, inputNama);
                    validasiHurufSpasi(inputNama, "Username", 4);
                    usernameValid = true;
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << "\n";
                    cout << "🔄 Silakan masukkan username kembali.\n\n";
                }
            }

            cout << "🔑 Masukkan Password : ";
            cin >> inputpw;
            int index = cariusername(data, jumlah, inputNama);
            if (index != -1 && data[index].pw == inputpw)
            {
                statusLogin = true;
                namaLogin = data[index].nama;
                roleLogin = data[index].role;

                loadingAnimation();
                cout << "✅ Login berhasil!\n";
                cout << "👋 Selamat datang, " << namaLogin << " (" << roleLogin << ")!\n\n";
                system("pause");
                return;
            }
            else
            {
                kesempatan--;
                cout << "\n❌ Login Gagal! Username atau Password salah.\n";
                if (kesempatan > 0)
                {
                    cout << "⚠️ Sisa kesempatan: " << kesempatan << "\n\n";
                }
                else
                {
                    cout << "\n🚫 Kesempatan Anda Habis!\n";
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
                cout << "⚠️ Sisa kesempatan: " << kesempatan << "\n";
            else
            {
                cout << "🚫 Kesempatan Habis.\n";
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
    cout << "||        📝 REGISTRASI AKUN BARU 📝              ||\n";
    cout << "====================================================\n";
    cin.ignore(1000, '\n');
    try
    {
        validasiKapasitas(jumlah, maxKapasitas);
        string namaBaru, pwBaru;

        cout << "👤 Masukkan Username : ";
        getline(cin, namaBaru);

        validasiHurufSpasi(namaBaru, "Username", 4);

        if (cariusername(data, jumlah, namaBaru) != -1)
            throw runtime_error("❌ Username sudah terdaftar. Gunakan username lain.");

        cout << "🔑 Masukkan Password : ";
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

        simpanAkun(data, jumlah);

        loadingAnimation();
        cout << "✅ Registrasi Berhasil! Silakan Login.\n";
        cout << "🆔 ID Anda: " << newID << "\n";
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
    cout << "||           ➕ TAMBAH MEMBER BARU ➕             ||\n";
    cout << "====================================================\n";
    cin.ignore(1000, '\n');
    try
    {
        validasiKapasitas(jumlah, maxKapasitas);
        string namaBaru, pwBaru;
        cout << "👤 Masukkan Nama Member : ";
        getline(cin, namaBaru);

        validasiHurufSpasi(namaBaru, "Username", 4);

        if (cariusername(data, jumlah, namaBaru) != -1)
            throw runtime_error("❌ Username sudah terdaftar.");

        cout << "🔑 Masukkan Password Member : ";
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

        simpanAkun(data, jumlah);

        loadingAnimation();
        cout << "✅ Member Berhasil Ditambahkan!\n";
        cout << "🆔 ID Member: " << newID << "\n\n";
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void lihatMember(Akun *data, int jumlah)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "=====================================================\n";
    cout << "||             👀 LIHAT DATA MEMBER 👀             ||\n";
    cout << "=====================================================\n";

    Akun temp[20];
    int memberCount = 0;
    for (int i = 0; i < jumlah; i++)
        if (data[i].role == "member")
            temp[memberCount++] = data[i];

    for (int i = 0; i < memberCount - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < memberCount; j++)
            if (temp[j].nama < temp[minIndex].nama)
                minIndex = j;

        if (minIndex != i)
            swap(temp[i], temp[minIndex]);
    }

    cout << "\n====================================================\n";
    cout << "||               📋 DAFTAR MEMBER 📋              ||\n";
    cout << "====================================================\n";
    cout << left << setw(8) << "ID" << setw(20) << "Nama" << setw(20) << "Saldo" << endl;
    cout << "----------------------------------------------------\n";

    if (memberCount == 0)
        cout << "❌ Belum ada data member.\n";
    else
        for (int i = 0; i < memberCount; i++)
            cout << left << setw(8) << temp[i].id
                 << setw(20) << temp[i].nama
                 << setw(20) << "💰 " + formatRupiah(temp[i].saldo) << "\n";

    cout << "====================================================\n\n";

    cout << "🔍 Ingin mencari member berdasarkan ID?\n";
    cout << "   1. ✅ Ya, cari member\n";
    cout << "   0. ⬅️ Kembali\n";
    cout << "----------------------------------------------------\n";

    try
    {
        int pilihan = inputInteger(" 🎯 Pilihan (1/0): ");

        if (pilihan == 1)
        {
            system("cls");
            tampilkanLogoKecil();
            cout << "====================================================\n";
            cout << "||        🔎 CARI MEMBER BERDASARKAN ID 🔎        ||\n";
            cout << "====================================================\n";

            tampilkanDaftarMember(data, jumlah);

            int targetID;
            while (true)
            {
                try
                {
                    targetID = inputInteger("\n🆔 Masukkan ID yang dicari: ");
                    validasiID(targetID);
                    break;
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << " Silakan coba lagi.\n";
                }
            }

            cout << "\n🎯 Target ID: " << targetID << endl;
            cout << "--------------------------------------------\n";

            int hasil = -1, jumlahCek = 0;
            for (int i = 0; i < jumlah && hasil == -1; i++)
            {
                if (data[i].role == "member")
                {
                    jumlahCek++;
                    cout << "🔍 Cek member ke-" << jumlahCek << ": ID " << data[i].id;

                    if (data[i].id == targetID)
                    {
                        cout << " >>> ✅ COCOK!\n";
                        hasil = i;
                    }
                    else
                        cout << " (❌ tidak cocok)\n";
                }
            }
            cout << "--------------------------------------------\n";

            if (hasil != -1)
            {
                cout << "🎉 Ditemukan setelah " << jumlahCek << " pengecekan!\n\n";
                cout << "=============================================\n";
                cout << "||         ✅ MEMBER DITEMUKAN! ✅         ||\n";
                cout << "=============================================\n";
                cout << "🆔 ID       : " << data[hasil].id << endl;
                cout << "👤 Nama     : " << data[hasil].nama << endl;
                cout << "💰 Saldo    : " << formatRupiah(data[hasil].saldo) << endl;
                cout << "=============================================\n";
            }
            else
                cout << "❌ Member dengan ID " << targetID << " tidak ditemukan!\n";

            cout << "\n";
            system("pause");
        }
        else if (pilihan == 0)
        {
            return;
        }
        else
        {
            cout << "\n❌ Pilihan tidak valid!\n";
            system("pause");
        }
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
        system("pause");
    }
}

void hapusMember(Akun *data, int &jumlah)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||               🗑️ HAPUS MEMBER 🗑️               ||\n";
    cout << "====================================================\n";
    tampilkanDaftarMember(data, jumlah);

    try
    {
        int IDHapus = inputInteger("\n🆔 Masukkan ID member yang ingin dihapus: ");
        validasiID(IDHapus);

        int index = cariID(data, jumlah, IDHapus);
        if (index == -1)
            throw runtime_error("❌ Member dengan ID tersebut tidak ditemukan!");
        cout << "\n🗑️   Menghapus member: " << data[index].nama << "\n";

        for (int j = index; j < jumlah - 1; j++)
            data[j] = data[j + 1];
        jumlah--;

        simpanAkun(data, jumlah);

        loadingAnimation();
        cout << "✅ Data member berhasil dihapus!\n\n";
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
    cout << "===========================================================\n";
    cout << "||               ➕ TAMBAH JADWAL KELAS ➕               ||\n";
    cout << "===========================================================\n";

    if (jumlahJadwal >= maxJadwal)
    {
        cout << "⚠️ Kuota penyimpanan jadwal penuh!\n\n";
        return;
    }

    try
    {
        cin.ignore(1000, '\n');

        string hariInput;
        cout << "\n📅 Hari (Senin/Selasa/Rabu/Kamis/Jumat/Sabtu/Minggu): ";
        getline(cin, hariInput);
        validasiHari(hariInput);

        string jamInput;
        cout << "🕐 Jam (contoh: 08:00 - 09:00): ";
        getline(cin, jamInput);
        validasiJam(jamInput);

        string jenisInput;
        cout << "🧘 Jenis Kelas (Mat/Reformer/Cadillac/Klinis/Kontemporer): ";
        getline(cin, jenisInput);
        validasiHurufSpasi(jenisInput, "Jenis kelas");

        string kategoriInput;
        cout << "📌 Kategori (Private/Reguler): ";
        getline(cin, kategoriInput);
        validasiHurufSpasi(kategoriInput, "Kategori");

        string instrukturInput;
        cout << "👩‍🦰👨‍🦰 Instruktur: ";
        getline(cin, instrukturInput);
        validasiHurufSpasi(instrukturInput, "Instruktur");

        int hargaInput;
        bool validHarga = false;
        while (!validHarga)
        {
            try
            {
                cout << "💰 Harga Kelas: Rp ";
                cin >> hargaInput;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    throw invalid_argument("❌ Input harga tidak valid!");
                }
                if (hargaInput <= 0)
                    throw invalid_argument("❌ Harga harus lebih dari 0!");
                validHarga = true;
            }
            catch (const exception &e)
            {
                cout << endl
                     << e.what() << " Silakan coba lagi.\n";
            }
        }

        int kapasitasInput = inputInteger("👥 Kapasitas Peserta: ");
        if (kapasitasInput <= 0)
            throw invalid_argument("❌ Kapasitas harus lebih dari 0!");

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

        simpanJadwal(dataJadwal, jumlahJadwal);

        loadingAnimation();
        cout << "✅ Jadwal berhasil ditambahkan!\n";
        cout << "🆔 ID Jadwal: " << newID << "\n\n";
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
    cout << "||            📋 LIHAT JADWAL KELAS 📋            ||\n";
    cout << "====================================================\n";

    JadwalKelas temp[30];
    for (int i = 0; i < jumlahJadwal; i++)
        temp[i] = dataJadwal[i];

    for (int i = 0; i < jumlahJadwal - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < jumlahJadwal; j++)
            if (temp[j].kategori < temp[minIndex].kategori)
                minIndex = j;

        if (minIndex != i)
            swap(temp[i], temp[minIndex]);
    }

    cout << "==========================================================================================================\n";
    cout << "||                                    📅 DAFTAR JADWAL KELAS 📅                                         ||\n";
    cout << "==========================================================================================================\n";
    cout << left
         << setw(5) << "ID"
         << setw(10) << "Hari"
         << setw(15) << "Jam"
         << setw(18) << "Jenis"
         << setw(15) << "Kategori"
         << setw(15) << "Instruktur"
         << setw(12) << "Harga"
         << "Kapasitas" << endl;
    cout << "----------------------------------------------------------------------------------------------------------\n";

    if (jumlahJadwal == 0)
        cout << "❌ Belum ada data jadwal!\n";
    else
        for (int i = 0; i < jumlahJadwal; i++)
        {
            int sisa = temp[i].kapasitas - temp[i].terisi;
            cout << left << setw(5) << temp[i].jadwalID;
            cout << setw(10) << temp[i].hari;
            cout << setw(15) << temp[i].jam;
            cout << setw(18) << temp[i].jenisKelas;
            cout << setw(15) << temp[i].kategori;
            cout << setw(15) << temp[i].instruktur;
            cout << setw(12) << formatRupiah(temp[i].harga);
            cout << temp[i].terisi << "/" << temp[i].kapasitas
                 << " (sisa " << sisa << ")" << endl;
        }

    cout << "==========================================================================================================\n\n";

    cout << "🔍 Ingin mencari jadwal berdasarkan ID?\n";
    cout << "   1. ✅ Ya, cari jadwal\n";
    cout << "   0. ⬅️ Kembali\n";
    cout << "----------------------------------------------------\n";

    try
    {
        int pilihan = inputInteger(" 🎯 Pilihan (1/0): ");

        if (pilihan == 1)
        {
            system("cls");
            tampilkanLogoKecil();
            cout << "====================================================\n";
            cout << "||        🔎 CARI JADWAL BERDASARKAN ID 🔎        ||\n";
            cout << "====================================================\n";

            tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);

            int targetID;
            while (true)
            {
                try
                {
                    targetID = inputInteger("\n🆔 Masukkan ID Jadwal yang dicari: ");
                    validasiID(targetID);
                    break;
                }
                catch (const exception &e)
                {
                    cout << endl
                         << e.what() << " Silakan coba lagi.\n";
                }
            }

            cout << "\n🎯 Target ID: " << targetID << endl;
            cout << "---------------------------------------\n";

            int hasil = -1, jumlahCek = 0;
            for (int i = 0; i < jumlahJadwal && hasil == -1; i++)
            {
                jumlahCek++;
                cout << "🔍 Cek jadwal ke-" << jumlahCek << ": ID " << dataJadwal[i].jadwalID;

                if (dataJadwal[i].jadwalID == targetID)
                {
                    cout << " >>> ✅ COCOK!\n";
                    hasil = i;
                }
                else
                    cout << " (❌ tidak cocok)\n";
            }
            cout << "---------------------------------------\n";

            if (hasil != -1)
            {
                cout << "🎉 Ditemukan setelah " << jumlahCek << " pengecekan!\n\n";
                cout << "===============================================\n";
                cout << "||          ✅ JADWAL DITEMUKAN! ✅          ||\n";
                cout << "===============================================\n";
                cout << "🆔 ID         : " << dataJadwal[hasil].jadwalID << endl;
                cout << "📅 Hari       : " << dataJadwal[hasil].hari << endl;
                cout << "🕐 Jam        : " << dataJadwal[hasil].jam << endl;
                cout << "🧘 Jenis      : " << dataJadwal[hasil].jenisKelas << endl;
                cout << "📌 Kategori   : " << dataJadwal[hasil].kategori << endl;
                cout << "👨‍🏫 Instruktur : " << dataJadwal[hasil].instruktur << endl;
                cout << "💰 Harga      : " << formatRupiah(dataJadwal[hasil].harga) << endl;
                cout << "👥 Kapasitas  : " << dataJadwal[hasil].terisi << "/" << dataJadwal[hasil].kapasitas << endl;
                cout << "===============================================\n";
            }
            else
                cout << "❌ Jadwal dengan ID " << targetID << " tidak ditemukan!\n";

            cout << "\n";
        }
        else if (pilihan == 0)
        {
            return;
        }
        else
        {
            cout << "\n❌ Pilihan tidak valid!\n";
        }
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void updateJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||             ✏️ UPDATE JADWAL KELAS ✏️          ||\n";
    cout << "====================================================\n";

    if (jumlahJadwal == 0)
    {
        cout << "❌ Data jadwal masih kosong!\n\n";
        return;
    }

    tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);
    cout << "\n";

    int idCari = inputInteger("🆔 Masukkan ID Jadwal yang ingin diubah: ");
    bool ditemukan = false;

    for (int i = 0; i < jumlahJadwal; i++)
    {
        if (dataJadwal[i].jadwalID == idCari)
        {
            ditemukan = true;
            cout << "===============================================\n";
            cout << "||          📝 MASUKKAN DATA BARU 📝         ||\n";
            cout << "===============================================\n";
            cin.ignore(1000, '\n');
            string inputBaru;

            cout << "📅 Hari (sekarang: " << dataJadwal[i].hari << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiHari(inputBaru);
                dataJadwal[i].hari = inputBaru;
            }

            cout << "🕐 Jam (sekarang: " << dataJadwal[i].jam << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiJam(inputBaru);
                dataJadwal[i].jam = inputBaru;
            }

            cout << "🧘 Jenis Kelas (sekarang: " << dataJadwal[i].jenisKelas << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiHurufSpasi(inputBaru, "Jenis kelas");
                dataJadwal[i].jenisKelas = inputBaru;
            }

            cout << "📌 Kategori (sekarang: " << dataJadwal[i].kategori << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiHurufSpasi(inputBaru, "Kategori");
                dataJadwal[i].kategori = inputBaru;
            }

            cout << "👩‍🏫 Instruktur (sekarang: " << dataJadwal[i].instruktur << "): ";
            getline(cin, inputBaru);
            if (!inputBaru.empty())
            {
                validasiHurufSpasi(inputBaru, "Instruktur");
                dataJadwal[i].instruktur = inputBaru;
            }

            cout << "💰 Harga (sekarang: " << formatRupiah(dataJadwal[i].harga) << "): Rp ";
            string hargaStr;
            getline(cin, hargaStr);
            if (!hargaStr.empty())
            {
                int hargaBaru = stoi(hargaStr);
                if (hargaBaru > 0)
                    dataJadwal[i].harga = hargaBaru;
            }

            cout << "👥 Kapasitas (sekarang: " << dataJadwal[i].kapasitas << "): ";
            string kapasitasStr;
            getline(cin, kapasitasStr);
            if (!kapasitasStr.empty())
            {
                int kapasitasBaru = stoi(kapasitasStr);
                if (kapasitasBaru > 0)
                    dataJadwal[i].kapasitas = kapasitasBaru;
            }

            simpanJadwal(dataJadwal, jumlahJadwal);

            loadingAnimation();
            cout << "✅ Data Jadwal Berhasil Diperbarui!\n\n";
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "\n❌ ID Jadwal tidak ditemukan.\n\n";
    }
}

void hapusJadwal(JadwalKelas *dataJadwal, int &jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||            🗑️ HAPUS JADWAL KELAS 🗑️            ||\n";
    cout << "====================================================\n";

    if (jumlahJadwal == 0)
    {
        cout << "❌ Data jadwal masih kosong!\n\n";
        return;
    }

    tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);
    cout << "\n";

    int idCari = inputInteger("🆔 Masukkan ID Jadwal yang ingin dihapus: ");
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
        cout << "\n🗑️ Menghapus jadwal: " << dataJadwal[indexKetemu].jenisKelas
             << " (" << dataJadwal[indexKetemu].kategori << ")"
             << " - " << dataJadwal[indexKetemu].hari
             << " " << dataJadwal[indexKetemu].jam << "\n";

        for (int i = indexKetemu; i < jumlahJadwal - 1; i++)
            dataJadwal[i] = dataJadwal[i + 1];
        jumlahJadwal--;

        simpanJadwal(dataJadwal, jumlahJadwal);

        loadingAnimation();
        cout << "✅ Jadwal Berhasil Dihapus!\n\n";
    }
    else
    {
        cout << "\n❌ ID tidak ditemukan.\n\n";
    }
}

void approvalBooking(Booking *dataBooking, int jumlahBooking, Akun *dataAkun, int jumlahAkun)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||             ✅ APPROVAL BOOKING ✅             ||\n";
    cout << "====================================================\n";

    if (jumlahBooking == 0)
    {
        cout << "❌ Belum ada data booking.\n\n";
        return;
    }

    cout << "\n";
    cout << "=====================================================================================\n";
    cout << left << setw(10) << "BookingID"
         << setw(18) << "Nama Member"
         << setw(10) << "MemberID"
         << setw(12) << "Kelas"
         << setw(18) << "Harga"
         << "Status" << endl;
    cout << "-------------------------------------------------------------------------------------\n";

    bool adaPending = false;
    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].status == "pending")
        {
            adaPending = true;
            cout << "    " << left << setw(10) << dataBooking[i].bookingID
                 << setw(18) << dataBooking[i].namaMember
                 << setw(10) << dataBooking[i].memberID
                 << setw(12) << dataBooking[i].jenisKelas
                 << setw(18) << "💰 " + formatRupiah(dataBooking[i].harga)
                 << "⏳ " << dataBooking[i].status << "\n";
        }
    }

    if (!adaPending)
    {
        cout << "✅ Tidak ada booking yang menunggu approval\n";
        cout << "=====================================================================================\n";
        return;
    }
    cout << "=====================================================================================\n";

    try
    {
        int bookingID = inputInteger("\n🆔 Masukkan Booking ID yang ingin diproses: ");

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
            throw runtime_error("❌ Booking ID tidak ditemukan atau sudah diproses!");

        cout << "\n========================================\n";
        cout << "||         📋 DETAIL BOOKING 📋       ||\n";
        cout << "========================================\n";
        cout << left << setw(15) << "🆔 Booking ID" << ": " << dataBooking[index].bookingID << "\n";
        cout << left << setw(15) << "👤 Nama Member" << ": " << dataBooking[index].namaMember << "\n";
        cout << left << setw(15) << "🧘 Kelas" << ": " << dataBooking[index].jenisKelas << "\n";
        cout << left << setw(15) << "💰 Harga" << ": " << formatRupiah(dataBooking[index].harga) << "\n";
        cout << "----------------------------------------\n";
        cout << "1. ✅ Approve\n";
        cout << "2. ❌ Reject\n";

        int pilihan = inputInteger("\n🎯 Pilihan (1/2): ");

        if (pilihan == 1)
        {
            dataBooking[index].status = "approved";
            loadingAnimation();
            cout << "✅ Booking berhasil di-approve!\n\n";
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
            cout << "❌ Booking di-reject! 💰 Saldo member dikembalikan.\n\n";
        }
        else
            throw out_of_range("❌ Pilihan tidak valid!");
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << "\n\n";
    }
}

void ProfilSaya(Akun *data, int jumlah, string namaLogin)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||                👤 PROFIL SAYA 👤               ||\n";
    cout << "====================================================\n";
    try
    {
        int index = cariusername(data, jumlah, namaLogin);
        if (index == -1)
            throw runtime_error("❌ Profil tidak ditemukan.");

        cout << "\n";
        cout << left << setw(12) << "🆔 ID" << ": " << data[index].id << "\n";
        cout << left << setw(12) << "👤 Nama" << ": " << data[index].nama << "\n";
        cout << left << setw(12) << "🔑 Password" << ": " << data[index].pw << "\n";
        cout << left << setw(12) << "💰 Saldo" << ": " << formatRupiah(data[index].saldo) << "\n";
        cout << "====================================================\n";

        cout << "\n🔧 Ingin mengubah password ?\n";
        cout << "   1. ✅ Ya, ganti password\n";
        cout << "   0. ❌ Tidak, kembali\n";

        int pilihan;
        bool validInput = false;
        while (!validInput)
        {
            try
            {
                pilihan = inputInteger("    Pilihan (1/0): ");
                if (pilihan != 1 && pilihan != 0)
                    throw out_of_range("❌ Pilihan harus 1 atau 0!");
                validInput = true;
            }
            catch (const exception &e)
            {
                cout << "❌ " << e.what() << " Silakan coba lagi.\n";
            }
        }

        if (pilihan == 1)
        {
            string pwBaru;
            cin.ignore(1000, '\n');
            cout << "🔑 Masukkan password baru: ";
            cin >> pwBaru;
            validasiPassword(pwBaru);
            data[index].pw = pwBaru;
            simpanAkun(data, jumlah);

            loadingAnimation();
            cout << "✅ Password berhasil diubah!\n\n";
        }
        else if (pilihan == 0)
        {
            cout << "\n⬅️ Kembali ke menu member...\n\n";
        }
    }
    catch (const exception &e)
    {
        cout << "\n❌ " << e.what() << "\n\n";
    }
}

void topUpSaldo(Akun *data, int jumlah, string namaLogin, TopUp *dataTopUp, int &jumlahTopUp, int maxTopUp)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||               💳 TOP UP SALDO 💳               ||\n";
    cout << "====================================================\n";

    try
    {
        int index = cariusername(data, jumlah, namaLogin);
        if (index == -1)
            throw runtime_error("❌ Akun tidak ditemukan!");
        cout << "💰 Saldo saat ini: ";
        cout << formatRupiah(data[index].saldo) << endl;
        cout << "----------------------------------------------------\n";

        int nominal = inputInteger("💵 Nominal top up: Rp ");
        if (nominal <= 0)
            throw invalid_argument("❌ Nominal harus lebih dari 0!");

        data[index].saldo += nominal;

        if (jumlahTopUp < maxTopUp)
        {
            dataTopUp[jumlahTopUp].namaMember = namaLogin;
            dataTopUp[jumlahTopUp].nominal = nominal;
            jumlahTopUp++;
        }

        loadingAnimation();
        cout << "✅ Top up berhasil!\n";
        cout << "💰 Saldo baru: ";
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
    cout << "||               📝 BOOKING KELAS 📝              ||\n";
    cout << "====================================================\n";

    try
    {
        validasiKapasitas(jumlahBooking, maxBooking);

        int indexMember = cariusername(data, jumlahAkun, namaLogin);
        if (indexMember == -1)
            throw runtime_error("❌ Akun tidak ditemukan!");

        if (jumlahJadwal == 0)
        {
            cout << "❌ Belum ada jadwal kelas tersedia.\n\n";
            return;
        }

        cout << "💰 Saldo Anda: ";
        cout << formatRupiah(data[indexMember].saldo) << endl;
        tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);

        int jadwalID = inputInteger("\n🆔 Masukkan ID Jadwal yang ingin dibooking: ");
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
            throw runtime_error("❌ ID Jadwal tidak ditemukan!");

        if (dataJadwal[indexJadwal].terisi >= dataJadwal[indexJadwal].kapasitas)
            throw runtime_error("⚠️ Kelas sudah penuh!");

        for (int i = 0; i < jumlahBooking; i++)
        {
            if (dataBooking[i].namaMember == namaLogin &&
                dataBooking[i].jadwalID == jadwalID &&
                (dataBooking[i].status == "pending" || dataBooking[i].status == "approved"))
            {
                throw runtime_error("⚠️ Anda sudah memiliki booking untuk jadwal ini!");
            }
        }

        int harga = dataJadwal[indexJadwal].harga;

        if (data[indexMember].saldo < harga)
            throw runtime_error("❌ Saldo tidak cukup! Silakan top up terlebih dahulu.");

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
        cout << "✅ Booking berhasil dibuat!\n\n";

        cout << "=============================================\n";
        cout << "||           📋 DETAIL BOOKING 📋          ||\n";
        cout << "=============================================\n\n";
        cout << "🆔 ID Booking   : " << newBookingID << endl;
        cout << "📅 Jadwal       : " << dataJadwal[indexJadwal].hari << ", " << dataJadwal[indexJadwal].jam << endl;
        cout << "🧘 Kelas        : " << dataJadwal[indexJadwal].jenisKelas << " (" << dataJadwal[indexJadwal].kategori << ")" << endl;
        cout << "👨‍🏫 Instruktur   : " << dataJadwal[indexJadwal].instruktur << endl;
        cout << "💰 Harga        : " << formatRupiah(harga) << endl;
        cout << "⏳ Status       : Menunggu Approval Admin" << endl;
        cout << "💵 Saldo Tersisa: " << formatRupiah(data[indexMember].saldo) << endl;
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
    cout << "====================================================\n";
    cout << "||           ❌ BATALKAN BOOKING KELAS ❌         ||\n";
    cout << "====================================================\n";
    cout << left << setw(20) << "ID Booking " << setw(20) << "Kelas" << setw(15) << "Harga" << "Status" << endl;
    cout << "----------------------------------------------------\n";

    bool adaPending = false;
    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].namaMember == namaLogin && dataBooking[i].status == "pending")
        {
            adaPending = true;
            cout << left << setw(20) << dataBooking[i].bookingID
                 << setw(20) << dataBooking[i].jenisKelas
                 << setw(15) << "💰 " + formatRupiah(dataBooking[i].harga)
                 << "⏳ " << dataBooking[i].status << endl;
        }
    }
    if (!adaPending)
    {
        cout << "----------------------------------------------------\n";
        throw runtime_error("❌ Tidak ada booking pending! ");
    }
    cout << "====================================================\n";
    try
    {
        int bookingID = inputInteger("\n🆔 Masukkan Booking ID yang ingin dibatalkan: ");
        int index = -1;
        for (int i = 0; i < jumlahBooking; i++)
        {
            if (dataBooking[i].bookingID == bookingID && dataBooking[i].namaMember == namaLogin && dataBooking[i].status == "pending")
            {
                index = i;
                break;
            }
        }
        if (index == -1)
            throw runtime_error("❌ Booking tidak ditemukan!");

        cout << "=============================================\n";
        cout << "||           📋 DETAIL BOOKING 📋          ||\n";
        cout << "=============================================\n\n";
        cout << "🆔 Booking ID  : " << dataBooking[index].bookingID << endl;
        cout << "🧘 Kelas       : " << dataBooking[index].jenisKelas << endl;
        cout << "💰 Harga       : " << formatRupiah(dataBooking[index].harga) << endl;
        cout << "⏳ Status      : " << dataBooking[index].status << endl;
        cout << "---------------------------------------------\n";

        dataBooking[index].status = "canceled";
        int indexMember = cariusername(dataAkun, jumlahAkun, namaLogin);
        if (indexMember != -1)
        {
            dataAkun[indexMember].saldo += dataBooking[index].harga;
            cout << "\n✅ Booking berhasil dibatalkan! 💰 Saldo dikembalikan.\n";
        }
    }
    catch (const exception &e)
    {
        cout << "❌ Error\n";
        cout << e.what() << "\n";
    }
}

void riwayatTransaksi(Booking *dataBooking, int jumlahBooking, TopUp *dataTopUp, int jumlahTopUp, string namaLogin)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "======================================================================\n";
    cout << "||                      📜 RIWAYAT TRANSAKSI 📜                     ||\n";
    cout << "======================================================================\n";

    cout << left << setw(20) << "Jenis Transaksi " << setw(20) << "Keterangan " << setw(35) << "Nominal " << setw(25) << "Status " << endl;
    cout << "----------------------------------------------------------------------\n";

    bool AdaData = false;
    for (int i = 0; i < jumlahTopUp; i++)
    {
        if (dataTopUp[i].namaMember == namaLogin)
        {
            AdaData = true;
            cout << left << setw(20) << "💳 Top Up" << setw(20) << "Saldo ditambah" << setw(35) << "➕ " + formatRupiah(dataTopUp[i].nominal) << setw(25) << "✅ Berhasil" << endl;
        }
    }
    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].namaMember == namaLogin)
        {
            AdaData = true;
            string keterangan = "Booking " + dataBooking[i].jenisKelas;

            string nominal;
            if (dataBooking[i].status == "approved")
                nominal = "➖ " + formatRupiah(dataBooking[i].harga);
            else if (dataBooking[i].status == "pending")
                nominal = "➖ " + formatRupiah(dataBooking[i].harga);
            else
                nominal = "➕ " + formatRupiah(dataBooking[i].harga);

            string status;
            if (dataBooking[i].status == "approved")
                status = "✅ Approved";
            else if (dataBooking[i].status == "pending")
                status = "⏳ Pending";
            else if (dataBooking[i].status == "canceled")
                status = "❌ Canceled";
            else
                status = "❌ Rejected";

            cout << left << setw(20) << "📝 Booking" << setw(20) << keterangan << setw(25) << nominal << setw(25) << status << endl;
        }
    }
    if (!AdaData)
        cout << "❌ Belum ada riwayat transaksi.  \n";
    cout << "----------------------------------------------------------------------\n";
}

int main()
{
    SetConsoleOutputCP(65001);

    const int MAX = 20;
    const int MAX_BOOKING = 50;
    const int MAX_JADWAL = 30;
    const int MAX_TOPUP = 100;

    Akun dataAkun[MAX];
    int jumlah = 0;

    Booking dataBooking[MAX_BOOKING];
    int jumlahBooking = 0;

    JadwalKelas dataJadwal[MAX_JADWAL];
    int jumlahJadwal = 0;

    TopUp dataTopUp[MAX_TOPUP];
    int jumlahTopUp = 0;

    muatAkun(dataAkun, jumlah);
    muatJadwal(dataJadwal, jumlahJadwal);

    if (jumlahJadwal == 0)
    {
        simpanJadwal(dataJadwal, jumlahJadwal);
    }

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
            cout << "              💪 >> STUDIO PILATES MANAGEMENT << 💪\n";
            setColor(10);
            cout << "                   Your Health, Our Priority! \n";
            setColor(7);
            cout << endl;

            cout << "============================================\n";
            cout << "||             🏠 MENU UTAMA 🏠           ||\n";
            cout << "============================================\n";
            cout << "1. 🔒 Login\n";
            cout << "2. 📝 Register\n";
            cout << "0. ❌ Keluar\n";
            cout << "--------------------------------------------\n";

            try
            {
                int pilihan = inputInteger("🎯 Pilih menu (1/2/0): ");
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
                    cout << "                  💪 Stay Healthy, Stay Strong! 💪\n\n";
                    programAktif = false;
                }
                else
                    throw out_of_range("❌ Pilihan tidak valid!");
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
                cout << "||            💼 MENU ADMIN 💼            ||\n";
                cout << "============================================\n";
                cout << "1. ➕ Tambah Member\n";
                cout << "2. 👀 Lihat Member\n";
                cout << "3. 🗑️  Hapus Member\n";
                cout << "4. ➕ Tambah Jadwal\n";
                cout << "5. 👀 Lihat Jadwal\n";
                cout << "6. ✏️  Update Jadwal\n";
                cout << "7. 🗑️  Hapus Jadwal\n";
                cout << "8. ✅ Approval Booking\n";
                cout << "0. 🚪 Logout\n";
                cout << "--------------------------------------------\n";

                try
                {
                    int pilihan = inputInteger("🎯 Pilih menu (0-8): ");
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
                        cout << "✅ Berhasil Logout!\n\n";
                        system("pause");
                    }
                    else
                        throw out_of_range("❌ Pilihan tidak valid!");
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
                cout << "||        👤 MENU MEMBER 👤               ||\n";
                cout << "============================================\n";
                cout << "1. 👁️  Lihat Profil Saya\n";
                cout << "2. 💳 Top Up Saldo\n";
                cout << "3. 📝 Booking Kelas\n";
                cout << "4. ❌ Batalkan Booking Kelas\n";
                cout << "5. 📜 Riwayat Transaksi\n";
                cout << "0. 🚪 Logout\n";
                cout << "--------------------------------------------\n";

                try
                {
                    int pilihan = inputInteger("🎯 Pilih menu: ");
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
                        cout << "✅ Berhasil Logout!\n\n";
                        system("pause");
                    }
                    else
                        throw out_of_range("❌ Pilihan tidak valid!");
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