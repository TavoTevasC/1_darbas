**V0.1**
1. Programa leidžia nuskaityti šios studentų duomenis: vardą ir pavardę, atliktu namų darbų rezultatus ir egzamino rezultatą (arba sugeneruos atsitiktinai).
2.  Iš šių duomenų suskaičiuoja galutinį rezultatą.
3.  Papildomos bibliotekos aprašytos faile ***Mylib.h***.
4.  Funkcijos aprašytos faile ***Studentas.h***.

**V0.2**
1. 5 failų (**studentai_1000.txt** ir t.t) generavimas su studentu informacija.
2. Šių studentų rušiavimas pagal galutinį balą.
3. Surūšiuotų studentų išvedimas į failus (**nuskriaustukai.txt** <5 ir **galvociai.txt** >=5).
4. Spartos matavimas.
5. Nauja bibloteka ***Timer.h*** laiko matavimui.

**V1.0**
1. Studentų rūšiavimo į dvį kategorijas optimizacija.
2. Konteineriu (**Vector, Deque, List**) spartos matavimas ir atminties poreikis priklausomai nuo **Strategijos**.
3. Nauja biblioteka ***Memory.h*** atminties matavimui.
4. Dabar po vienos operacijos atlikimo programa tesia darbą toliau.
5. Sukurtas **Studentas_setup.exe** failas programos įdegimui.

**V0.2** Konteineriu testavimas (5 studentų failai):

| Konteineris       | Nuskaitymas (s) | Rūšiavimas (s) | Išvedimas (s) | Bendras laikas (s) |
| ----------------- | --------------- | -------------- | ------------- | ------------------ |
| **`std::vector`** | 23.347          | 2.987          | 6.677         | 33.011             |
| **`std::deque`**  | 22.245          | 1.998          | 7.819         | 32.062             |
| **`std::list`**   | 22.050          | 1.934          | 6.907         | 30.891             |

Išvada: Konteineris **`std::list`**  sparčiausias.

**V1.0** Spartos testavimas: n = 10000000:

| Konteineris       | 1 Strategija (s) | 2 Strategija (s) | 1 Strategija (KB) | 2 Strategija (KB) |
| ----------------- | ---------------- | ---------------- | ----------------- | ----------------- |
| **`std::vector`** | 2.4803           | 0.743013         | 1526828           | 581968            |
| **`std::deque`**  | 1.21809          | 1.51079          | 1665808           | 681024            |
| **`std::list`**   | 1.33741          | 0.288231         | 1722936           | 0                 |

Išvada: 1 Strategija yra neefektyvi, nes užima daugiau laiko ir reikalauja daugiau atminties.

Įdegimo instrukcija:
1. Atsiuskit failą **Studentas_setup.exe**.
2. Paleiskit failą ir siekit instaliacijos instrukciją.
3. Po programos įdegimo, galyte pradeti darbą.

Naudojimosi instrukcija:
1. Paleiskite programą.
2. Pasirinkite duomenu ivedimo buda:
   - Rankiniu budu
     - Įveskite studentų kiekį ir duomenis
     - Programa išves lentelę su galutiniais įverčiais (vidurkis, mediana)             
   - Generuoti atsitiktinius duomenis
     - Įveskite, kiek studentų generuoti
     - Programa automatiškai sugeneruos duomenis ir juos parodys
   - Nuskaityti is failo (kursiokai.txt)
     - Programa bandys nuskaityti `kursiokai.txt`
     - Jei failas egzistuoja, išves lentelę
   - Generuoti duomenis i failus
     - Sugeneruojami failai:
        - `studentai_1000.txt`
        - `studentai_10000.txt`
        - `studentai_100000.txt`
        - `studentai_1000000.txt`
        - `studentai_10000000.txt`
     - Suskaičiuojami galutiniai įverčiai ir sukuriami:
        - `galvociai.txt` - vidurkis ≥ 5
        - `nuskriaustukai.txt` - vidurkis \< 5
   - Vykdyti spartos testavima
     - Programa testuoja našumą su:
       - `vector<Studentas>`
       - `deque<Studentas>`
       - `list<Studentas>`
     - Parodomi laikai ir atminties poreikiai dviem strategijoms
   - Baigti darba

