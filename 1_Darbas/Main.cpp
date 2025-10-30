#include "Studentas.h"



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
	double tGen = 0, tRead = 0, tSort = 0, tWrite = 0 ;
	cout << "Programa pradeda darba..." << endl;
    try {
        cout << "Pasirinkite duomenu ivedimo buda:\n"
             << "1 - Rankiniu budu\n"
             << "2 - Generuoti atsitiktinius duomenis\n"
             << "3 - Nuskaityti is failo (kursiokai.txt)\n"
             << "4 - Generuoti duomenis i failus (studentai_1000.txt, studentai_10000.txt, ...)\n"
             << "5 - Vykdyti spartos testavima (vector, deque, list, abi strategijos)\n"
		     << "Kad pradeti darba, iveskite pasirinkimo numeri ir paspauskite (ENTER)\n";

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
        else if (budas == 4) {
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
                return 1;
			}
            
		}
        else if (budas == 5) {
			// Testavimas konteineriu efektyvumo
			vector<size_t> sizes = { 1000, 10000, 100000, 1000000, 10000000 }; // Pasirinkit konteinerio dydi priklausomai nuo jusu kompiuterio galimybiu
            for (size_t n : sizes) {
                cout << "\n=== Spartos testavimas: n = " << n << " ===\n";
                // Vector
                auto vec = generateStudents<vector<Studentas>>(n);
                for (auto c : {1,2}) {
                    if (c==1) run_strategy1<vector<Studentas>>(vec, "vector");
                    else run_strategy2<vector<Studentas>>(vec, "vector");
                }

                // Deque
                auto deq = generateStudents<deque<Studentas>>(n);
                for (auto c : {1,2}) {
                    if (c==1) run_strategy1<deque<Studentas>>(deq, "deque");
                    else run_strategy2<deque<Studentas>>(deq, "deque");
                }

                // List
                auto lst = generateStudents<list<Studentas>>(n);
                for (auto c : {1,2}) {
                    if (c==1) run_strategy1<list<Studentas>>(lst, "list");
                    else run_strategy2<list<Studentas>>(lst, "list");
                }
            }

            cout << "Testavimas baigtas." << endl;
            return 0;
        }
        else {
            throw runtime_error("Neteisingas pasirinkimas!");
        }

        
        
        if (budas != 4) {
            // Lentelės antraštė
            cout << "\n"
                << left << setw(15) << "Vardas"
                << setw(15) << "Pavarde"
                << setw(18) << "Galutinis (Vid.)"
                << setw(18) << "Galutinis (Med.)"
                << "\n-------------------------------------------------------------\n";

            // Rusiavimas pagal vardą 
            sort(grupe.begin(), grupe.end(),
                [](const Studentas& a, const Studentas& b) {
                    return a.getVardas() < b.getVardas();
                }); 
        }

        if (budas != 4) {
            for (const auto& s : grupe) {
                s.isvedimas();
                
            }
            
        }

        else {
			time.reset();
            for (auto& s : grupe) {
                s.skaiciuotiGalutinis();
				if (s.getGalutinisVidurkis() < 5.0) // Studentų rusiavimas į dvi grupes
                    nuskriaustukai.push_back(s);
                else
                    galvociai.push_back(s);
            }
			tSort = time.elapsed();
		}
        
        if (budas == 4) {
			time.reset();
            isvestiIFaila(nuskriaustukai, "nuskriaustukai.txt"); // Surušiuotų studentų išvedimas į failą (galutinis < 5)
            isvestiIFaila(galvociai, "galvociai.txt"); // Surušiuotų studentų išvedimas į failą (galutinis >= 5)
			tWrite = time.elapsed();
            cout << "Failu kurimas uztruko " << tGen << " sekundziu." << endl;
			cout << "Nuskaitymas is failu uztruko " << tRead << " sekundziu." << endl;
			cout << "Studentu rusiavimas i dvi grupes uztruko " << tSort << " sekundziu." << endl;
			cout << "Surusiuotu studentu isvedimas i failus uztruko " << tWrite << " sekundziu." << endl;
            cout << "Ar atlikti pakartotina sukurtu failu testavima? (1 - Taip, 0 - Ne): ";
            int test;
            if (!(cin >> test)) {
                throw runtime_error("Netinkama ivestis!");
            }

            if (test == 1) {
                cout << "Nuskaitymas is failu..." << endl;
				time.reset();
                grupe = Studentas::nuskaitytiIsFailo("studentai_1000.txt");
                grupe = Studentas::nuskaitytiIsFailo("studentai_10000.txt");
                grupe = Studentas::nuskaitytiIsFailo("studentai_100000.txt");
                grupe = Studentas::nuskaitytiIsFailo("studentai_1000000.txt");
                grupe = Studentas::nuskaitytiIsFailo("studentai_10000000.txt");
				tRead = time.elapsed();

				time.reset();
                for (auto& s : grupe) {
                    s.skaiciuotiGalutinis();
                    if (s.getGalutinisVidurkis() < 5.0) // Studentų rusiavimas į dvi grupes
                        nuskriaustukai.push_back(s);
                    else
                        galvociai.push_back(s);
                }
				tSort = time.elapsed();
				time.reset();
                isvestiIFaila(nuskriaustukai, "nuskriaustukai.txt"); // Surušiuotų studentų išvedimas į failą (galutinis < 5)
                isvestiIFaila(galvociai, "galvociai.txt"); // Surušiuotų studentų išvedimas į failą (galutinis >= 5)
				tWrite = time.elapsed();
                cout << "Nuskaitymas is failu uztruko " << tRead << " sekundziu." << endl;
                cout << "Studentu rusiavimas i dvi grupes uztruko " << tSort << " sekundziu." << endl;
                cout << "Surusiuotu studentu isvedimas i failus uztruko " << tWrite << " sekundziu." << endl;


            }
            else if (test == 0) {
				cout << "Programa baige darba." << endl;
            } 
            else {
				throw runtime_error("Neteisingas pasirinkimas!");
            }

            
        }

    }
    catch (const std::exception& e) {
        cerr << "Klaida: " << e.what() << endl;
        return 1;
    }

    return 0;
}
