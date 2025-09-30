#include "Mylib.h"

    // Konstruktoriai
    Studentas::Studentas() {
        vardas = "Tadas";
        pavarde = "Kazlauskas";
        nd = { 5, 8, 6, 7, 10, 9, 9, 8, 10, 10 };
        egz = 10;
        skaiciuotiGalutinis();
    }

    Studentas::Studentas(string A, string B, vector<int> C, int D) {
        vardas = A;
        pavarde = B;
        nd = C;
        egz = D;
        skaiciuotiGalutinis();
    }

	// Geteriai
    string Studentas::getVardas() const { return vardas; }
	string Studentas::getPavarde() const { return pavarde; }


    // Kopijavimo konstruktorius
    Studentas::Studentas(const Studentas& other) = default;

    // Priskyrimo operatorius
    Studentas& Studentas::operator=(const Studentas& other) = default;

    // Destruktorius
    Studentas::~Studentas() = default;

    // Atsitiktinis pažymių generavimas
    void Studentas::generuotiDuomenis() {
        cout << "Iveskite varda: ";
        cin >> vardas;
        cout << "Iveskite pavarde: ";
        cin >> pavarde;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 10);

        int kiekNd;
        cout << "Kiek namu darbu pazymiu generuoti? ";
        cin >> kiekNd;

        nd.clear();
        for (int i = 0; i < kiekNd; i++) {
            nd.push_back(dist(gen));
        }

        egz = dist(gen);

        cout << "Sugeneruoti ND: ";
        for (int x : nd) cout << x << " ";
        cout << "\nSugeneruotas egzamino pazymis: " << egz << "\n";
        skaiciuotiGalutinis();
    }

    // Duomenų įvedimas ranka
    void Studentas::ivedimas() {
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

    // Išvedimas
    void Studentas::isvedimas() const {
        cout << left << setw(15) << vardas
            << setw(15) << pavarde
            << setw(18) << fixed << setprecision(2) << galutinisVidurkis
            << setw(18) << fixed << setprecision(2) << galutinisMediana
            << endl;
    }

    // Galutinio balo skaičiavimas
    void Studentas::skaiciuotiGalutinis() {
        double vidurkis = accumulate(nd.begin(), nd.end(), 0.0) / nd.size();
        galutinisVidurkis = 0.4 * vidurkis + 0.6 * egz;

        vector<int> temp = nd;
        sort(temp.begin(), temp.end());
        int n = temp.size();
        double mediana;
        if (n % 2 == 0)
            mediana = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
        else
            mediana = temp[n / 2];
        galutinisMediana = 0.4 * mediana + 0.6 * egz;
    }

    // Duomenų nuskaitymas iš failo
        vector<Studentas> Studentas::nuskaitytiIsFailo(const string& failoVardas) {
        ifstream in(failoVardas);
        vector<Studentas> grupe;

        if (!in.is_open()) {
            cerr << "Klaida atidarant faila!" << endl;
            return grupe;
        }

        string eilute;
        getline(in, eilute); 

        while (getline(in, eilute)) {
            stringstream ss(eilute);
            string vardas, pavarde;
            vector<int> nd;
            int paz;

            ss >> vardas >> pavarde;

            while (ss >> paz) {
                nd.push_back(paz);
            }

            if (nd.empty()) continue;

            int egz = nd.back();
            nd.pop_back();

            grupe.emplace_back(vardas, pavarde, nd, egz);
        }
        return grupe;
    }


