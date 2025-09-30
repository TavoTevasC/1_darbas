#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>

using namespace std;

class Studentas {
    string vardas;
    string pavarde;
    vector<int>nd;
    int egz;
    double galutinis;

public:
    // Konstruktoriai
    Studentas() {
        vardas = "Tadas";
        pavarde = "Kazlauskas";
        nd = { 5,8,6,7,10,9,9,8,10,10 };
        egz = 10;
        skaiciuotiGalutinis();
    }

    Studentas(string A, string B, vector<int> C, int D) {
        vardas = A;
        pavarde = B;
        nd = C;
        egz = D;
        skaiciuotiGalutinis();
    }
    // Kopijavimo konstruktorius
    Studentas(const Studentas& other) {
        vardas = other.vardas;
        pavarde = other.pavarde;
        nd = other.nd;
        egz = other.egz;
        galutinis = other.galutinis;
    }
    // Priskyrimo operatorius
    Studentas& operator=(const Studentas& other) {
        if (this == &other) return *this;
        vardas = other.vardas;
        pavarde = other.pavarde;
        nd = other.nd;
        egz = other.egz;
        galutinis = other.galutinis;
        return *this;
    }
    // Destruktorius
    ~Studentas() {
        vardas.clear();
        pavarde.clear();
        nd.clear();
        egz = 0;
        galutinis = 0.0;
    }

    // Funkcija galutinio skaiciavimui
    void skaiciuotiGalutinis() {
        double vidurkis = accumulate(nd.begin(), nd.end(), 0) / nd.size();
        galutinis = 0.4 * vidurkis + 0.6 * egz;
    }

    //Duomenų įvedimas ir išvedimas
    friend istream& operator>>(istream& in, Studentas& s) {
        cout << "Iveskite varda: ";
        in >> s.vardas;
        cout << "Iveskite pavarde: ";
        in >> s.pavarde;

        s.skaiciuotiGalutinis();

        return in;
    }

    friend ostream& operator<<(ostream& out, const Studentas& s) {
        out << left << setw(15) << s.vardas
            << setw(15) << s.pavarde
            << fixed << setprecision(2) << s.galutinis;
        return out;
    }


};

int main() {
    int kiek;
    cout << "Kiek studentu ivesite? ";
    cin >> kiek;


    vector<Studentas> grupe(kiek);

    for (int i = 0; i < kiek; i++) {
        cout << "\nStudentas #" << i + 1 << ":\n";
        cin >> grupe[i];
    }

    // Lentelės antraštė
    cout << "\n"
        << left << setw(15) << "Vardas"
        << setw(15) << "Pavarde"
        << "Galutinis (Vid.)" << endl;
    cout << "--------------------------------------------------" << endl;

    // Rezultatų išvedimas
    for (const auto& s : grupe) {
        cout << s << endl;
    }

    return 0;
}