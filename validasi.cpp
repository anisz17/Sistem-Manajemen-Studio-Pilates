#ifndef Validasi_H
#define Validasi_H

#include <string>
#include <cctype>
using namespace std;

bool isValidKelas(const string &kelas)
{
    string lowerKelas = kelas;
    for (char &c : lowerKelas)
        c = tolower(c);

    return (lowerKelas == "private" || lowerKelas == "reguler");
}

bool isInputAngka(const string &str)
{
    if (str.empty())
        return false;
    for (char c : str)
    {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

bool isUsernameValid(const string &nama)
{
    if (nama.empty())
        return false;
    if (nama[0] == ' ' || nama[nama.size() - 1] == ' ')
        return false;
    return true;
}

#endif