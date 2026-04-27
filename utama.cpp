#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
using namespace std;

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

void validasiKelas(const string &kelas)
{
    if (kelas != "private" && kelas != "Private" && kelas != "PRIVATE" &&
        kelas != "reguler" && kelas != "Reguler" && kelas != "REGULER")
        throw invalid_argument("Kelas tidak valid! Pilih 'private' atau 'reguler'.");
}

void validasiUsername(const string &nama)
{
    if (nama.empty() || nama == " ")
        throw invalid_argument("Username tidak boleh kosong!");
}

void validasiPassword(const string &pw)
{
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

void cetakGaris(char karakter = '=', int panjang = 50)
{
    for (int i = 0; i < panjang; i++)
        cout << karakter;
    cout << endl;
}

void cetakHeader(const string &judul)
{
    cetakGaris('=', 50);
    int spasi = (50 - (int)judul.length()) / 2;
    for (int i = 0; i < spasi; i++)
        cout << " ";
    cout << judul << endl;
    cetakGaris('=', 50);
}

struct Kelas
{
    string jenis;
    int harga;
};

struct Akun
{
    string nama;
    string pw;
    string role;
    Kelas kelas;
    int id;
    int saldo;
};

struct JadwalKelas
{
    int jadwalID;
    string namaKelas;
    string jenisKelas;
    string hari;
    string waktu;
    string instruktur;
    int kapasitas;
    int terisi;
};

struct Booking
{
    int bookingID;
    string namaMember;
    int memberID;
    string jenisKelas;
    int harga;
    string status;
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
    cetakGaris('=', 64);
    cout << "                       DAFTAR MEMBER\n";
    cetakGaris('=', 64);
    cout << left << setw(8) << "ID" << setw(15) << "Nama" << setw(15) << "Kelas" << "Harga" << endl;
    cetakGaris('=', 64);
    bool ada = false;
    for (int i = 0; i < jumlah; i++)
    {
        if (data[i].role == "member")
        {
            ada = true;
            cout << left << setw(8) << data[i].id << setw(15) << data[i].nama;
            cout << setw(15) << data[i].kelas.jenis << formatRupiah(data[i].kelas.harga) << "\n";
        }
    }
    if (!ada)
        cout << "Belum ada data member terdaftar \n";
    cetakGaris('=', 64);
}

void login(Akun *data, int jumlah, bool &statusLogin, string &namaLogin, string &roleLogin)
{
    system("cls");
    cetakHeader("LAMAN LOGIN");
    string inputNama, inputpw;
    int kesempatan = 3;

    while (kesempatan > 0)
    {
        try
        {
            cin.ignore(1000, '\n');
            cout << "Masukkan Nama (Username) : ";
            getline(cin, inputNama);
            validasiUsername(inputNama);
            cout << "Masukkan Password        : ";
            cin >> inputpw;

            int index = cariusername(data, jumlah, inputNama);
            if (index != -1 && data[index].pw == inputpw)
            {
                statusLogin = true;
                namaLogin = data[index].nama;
                roleLogin = data[index].role;
                cout << "\nLogin berhasil. Halo " << namaLogin << " sebagai " << roleLogin << "!\n";
                system("pause");
                return;
            }
            else
            {
                kesempatan--;
                if (kesempatan > 0)
                    cout << "\nLogin Gagal! Nama atau Password salah.\n"
                         << "Sisa kesempatan: " << kesempatan << "\n";
                else
                {
                    cout << "\nKesempatan Anda Habis. Annyeong\n";
                    system("pause");
                }
            }
        }
        catch (const exception &e)
        {
            cout << "\n"
                 << e.what() << "\n";
            kesempatan--;
            if (kesempatan > 0)
                cout << "Sisa kesempatan: " << kesempatan << "\n";
            else
            {
                cout << "Kesempatan Habis.\n";
                system("pause");
            }
        }
    }
}

void registrasi(Akun *data, int &jumlah, int maxKapasitas)
{
    system("cls");
    cetakHeader("REGISTRASI AKUN");
    cin.ignore(1000, '\n');
    try
    {
        validasiKapasitas(jumlah, maxKapasitas);
        string namaBaru, pwBaru, kelasBaru;
        cout << "Masukkan Nama (Username)     : ";
        getline(cin, namaBaru);
        validasiUsername(namaBaru);
        if (cariusername(data, jumlah, namaBaru) != -1)
            throw runtime_error("Username sudah terdaftar. Gunakan username lain.");

        cout << "Masukkan Password            : ";
        cin >> pwBaru;
        validasiPassword(pwBaru);
        cout << "\nRegistrasi Berhasil! Silakan Login.\n";
    }
    catch (const exception &e)
    {
        cout << "\n"
             << e.what() << "\n";
    }
}

void tambahMember(Akun *data, int &jumlah, int maxKapasitas)
{
    system("cls");
    cetakHeader("TAMBAH MEMBER");
    cin.ignore(1000, '\n');
    try
    {
        validasiKapasitas(jumlah, maxKapasitas);

        string namaBaru, pwBaru, kelasBaru;
        cout << "Nama Member (Username)  : ";
        getline(cin, namaBaru);
        validasiUsername(namaBaru);

        if (cariusername(data, jumlah, namaBaru) != -1)
            throw runtime_error("Username sudah terdaftar.");

        cout << "Password Member         : ";
        cin >> pwBaru;
        validasiPassword(pwBaru);

        cout << "Kelas (private/reguler) : ";
        cin >> kelasBaru;
        validasiKelas(kelasBaru);

        int newID = 1;
        for (int i = 0; i < jumlah; i++)
            if (data[i].role == "member" && data[i].id >= newID)
                newID = data[i].id + 1;

        int hargaKelas = (kelasBaru == "private" || kelasBaru == "Private" || kelasBaru == "PRIVATE") ? 1000000 : 450000;
        data[jumlah] = {namaBaru, pwBaru, "member", {kelasBaru, hargaKelas}, newID, 0};
        jumlah++;
        cout << "\nMember berhasil ditambahkan!\n";
    }
    catch (const exception &e)
    {
        cout << "\n"
             << e.what() << "\n";
    }
}

void lihatMember(Akun *data, int jumlah)
{
    bool kembali = false;
    while (!kembali)
    {
        system("cls");
        cetakHeader("LIHAT DATA MEMBER");
        cout << "1. Urutkan Kelas (Ascending)\n";
        cout << "2. Cari Member Berdasarkan ID\n";
        cout << "0. Kembali\n";
        cetakGaris('-', 50);
        try
        {
            int pilihan = inputInteger("Pilih (0-2): ");

            if (pilihan == 0)
            {
                kembali = true;
                continue;
            }

            system("cls");
            Akun temp[20];
            int memberCount = 0;
            for (int i = 0; i < jumlah; i++)
                if (data[i].role == "member")
                    temp[memberCount++] = data[i];

            if (memberCount == 0)
                throw runtime_error("Belum ada data member.");

            if (pilihan == 1)
            {
                // Insertion Sort - Kelas Ascending
                for (int i = 1; i < memberCount; i++)
                {
                    Akun key = temp[i];
                    int j = i - 1;
                    while (j >= 0 && temp[j].kelas.jenis > key.kelas.jenis)
                    {
                        temp[j + 1] = temp[j];
                        j--;
                    }
                    temp[j + 1] = key;
                }

                cetakGaris('=', 64);
                cout << "                       DAFTAR MEMBER\n";
                cetakGaris('=', 64);
                cout << left << setw(8) << "ID" << setw(15) << "Nama" << setw(15) << "Kelas" << "Harga" << endl;
                cetakGaris('=', 64);
                for (int i = 0; i < memberCount; i++)
                    cout << left << setw(8) << temp[i].id << setw(15) << temp[i].nama
                         << setw(15) << temp[i].kelas.jenis
                         << formatRupiah(temp[i].kelas.harga) << "\n";
                cetakGaris('=', 64);
                system("pause");
            }
            else if (pilihan == 2)
            {
                system("cls");
                cetakHeader("CARI MEMBER BERDASARKAN ID");
                cout << "           (Linear Search)\n";
                tampilkanDaftarMember(data, jumlah);

                int targetID = inputInteger("\nMasukkan ID member yang dicari: ");
                validasiID(targetID);

                // Linear Search
                cout << "\nTarget ID: " << targetID << endl;
                cetakGaris('-', 35);
                int jumlahDiperiksa = 0;
                int hasil = -1;
                for (int i = 0; i < jumlah; i++)
                {
                    if (data[i].role == "member")
                    {
                        jumlahDiperiksa++;
                        cout << "Cek member ke-" << jumlahDiperiksa << ": ID " << data[i].id;
                        if (data[i].id == targetID)
                        {
                            cout << " ==> COCOK!" << endl;
                            hasil = i;
                            break;
                        }
                        else
                            cout << " (tidak cocok)" << endl;
                    }
                }
                cetakGaris('-', 35);

                if (hasil != -1)
                {
                    cout << "Ditemukan setelah " << jumlahDiperiksa << " pengecekan!\n";
                    cetakGaris('=', 64);
                    cout << "                   MEMBER DITEMUKAN!\n";
                    cetakGaris('=', 64);
                    cout << left << setw(15) << "ID" << ": " << data[hasil].id << endl;
                    cout << left << setw(15) << "Nama" << ": " << data[hasil].nama << endl;
                    cout << left << setw(15) << "Kelas" << ": " << data[hasil].kelas.jenis << endl;
                    cout << left << setw(15) << "Harga" << ": " << formatRupiah(data[hasil].kelas.harga) << endl;
                    cetakGaris('=', 64);
                }
                else
                    cout << "Member dengan ID " << targetID << " tidak ditemukan!\n";

                system("pause");
            }
            else
                throw out_of_range("Pilihan tidak valid!");
        }
        catch (const exception &e)
        {
            cout << "\n"
                 << e.what() << "\n";
            system("pause");
        }
    }
}

void hapusMember(Akun *data, int &jumlah)
{
    tampilkanDaftarMember(data, jumlah);
    try
    {
        int IDHapus = inputInteger("\nMasukkan ID member yang ingin dihapus: ");
        validasiID(IDHapus);

        int index = cariID(data, jumlah, IDHapus);
        if (index == -1)
            throw runtime_error("Member dengan ID tersebut tidak ditemukan!");

        for (int j = index; j < jumlah - 1; j++)
            data[j] = data[j + 1];
        jumlah--;
        cout << "\nData member berhasil dihapus!\n";
    }
    catch (const exception &e)
    {
        cout << "\n"
             << e.what() << "\n";
    }
}

void tambahJadwal(JadwalKelas *dataJadwal, int &jumlahJadwal, int maxJadwal)
{
    cout << "Halo halo";
    system("cls");
    cetakHeader("TAMBAH JADWAL KELAS");
}

void lihatJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    cetakHeader("JADWAL KELAS");
}

void updateJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    cetakHeader("UPDATE JADWAL KELAS");
}

void hapusJadwal(JadwalKelas *dataJadwal, int &jumlahJadwal)
{
    system("cls");
    cetakHeader("HAPUS JADWAL KELAS");
}

void approvalBooking(Booking *dataBooking, int jumlahBooking, Akun *dataAkun, int jumlahAkun)
{
    system("cls");
    cetakHeader("APPROVAL BOOKING");

    if (jumlahBooking == 0)
    {
        cout << "Belum ada data booking.\n";
        return;
    }
    cetakGaris('=', 80);
    cout << left << setw(10) << "Booking ID" << setw(15) << "Nama Member"
         << setw(12) << "Member ID" << setw(15) << "Kelas"
         << setw(15) << "Harga" << "Status" << endl;
    cetakGaris('=', 80);

    bool adaPending = false;
    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].status == "pending")
        {
            adaPending = true;
            cout << left << setw(10) << dataBooking[i].bookingID
                 << setw(15) << dataBooking[i].namaMember
                 << setw(12) << dataBooking[i].memberID
                 << setw(15) << dataBooking[i].jenisKelas
                 << setw(15) << formatRupiah(dataBooking[i].harga)
                 << dataBooking[i].status << endl;
        }
    }

    if (!adaPending)
    {
        cout << "       [ Tidak ada booking yang menunggu approval ]\n";
        cetakGaris('=', 80);
        return;
    }
    cetakGaris('=', 80);

    try
    {
        int bookingID = inputInteger("\nMasukkan Booking ID yang ingin di-approve/reject: ");

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

        cout << "\nDetail Booking:\n";
        cout << "Booking ID  : " << dataBooking[index].bookingID << endl;
        cout << "Nama Member : " << dataBooking[index].namaMember << endl;
        cout << "Kelas       : " << dataBooking[index].jenisKelas << endl;
        cout << "Harga       : " << formatRupiah(dataBooking[index].harga) << endl;
        cetakGaris('-', 50);
        cout << "1. Approve\n";
        cout << "2. Reject\n";

        int pilihan = inputInteger("Pilihan (1/2): ");

        if (pilihan == 1)
        {
            dataBooking[index].status = "approved";
            cout << "\nBooking berhasil di-approve!\n";
        }
        else if (pilihan == 2)
        {
            dataBooking[index].status = "rejected";

            int indexMember = cariusername(dataAkun, jumlahAkun, dataBooking[index].namaMember);
            if (indexMember != -1)
            {
                dataAkun[indexMember].saldo += dataBooking[index].harga;
                cout << "\nBooking di-reject! Saldo member dikembalikan.\n";
            }
        }
        else
            throw out_of_range("Pilihan tidak valid!");
    }
    catch (const exception &e)
    {
        cout << "\n"
             << e.what() << "\n";
    }
}

void ProfilSaya(Akun *data, int jumlah, string namaLogin)
{
    system("cls");
    cetakHeader("PROFIL SAYA");
}

void topUpSaldo(Akun *data, int jumlah, string namaLogin)
{
    system("cls");
    cetakHeader("TOP UP SALDO");
    try
    {
        int index = cariusername(data, jumlah, namaLogin);
        if (index == -1)
            throw runtime_error("Akun tidak ditemukan!");

        cout << "Saldo saat ini: " << formatRupiah(data[index].saldo) << endl;
        cetakGaris('-', 50);

        int nominal = inputInteger("Masukkan nominal top up: Rp ");
        if (nominal <= 0)
            throw invalid_argument("Nominal harus lebih dari 0!");

        data[index].saldo += nominal;
        cout << "\nTop up berhasil!" << endl;
        cout << "Saldo baru: " << formatRupiah(data[index].saldo) << endl;
    }
    catch (const exception &e)
    {
        cout << "\n"
             << e.what() << "\n";
    }
}

void bookingKelas(Akun *data, int jumlahAkun, string namaLogin, Booking *dataBooking, int &jumlahBooking, int maxBooking)
{
    system("cls");
    cetakHeader("BOOKING KELAS");
    try
    {
        validasiKapasitas(jumlahBooking, maxBooking);

        int indexMember = cariusername(data, jumlahAkun, namaLogin);
        if (indexMember == -1)
            throw runtime_error("Akun tidak ditemukan!");

        cout << "Saldo Anda: " << formatRupiah(data[indexMember].saldo) << endl;
        cetakGaris('-', 50);
        cout << "Pilihan Kelas:\n";
        cout << "1. Private  - " << formatRupiah(1000000) << endl;
        cout << "2. Reguler  - " << formatRupiah(450000) << endl;
        cetakGaris('-', 50);

        int pilihan = inputInteger("Pilih kelas (1/2): ");
        string jenisKelas;
        int harga;

        if (pilihan == 1)
        {
            jenisKelas = "private";
            harga = 1000000;
        }
        else if (pilihan == 2)
        {
            jenisKelas = "reguler";
            harga = 450000;
        }
        else
            throw out_of_range("Pilihan tidak valid!");

        if (data[indexMember].saldo < harga)
            throw runtime_error("Saldo tidak cukup! Silakan top up terlebih dahulu.");
        int newBookingID = 1;
        for (int i = 0; i < jumlahBooking; i++)
            if (dataBooking[i].bookingID >= newBookingID)
                newBookingID = dataBooking[i].bookingID + 1;

        data[indexMember].saldo -= harga;

        dataBooking[jumlahBooking] = {
            newBookingID,
            namaLogin,
            data[indexMember].id,
            jenisKelas,
            harga,
            "pending"};
        jumlahBooking++;

        cout << "\nBooking berhasil dibuat!" << endl;
        cout << "ID Booking  : " << newBookingID << endl;
        cout << "Kelas       : " << jenisKelas << endl;
        cout << "Harga       : " << formatRupiah(harga) << endl;
        cout << "Status      : Menunggu Approval Admin" << endl;
        cout << "Saldo tersisa: " << formatRupiah(data[indexMember].saldo) << endl;
    }
    catch (const exception &e)
    {
        cout << "\n"
             << e.what() << "\n";
    }
}

void riwayatTransaksi(Booking *dataBooking, int jumlahBooking, string namaLogin)
{
    system("cls");
    cetakHeader("RIWAYAT TRANSAKSI");
}

int main()
{
    const int MAX = 20;
    const int MAX_BOOKING = 50;
    const int MAX_JADWAL = 30;

    Akun dataAkun[MAX];
    int jumlah = 2;
    dataAkun[0] = {"annisa", "078", "admin", {"", 0}, 0, 0};
    dataAkun[1] = {"juun", "0412", "member", {"reguler", 450000}, 1, 100000};

    Booking dataBooking[MAX_BOOKING];
    int jumlahBooking = 0;

    JadwalKelas dataJadwal[MAX_JADWAL];
    int jumlahJadwal = 0;

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
            cetakHeader("STUDIO PILATES MANIAK");
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "3. Keluar\n";
            cetakGaris('-', 50);
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
                else if (pilihan == 3)
                {
                    programAktif = false;
                    cout << "Terima Kasih Telah Berkunjung!\n";
                }
                else
                    throw out_of_range("Pilihan tidak valid!");
            }
            catch (const exception &e)
            {
                cout << "\n"
                     << e.what() << "\n";
                system("pause");
            }
        }
        else
        {
            if (roleLogin == "admin")
            {
                system("cls");
                cetakHeader("MENU ADMIN");
                cout << "1. Tambah Member (Create)\n";
                cout << "2. Lihat Member (Read)\n";
                cout << "3. Hapus Member (Delete)\n";
                cout << "4. Tambah Jadwal (Create)\n";
                cout << "5. Lihat Jadwal (Read)\n";
                cout << "6. Update Jadwal (Update)\n";
                cout << "7. Hapus Jadwal (Delete)\n";
                cout << "8. Approval Booking\n";
                cout << "0. Logout\n";
                cetakGaris('-', 50);
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
                        system("cls");
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
                        cout << "Berhasil Logout!\n";
                        system("pause");
                    }
                    else
                        throw out_of_range("Pilihan tidak valid!");
                }
                catch (const exception &e)
                {
                    cout << "\n"
                         << e.what() << "\n";
                    system("pause");
                }
            }
            else if (roleLogin == "member")
            {
                system("cls");
                cetakHeader("MENU MEMBER");
                cout << "1. Lihat Profil Saya\n";
                cout << "2. Top Up Saldo\n";
                cout << "3. Booking Kelas\n";
                cout << "4. Riwayat Transaksi\n";
                cout << "0. Logout\n";
                cetakGaris('-', 50);
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
                        topUpSaldo(ptrAkun, jumlah, namaLogin);
                        system("pause");
                    }
                    else if (pilihan == 3)
                    {
                        bookingKelas(ptrAkun, jumlah, namaLogin, dataBooking, jumlahBooking, MAX_BOOKING);
                        system("pause");
                    }
                    else if (pilihan == 4)
                    {
                        riwayatTransaksi(dataBooking, jumlahBooking, namaLogin);
                        system("pause");
                    }
                    else if (pilihan == 0)
                    {
                        statusLogin = false;
                        namaLogin = "";
                        roleLogin = "";
                        cout << "Berhasil Logout!\n";
                        system("pause");
                    }
                    else
                        throw out_of_range("Pilihan tidak valid!");
                }
                catch (const exception &e)
                {
                    cout << "\n"
                         << e.what() << "\n";
                    system("pause");
                }
            }
        }
    }
    return 0;
}