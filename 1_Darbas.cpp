#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <random>

using namespace std;

class Studentas {
    string vardas;
    string pavarde;
    vector<int>nd;
    int egz;
    double galutinisVidurkis;
	double galutinisMediana;

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
        galutinisVidurkis = other.galutinisVidurkis;
		galutinisMediana = other.galutinisMediana;
    }
    // Priskyrimo operatorius
    Studentas& operator=(const Studentas& other) {
        if (this == &other) return *this;
        vardas = other.vardas;
        pavarde = other.pavarde;
        nd = other.nd;
        egz = other.egz;
        galutinisVidurkis = other.galutinisVidurkis;
		galutinisMediana = other.galutinisMediana;
        return *this;
    }
    // Destruktorius
    ~Studentas() {}

    

	// Atsitiktinis pažymių generavimas
    void generuotiDuomenis() {
        cout << "Iveskite varda: ";
        cin >> vardas;
        cout << "Iveskite pavarde: ";
        cin >> pavarde;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 10);

        int kiekNd;
        std::cout << "Kiek namu darbu pazymiu generuoti? ";
        std::cin >> kiekNd;

        nd.clear();
        for (int i = 0; i < kiekNd; i++) {
            nd.push_back(dist(gen));
        }

        egz = dist(gen);

        std::cout << "Sugeneruoti ND: ";
        for (int x : nd) std::cout << x << " ";
        std::cout << "\nSugeneruotas egzamino pazymis: " << egz << "\n";
		skaiciuotiGalutinis();

    }

    //Duomenų įvedimas ir išvedimas
    void ivedimas() {
        cout << "Iveskite varda: ";
        cin >> vardas;
        cout << "Iveskite pavarde: ";
        cin >> pavarde;
        cout << "Kiek namu darbu pazymiu ivesite? ";
        int n; cin >> n;
        nd.resize(n);
        cout << "Iveskite " << n << " pazymius: ";
        for (int i = 0; i < n; i++) {
            cin >> nd[i];
        }
        cout << "Iveskite egzamino pazymi: ";
        cin >> egz;
        skaiciuotiGalutinis();
      
	}
    
    
	// Išvedimas pagal pasirinkimą
    void isvedimas(int pasirinkimas) const {
        cout << left << setw(15) << vardas
			<< setw(15) << pavarde;
        if (pasirinkimas == 1) {
            cout << fixed << setprecision(2) << galutinisVidurkis << endl;
        } else {
            cout << fixed << setprecision(2) << galutinisMediana << endl;
		}
	}
	
    // Funkcija galutinio skaiciavimui
    void skaiciuotiGalutinis() {
        double vidurkis = accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
        galutinisVidurkis = 0.4 * vidurkis + 0.6 * egz;

        double mediana;
        sort(nd.begin(), nd.end());
        int n = nd.size();
        if (n % 2 == 0)
            mediana = (nd[n / 2 - 1] + nd[n / 2]) / 2.0;
        else
            mediana = nd[n / 2];
        galutinisMediana = 0.4 * mediana + 0.6 * egz;
    }

};

int main() {
    int kiek;
    cout << "Kiek studentu ivesite? ";
    cin >> kiek;


    vector<Studentas> grupe(kiek);

    for (int i = 0; i < kiek; i++) {
		int budas;
        cout << "\nStudentas #" << i + 1 << ": pasirinkite duomenu ivedimo buda:\n"
            << "1 - rankiniu budu\n"
			<< "2 - atsitiktiniu budu\n";
		cin >> budas;

		if (budas == 1) 
			grupe[i].ivedimas();
		else 
			grupe[i].generuotiDuomenis();
        
    }
    
	// Pasirinkimas, pagal ka skaiciuoti galutini
    int pasirinkimas;
    cout << "Pasirinkite isvedima:\n"
        << "1 - galutinis pagal vidurki\n"
        << "2 - galutinis pagal mediana\n";
	cin >> pasirinkimas;


    // Lentelės antraštė
    cout << "\n"
        << left << setw(15) << "Vardas"
        << setw(15) << "Pavarde";
    if (pasirinkimas == 1) {
        cout << "Galutinis (Vid.)" << endl;
    } else{
		cout << "Galutinis (Med.)" << endl;
	}
    cout << "--------------------------------------------------" << endl;

    // Rezultatų išvedimas
    for (const auto& s : grupe) {
        s.isvedimas(pasirinkimas);
    }

    return 0;
}