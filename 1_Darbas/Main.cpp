#include "Studentas.h"
#define NOMINMAX
#ifdef max
#undef max
#endif


// Generuoti N studentų duomenis į konteinerį
template <typename Container>
Container generateStudents(size_t N, int ndCount = 5) {
    Container c;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);
    for (size_t i = 1; i <= N; ++i) {
        string vard = "Vardas" + to_string(i);
        string pav = "Pavarde" + to_string(i);
        vector<int> nd;
        nd.reserve(ndCount);
        for (int j = 0; j < ndCount; ++j) nd.push_back(dist(gen));
        int egz = dist(gen);
        c.push_back(Studentas(vard, pav, nd, egz));
    }
    return c;
} 


// 1 Strategija: Skaidymas į du to paties tipo kontienerius
template <typename Container>
void run_strategy1(const Container& orig, const string& name) {
    Timer t;
    size_t memBefore = getProcessMemoryKB();
    t.reset();
    Container vargsiukai;
    Container galvociai;
    for (const auto& s : orig) {
        if (s.getGalutinisVidurkis() < 5.0)
            vargsiukai.push_back(s);
        else
            galvociai.push_back(s);
    }
    double elapsed = t.elapsed();
    size_t memAfter = getProcessMemoryKB();

    cout << "[1 Strategija] Konteineris: " << name << "\n";
    cout << "  Laikas: " << elapsed << " s, Papildomos atminties poreikis: " << (memAfter >= memBefore ? memAfter - memBefore : 0) << " KB\n";
}

// 2 Strategija: Naudojam tik vieną konteinerį, perkeliam elementus
template <typename Container>
void run_strategy2(Container orig, const string& name) {
    Timer t;
    size_t memBefore = getProcessMemoryKB();
    t.reset();
    Container vargsiukai;

    if constexpr (is_same<Container, list<Studentas>>::value) {
        for (auto it = orig.begin(); it != orig.end(); ) {
            if (it->getGalutinisVidurkis() < 5.0) {
                auto cur = it++;
                vargsiukai.splice(vargsiukai.end(), orig, cur);
            } else {
                ++it;
            }
        }
    } else {
        auto predGalvociai = [](const Studentas& s){ return s.getGalutinisVidurkis() >= 5.0; };
        auto it = stable_partition(orig.begin(), orig.end(), predGalvociai);
		// Perkelia vargsiukus i nauja konteineri
        vargsiukai.insert(vargsiukai.end(), make_move_iterator(it), make_move_iterator(orig.end()));
        orig.erase(it, orig.end());
    }

    double elapsed = t.elapsed();
    size_t memAfter = getProcessMemoryKB();

    cout << "[2 Strategija] Konteineris: " << name << "\n";
    cout << "  Laikas: " << elapsed << " s, Papildomos atminties poreikis: " << (memAfter >= memBefore ? memAfter - memBefore : 0) << " KB\n";
}


int main() {
    vector<Studentas> grupe;
    vector<Studentas> nuskriaustukai;
    vector<Studentas> galvociai;
    Timer time;
    double tGen = 0, tRead = 0, tSort = 0, tWrite = 0;

    cout << "Programa pradeda darba..." << endl;

    try {
        bool veikia = true;
        while (veikia) {
            cout << "\nPasirinkite duomenu ivedimo buda:\n"
                << "1 - Rankiniu budu\n"
                << "2 - Generuoti atsitiktinius duomenis\n"
                << "3 - Nuskaityti is failo (kursiokai.txt)\n"
                << "4 - Generuoti duomenis i failus (studentai_1000.txt, studentai_10000.txt, ...)\n"
                << "5 - Vykdyti spartos testavima (vector, deque, list, abi strategijos)\n"
                << "0 - Baigti darba\n"
                << "Kad pradeti darba, iveskite pasirinkimo numeri ir paspauskite (ENTER): ";

            int budas;
            if (!(cin >> budas)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Netinkama ivestis! Bandykite dar karta.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            switch (budas) {
				// Išeiti iš programos
            case 0:
                cout << "Programa baigia darba. Iki!" << endl;
                veikia = false;
                break;

                // Rankinis įvedimas 
            case 1: {
                int kiek;
                cout << "Kiek studentu ivesite? ";
                if (!(cin >> kiek) || kiek <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw runtime_error("Neteisinga ivestis! Programa baigia darba.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                grupe.resize(kiek);
                for (int i = 0; i < kiek; i++) {
                    cout << "\nStudentas #" << i + 1 << ":\n";
                    grupe[i].ivedimas();
                }

                // Lentelės antraštė
                cout << "\n"
                    << left << setw(15) << "Vardas"
                    << setw(15) << "Pavarde"
                    << setw(18) << "Galutinis (Vid.)"
                    << setw(18) << "Galutinis (Med.)"
                    << "\n-------------------------------------------------------------\n";

                // Rūšiavimas pagal vardą
                sort(grupe.begin(), grupe.end(),
                    [](const Studentas& a, const Studentas& b) {
                        return a.getVardas() < b.getVardas();
                    });

                for (const auto& s : grupe)
                    s.isvedimas();
                break;
            }

                  // Atsitiktinis generavimas
            case 2: {
                int kiek;
                cout << "Kiek studentu generuoti? ";
                if (!(cin >> kiek) || kiek <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw runtime_error("Neteisinga ivestis! Programa baigia darba.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                grupe.resize(kiek);
                for (int i = 0; i < kiek; i++) {
                    grupe[i].generuotiDuomenis();
                }

                cout << "\nSugeneruoti studentu duomenys:\n";
                cout << left << setw(15) << "Vardas"
                    << setw(15) << "Pavarde"
                    << setw(18) << "Galutinis (Vid.)"
                    << setw(18) << "Galutinis (Med.)"
                    << "\n-------------------------------------------------------------\n";

                sort(grupe.begin(), grupe.end(),
                    [](const Studentas& a, const Studentas& b) {
                        return a.getVardas() < b.getVardas();
                    });

                for (const auto& s : grupe)
                    s.isvedimas();
                break;
            }

                  // Nuskaitymas iš failo
            case 3: {
                grupe = Studentas::nuskaitytiIsFailo("kursiokai.txt");
                if (grupe.empty()) {
                    cout << "Nera duomenu nuskaitymui is failo." << endl;
                    break;
                }

                cout << "\nDuomenys nuskaityti is failo:\n";
                cout << left << setw(15) << "Vardas"
                    << setw(15) << "Pavarde"
                    << setw(18) << "Galutinis (Vid.)"
                    << setw(18) << "Galutinis (Med.)"
                    << "\n-------------------------------------------------------------\n";

                sort(grupe.begin(), grupe.end(),
                    [](const Studentas& a, const Studentas& b) {
                        return a.getVardas() < b.getVardas();
                    });

                for (const auto& s : grupe)
                    s.isvedimas();
                break;
            }

                  // Generavimas į failus
            case 4: {
                time.reset();
                Generatorius::generuotiVisus();
                tGen = time.elapsed();
                cout << "Duomenys sugeneruoti i failus." << endl;

                cout << "Nuskaitymas is failu..." << endl;
                time.reset();
                grupe = Studentas::nuskaitytiIsFailo("studentai_1000.txt");
                grupe = Studentas::nuskaitytiIsFailo("studentai_10000.txt");
                grupe = Studentas::nuskaitytiIsFailo("studentai_100000.txt");
                grupe = Studentas::nuskaitytiIsFailo("studentai_1000000.txt");
                grupe = Studentas::nuskaitytiIsFailo("studentai_10000000.txt");
                tRead = time.elapsed();

                if (grupe.empty()) {
                    cout << "Nera duomenu nuskaitymui is failo." << endl;
                    break;
                }

                time.reset();
                for (auto& s : grupe) {
                    s.skaiciuotiGalutinis();
                    if (s.getGalutinisVidurkis() < 5.0)
                        nuskriaustukai.push_back(s);
                    else
                        galvociai.push_back(s);
                }
                tSort = time.elapsed();

                time.reset();
                isvestiIFaila(nuskriaustukai, "nuskriaustukai.txt");
                isvestiIFaila(galvociai, "galvociai.txt");
                tWrite = time.elapsed();

                cout << "Failu kurimas uztruko " << tGen << " s.\n";
                cout << "Nuskaitymas uztruko " << tRead << " s.\n";
                cout << "Rusiavimas uztruko " << tSort << " s.\n";
                cout << "Isvedimas i failus uztruko " << tWrite << " s.\n";
                break;
            }

                  
            case 5: {
                // Testavimas konteineriu efektyvumo
                vector<size_t> sizes = { 1000, 10000, 100000, 1000000, 10000000 };
                for (size_t n : sizes) {
                    cout << "\n=== Spartos testavimas: n = " << n << " ===\n";
                    // Vector
                    auto vec = generateStudents<vector<Studentas>>(n);
                    run_strategy1(vec, "vector");
                    run_strategy2(vec, "vector");

                    // Deque
                    auto deq = generateStudents<deque<Studentas>>(n);
                    run_strategy1(deq, "deque");
                    run_strategy2(deq, "deque");

                    // List
                    auto lst = generateStudents<list<Studentas>>(n);
                    run_strategy1(lst, "list");
                    run_strategy2(lst, "list");
                }
                cout << "Testavimas baigtas.\n";
                break;
            }

                  // Neteisingas pasirinkimas
            default:
                cout << "Neteisingas pasirinkimas! Bandykite dar karta.\n";
                break;
            }

			// Ar tęsti darbą?
            if (veikia) {
                cout << "\nAr norite atlikti dar viena operacija? (1 - Taip, 0 - Ne): ";
                int testi;
                if (!(cin >> testi)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cerr << "Netinkama ivestis! Programa baigia darba.\n";
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (testi == 0) {
                    veikia = false;
                    cout << "Programa baigia darba. Iki!" << endl;
                }
                else {
                    // išvalom senus duomenis tarp operacijų
                    grupe.clear();
                    galvociai.clear();
                    nuskriaustukai.clear();
                }
            }
        }

    }
    catch (const std::exception& e) {
        cerr << "Klaida: " << e.what() << endl;
        return 1;
    }

    return 0;
}

