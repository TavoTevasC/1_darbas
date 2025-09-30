#include "Mylib.h"

int main() {
    vector<Studentas> grupe;

    cout << "Pasirinkite duomenu ivedimo buda:\n"
        << "1 - rankiniu budu\n"
        << "2 - generuoti atsitiktinius duomenis\n"
        << "3 - nuskaityti is failo (kursiokai.txt)\n";
    int budas;
    cin >> budas;

    // Duomenų įvedimas pagal pasirinkimą
    if (budas == 1) {
        int kiek;
        cout << "Kiek studentu ivesite? ";
        cin >> kiek;
        grupe.resize(kiek);

        for (int i = 0; i < kiek; i++) {
            cout << "\nStudentas #" << i + 1 << ":\n";
            grupe[i].ivedimas();
        }
    }
    else if (budas == 2) {
        int kiek;
        cout << "Kiek studentu generuoti? ";
        cin >> kiek;
        grupe.resize(kiek);

        for (int i = 0; i < kiek; i++) {
            cout << "\nStudentas #" << i + 1 << ":\n";
            grupe[i].generuotiDuomenis();
        }
    }
    else if (budas == 3) {
        grupe = Studentas::nuskaitytiIsFailo("kursiokai.txt");
        if (grupe.empty()) {
            cout << "Nera duomenu nuskaitymui is failo." << endl;
            return 1;
        }
    }
    else {
        cout << "Neteisingas pasirinkimas." << endl;
        return 1;
    }

    // Rusiavimas pagal vardą
    sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
        return a.getVardas() < b.getVardas();
        });


    // Lentelės antraštė
    cout << "\n"
        << left << setw(15) << "Vardas"
        << setw(15) << "Pavarde"
        << setw(18) << "Galutinis (Vid.)"
        << setw(18) << "Galutinis (Med.)"
        << "\n-------------------------------------------------------------\n";

    for (const auto& s : grupe) {
        s.isvedimas();
    }


    return 0;
}