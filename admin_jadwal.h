#ifndef ADMIN_JADWAL_H
#define ADMIN_JADWAL_H

#include "utils.h"

void tambahJadwal(JadwalKelas *dataJadwal, int &jumlahJadwal, int maxJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "===========================================================\n";
    cout << "||               ➕ TAMBAH JADWAL KELAS ➕               ||\n";
    cout << "===========================================================\n";
    try
    {
        validasiKapasitas(jumlahJadwal, maxJadwal);
        string hariInput = pilihHari();
        string jamInput = inputJam();

        string jenisInput;
        cout << "🧘 Jenis Kelas (mat/reformer/cadillac/klinis/kontemporer): ";
        getline(cin, jenisInput);
        validasiJenis(jenisInput);

        string kategoriInput;
        cout << "📌 Kategori (private/reguler): ";
        getline(cin, kategoriInput);
        validasiKategori(kategoriInput);

        string instrukturInput;
        cout << "👩👨 Instruktur: ";
        getline(cin, instrukturInput);
        validasiHurufSpasi(instrukturInput, "Instruktur");
        if (instrukturInput.length() > 30)
            throw invalid_argument("❌ Nama instruktur terlalu panjang! Maksimal 30 karakter.");
        if (instrukturInput.length() < 3)
            throw invalid_argument("❌ Nama instruktur terlalu pendek! Minimal 3 karakter.");

        int hargaInput = inputInteger("💰 Harga Kelas: Rp ");
        if (kategoriInput == "private" && hargaInput < 500000)
            throw invalid_argument("❌ Harga untuk kelas private minimal Rp 500.000!");
        if (kategoriInput == "reguler" && hargaInput < 200000)
            throw invalid_argument("❌ Harga untuk kelas reguler minimal Rp 200.000!");

        int kapasitasInput = inputInteger("👥 Kapasitas Peserta: ");
        if (kategoriInput == "private" && kapasitasInput > 5)
            throw invalid_argument("❌ Kapasitas untuk kelas private maksimal 5!");
        if (kategoriInput == "reguler" && kapasitasInput > 20)
            throw invalid_argument("❌ Kapasitas untuk kelas reguler maksimal 20!");

        int newID = 1;
        for (int i = 0; i < jumlahJadwal; i++)
        {
            if (dataJadwal[i].jadwalID >= newID)
                newID = dataJadwal[i].jadwalID + 1;
        }
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
        cout << e.what() << "\n\n";
    }
}

void lihatJadwal(JadwalKelas *dataJadwal, int jumlahJadwal)
{
    system("cls");
    tampilkanLogoKecil();
    cout << "====================================================\n";
    cout << "||            📋 LIHAT JADWAL KELAS 📋            ||\n";
    cout << "====================================================\n";
    JadwalKelas temp[50];
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

    tampilkanDaftarJadwal(temp, jumlahJadwal);

    cout << "==========================================================================================================\n\n";
    cout << "🔍 Ingin mencari jadwal berdasarkan ID?\n";
    cout << "   1. ✅ Ya, cari jadwal\n";
    cout << "   0. ⬅️ Kembali\n";
    cout << "----------------------------------------------------\n";
    try
    {
        int pilihan = inputMenu(" 🎯 Pilihan (1/0): ");
        if (pilihan == 1)
        {
            system("cls");
            tampilkanLogoKecil();
            cout << "====================================================\n";
            cout << "||        🔎 CARI JADWAL BERDASARKAN ID 🔎        ||\n";
            cout << "====================================================\n";
            tampilkanDaftarJadwal(dataJadwal, jumlahJadwal);

            int targetID;
            targetID = inputInteger("\n🆔 Masukkan ID Jadwal yang dicari: ");
            validasiID(targetID);
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
                cout << "🆔 ID           : " << dataJadwal[hasil].jadwalID << endl;
                cout << "📅 Hari         : " << dataJadwal[hasil].hari << endl;
                cout << "🕐 Jam          : " << dataJadwal[hasil].jam << endl;
                cout << "🧘 Jenis        : " << dataJadwal[hasil].jenisKelas << endl;
                cout << "📌 Kategori     : " << dataJadwal[hasil].kategori << endl;
                cout << "👨‍🏫 Instruktur : " << dataJadwal[hasil].instruktur << endl;
                cout << "💰 Harga        : " << formatRupiah(dataJadwal[hasil].harga) << endl;
                cout << "👥 Kapasitas    : " << dataJadwal[hasil].terisi << "/" << dataJadwal[hasil].kapasitas << endl;
                cout << "===============================================\n";
            }
            else
                cout << "❌ Jadwal dengan ID " << targetID << " tidak ditemukan!\n\n";
        }
        else if (pilihan == 0)
        {
            cout << "🔙 Kembali ke menu utama...\n\n";
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
    cout << "||             ✏️ UPDATE JADWAL KELAS ✏️           ||\n";
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
            if (dataJadwal[i].terisi > 0)
            {
                cout << "\n╔══════════════════════════════════════════════════════╗\n";
                cout << "║             ❌ JADWAL TIDAK BISA DIHAPUS ❌          ║\n";
                cout << "╚══════════════════════════════════════════════════════╝\n";
                cout << "\n⚠️ Jadwal ini sudah memiliki " << dataJadwal[i].terisi << " peserta yang terisi.\n";
                cout << "💡 Jadwal hanya bisa diubah jika belum ada yang booking.\n\n";
                return;
            }

            cout << "\n===============================================\n";
            cout << "||          📝 MASUKKAN DATA BARU 📝         ||\n";
            cout << "===============================================\n";
            try
            {
                if (inputYesNo("📅 Ubah Hari? (y/n): "))
                {
                    dataJadwal[i].hari = pilihHari();
                }
                if (inputYesNo("🕐 Ubah Jam? (y/n): "))
                {
                    dataJadwal[i].jam = inputJam();
                }
                if (inputYesNo("🧘 Ubah Jenis Kelas? (y/n): "))
                {
                    string jenis;
                    cout << "🧘 Jenis Kelas Baru (Mat/Reformer/Cadillac/Klinis/Kontemporer): ";
                    getline(cin, jenis);
                    validasiJenis(jenis);
                    dataJadwal[i].jenisKelas = jenis;
                }
                if (inputYesNo("📌 Ubah Kategori? (y/n): "))
                {
                    string kategori;
                    cout << "📌 Kategori Baru (Private/Reguler): ";
                    getline(cin, kategori);
                    validasiKategori(kategori);
                    dataJadwal[i].kategori = kategori;
                }

                if (inputYesNo("👩 Ubah Instruktur? (y/n): "))
                {
                    string instruktur;
                    cout << "👩👨 Instruktur Baru: ";
                    getline(cin, instruktur);
                    validasiHurufSpasi(instruktur, "Instruktur", 3);
                    if (instruktur.length() > 30)
                        throw invalid_argument("❌ Nama instruktur terlalu panjang! Maksimal 30 karakter.");
                    dataJadwal[i].instruktur = instruktur;
                }

                if (inputYesNo("💰 Ubah Harga? (y/n): "))
                {
                    int hargaBaru = inputInteger("💰 Harga baru: Rp ");
                    if (dataJadwal[i].kategori == "private" && hargaBaru < 500000)
                        throw invalid_argument("❌ Harga untuk kelas private minimal Rp 500.000!\n");
                    if (dataJadwal[i].kategori == "reguler" && hargaBaru < 200000)
                        throw invalid_argument("❌ Harga untuk kelas reguler minimal Rp 200.000!\n");
                    dataJadwal[i].harga = hargaBaru;
                }

                if (inputYesNo("👥 Ubah Kapasitas? (y/n): "))
                {
                    int kapasitasBaru = inputInteger("👥 Kapasitas baru: ");
                    if (dataJadwal[i].kategori == "private" && kapasitasBaru > 5)
                        throw invalid_argument("❌ Kapasitas maksimal 5 untuk kelas private.\n");
                    if (dataJadwal[i].kategori == "reguler" && kapasitasBaru > 20)
                        throw invalid_argument("❌ Kapasitas maksimal 20 untuk kelas reguler.\n");
                    if (kapasitasBaru < dataJadwal[i].terisi)
                        throw invalid_argument("❌ Kapasitas baru tidak boleh kurang dari jumlah peserta yang sudah terisi!\n");
                    dataJadwal[i].kapasitas = kapasitasBaru;
                }

                simpanJadwal(dataJadwal, jumlahJadwal);
                loadingAnimation();
                cout << "✅ Data Jadwal Berhasil Diperbarui!\n\n";
                break;
            }
            catch (const exception &e)
            {
                cout << endl
                     << e.what() << "\n\n";
                break;
            }
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
        if (dataJadwal[indexKetemu].terisi > 0)
        {
            cout << "\n╔══════════════════════════════════════════════════════╗\n";
            cout << "║             ❌ JADWAL TIDAK BISA DIHAPUS ❌          ║\n";
            cout << "╚══════════════════════════════════════════════════════╝\n";
            cout << "\n⚠️ Jadwal ini sudah memiliki " << dataJadwal[indexKetemu].terisi << " peserta yang terisi.\n";
            cout << "💡 Jadwal hanya bisa dihapus jika belum ada yang booking.\n\n";
            return;
        }

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

void approvalBooking(Booking *dataBooking, int jumlahBooking, Akun *dataAkun, 
    int jumlahAkun, JadwalKelas *dataJadwal, int jumlahJadwal)
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
    cout << "========================================================================================\n";
    cout << left << setw(12) << "BookingID" << setw(16) << "Nama Member" << setw(15) << "MemberID"
         << setw(17) << "Kelas" << setw(17) << "Harga" << "Status" << endl;
    cout << "----------------------------------------------------------------------------------------\n";

    bool adaPending = false;
    for (int i = 0; i < jumlahBooking; i++)
    {
        if (dataBooking[i].status == "pending")
        {
            adaPending = true;
            cout << "  " << left << setw(12) << dataBooking[i].bookingID
                 << setw(16) << dataBooking[i].namaMember
                 << setw(10) << dataBooking[i].memberID
                 << setw(18) << dataBooking[i].jenisKelas
                 << setw(20) << "💰 " + formatRupiah(dataBooking[i].harga)
                 << "⏳ " << dataBooking[i].status << "\n";
        }
    }
    if (!adaPending)
    {
        cout << "✅ Tidak ada booking yang menunggu approval\n";
        cout << "========================================================================================\n";
        return;
    }
    cout << "========================================================================================\n";
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
        cout << "🆔 Booking ID" << "  : " << dataBooking[index].bookingID << "\n";
        cout << "👤 Nama Member" << ": " << dataBooking[index].namaMember << "\n";
        cout << "🧘 Kelas" << "       : " << dataBooking[index].jenisKelas << "\n";
        cout << "💰 Harga" << "       : " << formatRupiah(dataBooking[index].harga) << "\n";
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
            simpanAkun(dataAkun, jumlahAkun);
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

#endif