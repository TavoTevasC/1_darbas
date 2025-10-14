#include "Studentas.h"


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
