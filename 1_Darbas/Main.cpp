#include "Mylib.h"

int main() {
    vector<Studentas> grupe;

    try {
        cout << "Pasirinkite duomenu ivedimo buda:\n"
             << "1 - Rankiniu budu\n"
             << "2 - Generuoti atsitiktinius duomenis\n"
             << "3 - Nuskaityti is failo (kursiokai.txt)\n";

        int budas;
        if (!(cin >> budas)) {
            throw runtime_error("Netinkama ivestis!");
        }

        if (budas == 1) {
            int kiek;
            cout << "Kiek studentu ivesite? ";
            if (!(cin >> kiek) || kiek <= 0) throw runtime_error("Neteisingas kiekis!");
            grupe.resize(kiek);

            for (int i = 0; i < kiek; i++) {
                cout << "\nStudentas #" << i + 1 << ":\n";
                grupe[i].ivedimas();
            }
        }
        else if (budas == 2) {
            int kiek;
            cout << "Kiek studentu generuoti? ";
            if (!(cin >> kiek) || kiek <= 0) throw runtime_error("Neteisingas kiekis!");
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
            throw runtime_error("Neteisingas pasirinkimas!");
        }

        // Rusiavimas pagal vardą
        sort(grupe.begin(), grupe.end(), 
            [](const Studentas& a, const Studentas& b) {
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
    }
    catch (const std::exception& e) {
        cerr << "Klaida: " << e.what() << endl;
        return 1;
    }

    return 0;
}
