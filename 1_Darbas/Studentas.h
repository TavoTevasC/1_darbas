#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED
#include "Mylib.h"
#include "Timer.h"

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
	string getVardas() const { return vardas; } // Taikomas vardu rušiavimui
    string getPavarde() const { return pavarde; } // Taikomas vardu rušiavimui
	double getGalutinisVidurkis() const { return galutinisVidurkis; } // Taikomas rušiavimui į dvi grupes

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

// Duomenų generavimas į failą
class Generatorius {
public:
    static void generuotiFaila(const string& failoVardas, size_t kiekStud, int kiekNd = 5);
    static void generuotiVisus();
};

// Surušiuotu studentų sąrašo išvedimas į failus
void isvestiIFaila(const vector<Studentas>& sarasas, const string& failoVardas);


#endif // STUDENTAS_H_INCLUDED