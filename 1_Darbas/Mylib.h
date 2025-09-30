#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <stdexcept>   

using std::endl;
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::sort;
using std::accumulate;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::ifstream;
using std::cerr;
using std::getline;
using std::stringstream;
using std::runtime_error;

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
#endif // MYLIB_H_INCLUDED
