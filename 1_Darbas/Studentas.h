#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED
#include "Mylib.h"

class Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz{};
    double galutinisVidurkis{};
    double galutinisMediana{};

public:
    // Konstruktoriai
    Studentas();
    Studentas(string A, string B, vector<int> C, int D);

    // Geteriai
    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }

    // Kopijavimo konstruktorius
    Studentas(const Studentas& other);

    // Priskyrimo operatorius
    Studentas& operator=(const Studentas& other);

    // Destruktorius
    ~Studentas();

    // Atsitiktinis pažymių generavimas
    void generuotiDuomenis();

    // Duomenų įvedimas ranka
    void ivedimas();

    // Išvedimas
    void isvedimas() const;

    // Galutinio balo skaičiavimas
    void skaiciuotiGalutinis();

    // Duomenų nuskaitymas iš failo
    static vector<Studentas> nuskaitytiIsFailo(const string& failoVardas);
};

#endif // STUDENTAS_H_INCLUDED