#include "include/PERT.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#define mtpl 1

using namespace std;

PERT::PERT() {
    PERT::N = 0;
    PERT::M = 0;
    PERT::processTime = 0;
    PERT::cycle = false;
    PERT::CRPwar = 0;
    PERT::CRPtime = 0;
}

PERT::~PERT() {}


void PERT::importData(string fileName) {
    //metoda odpowiedzialna za wczytanie danych
    //odcyztanie danych z pliku
    ifstream file(fileName);

    //odczytanie pierwszej linijki z danych
    file >> PERT::N >> PERT::M;

    // wektor pomocniczy do utworzenia macierzy X
    vector <int> help(PERT::N);

    // tworzenie macierzy X
    for (int i = 0; i < PERT::N; i++) {
        PERT::X.push_back(help);
    }

    // stworzenie macierzy C z wartościami początkowymi jak z wektora P
    // odczytanie drugiej linijki z danych
    vector <int> hlp_(3, 0);
    float Toper {0};

    for (int i=0; i<PERT::N; i++) {
        file >> hlp_[0] >> hlp_[1] >> hlp_[2];
        PERT::inputTripleTime.push_back(hlp_);

        Toper = (hlp_[0] + 4*hlp_[1] + hlp_[2]) / 6.0;
        float calculateThis = (hlp_[2] - hlp_[1])/6;
        calculateThis *= calculateThis;
        PERT::war.push_back(calculateThis);
        PERT::P.push_back(Toper);
        PERT::C.push_back(Toper);
    }

    // odczytanie pozostałych rzeczy
    for (int i=0; i<PERT::M; i++) {
        int a,b; file >> a >> b; PERT::X[a-1][b-1] = 1; 
    }
    file.close();
    return;
 }

 void PERT::printAdjacencyMatrix() {
     printf("    ");
     for (int i = 0; i < PERT::N; i++) {
         printf("%3d", i+1);
     }
     printf("\n__");
     for (int i = 0; i < PERT::N+1; i++) {
         printf("___");
     }
     printf("\n");
     for (int i = 0; i < N; i++) {
         printf("%2d |", i+1);
         for (int j = 0; j < PERT::N; j++) {
             printf("%3d", PERT::X[i][j]);
         }
         cout << endl;
     }
     return;
 }


 void PERT::printTaskTimes() {
     printf("\n");
     for (int i = 0; i < PERT::N; i++) {
         printf("%3f", PERT::P[i]);
     }
     printf("\n\n");
     return;
 }

void PERT::findProcessTime() {
    // zmienna pomocnicza do sprawdzania czy zachodzi cykl blokujący
    int cnt = 0;
    // iteracja M razy, aby uniknąć konieczności wyznaczania kolejności
    for(int rpt = 0; rpt<mtpl*PERT::M; rpt++) {
        // poszukiwanie jedynek w macierzy sąsiedztwa
        // iteracja przez wiersze
        cnt = 0;
        for (int a = 0; a<PERT::N; a++) {
            // iteracja przez kolumny
            for (int b = 0; b<PERT::N; b++) { 
                if (X[a][b] == 1) {
                    // PERT::C[b] = max(PERT::C[a] + PERT::P[b], PERT::C[b]);
                    if (PERT::C[a] + PERT::P[b] > PERT::C[b]) {
                        PERT::C[b] = PERT::C[a] + PERT::P[b];
                        cnt++;
                    }
                }
            }
        }
    }

    // sprawdzenie czy wykryto cykl blokujący
    if (cnt > 0) {
        printf("\nWykryto cykl, brak mozliwego rozwiazania...\n");
        PERT::cycle = true;
        return;
    }

    // szukanie największej wartości:
    PERT::processTime = PERT::C[0];
    for (int i = 0; i< PERT::N; i++) PERT::processTime = max(PERT::C[i], PERT::processTime);
    printf("\n\nProcess time: %f\n\n", PERT::processTime);
    return;
 }

void PERT::findTaskTimes() {
    // sprawdzenie czy wykryto cykl blokujący
    if (PERT::cycle) return;
    
    // przygotowanie wektorów z czasami
    vector <float> earlyStart(PERT::N, 0);
    vector <float> earlyFinish(PERT::N, 0);
    vector <float> lateStart(PERT::N, 0);
    vector <float> lateFinish(PERT::N, 0);

    // Przypisanie do wektora D odpowiednich wartości początkowych
    for (int i = 0; i < PERT::N; i++) {
        lateStart[i] = PERT::processTime - PERT::P[i];
    }

    // iteracja n razy, aby uniknąć konieczności wyznaczania kolejności
    for (int rpt = 0; rpt< mtpl*PERT::M; rpt++) {
        // iteracja przez kolumny
        for (int b = 0; b < PERT::N; b++) {
            // iteracja przez wiersze
            for (int a = 0; a < PERT::N; a++) {
                if (X[a][b] == 1) {
                    earlyStart[b] = max(earlyStart[b], C[a]);
                    lateStart[a] = min(lateStart[b] - P[a], lateStart[a]);
                }
            }
            earlyFinish[b] = earlyStart[b] + P[b];
        }
    }

    // obliczenie ostatecznych warości startu i finishu
    for(int i=0; i<PERT::N; i++) {
        lateFinish[i] = lateStart[i] + PERT::P[i];
    }
    vector <float> help(4, 0);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j<PERT::N; j++) {
            help[0] = earlyStart[j];    help[1] = earlyFinish[j];
            help[2] = lateStart[j];     help[3] = lateFinish[j];
            PERT::TaskTimes.push_back(help);
        }
    }

    // printowanie danych:
    printf("\nearlyStart earlyFinish lateStart lateFinish");
    for (int a = 0; a<PERT::N; a++) {
        printf("\n%4f %4f %4f %4f", PERT::TaskTimes[a][0], PERT::TaskTimes[a][1], PERT::TaskTimes[a][2], PERT::TaskTimes[a][3]);
    }
    return;
}

// funkcja do sortowania weirszy na podstawie jednej kolumny  w tym przypadku nr 1
bool sortcol(const vector<float>& v1, const vector<float>& v2) {
    //definicja kolumny względem której sortujemy wiersze 
    int colNum{ 1 }; // środkowa kolumna
    return v1[colNum] < v2[colNum];
}

void PERT::findCRP() {
    // sprawdzenie czy wykryto cykl blokujący
    if (PERT::cycle) return;

    // szukamy PERT
    // istotne jest określenie operacji krytycznych czyli takich dla których 
    // Total Float (całkowity luz) TF = 0, 
    // przy czym TF = LS - ES = LF - EF
    // int* TF = new int[N+1] {0};
    vector <float> PERT_sub (4, 0.0);

    for (int i = 0; i<PERT::N; i++) {
        // sprawdzenie warunku czy czynność należy do PERT
        if (abs(PERT::TaskTimes[i][2] - PERT::TaskTimes[i][0]) > 0.1) {
            // jeśli tak, to create helping vector i dodaj do TF
            PERT_sub[0] = i+1;  PERT_sub[1] = PERT::TaskTimes[i][0]; PERT_sub[2] = PERT::TaskTimes[i][1]; PERT_sub[3] = PERT::war[i];
            PERT::CritPath.push_back(PERT_sub);
        }
    }

    // wiedząc, które czynności należą do PERT, teraz musimy je posortowąć względem czasu finishu:
    sort(PERT::CritPath.begin(), PERT::CritPath.end(), sortcol);

    // wyświetlenie PERT
    printf("\n\n");
    for (int i = 0; i<static_cast<int>(PERT::CritPath.size()); i++) {
        printf("%3f %3f %3f %3f\n", PERT::CritPath[i][0], PERT::CritPath[i][1], PERT::CritPath[i][2], PERT::CritPath[i][3]);
        PERT::CRPwar += PERT::CritPath[i][3];
        PERT::CRPtime += PERT::P[PERT::CritPath[i][0]-1];
    }

    printf("\nOdchylenie standardowe: %f\n", sqrt(PERT::CRPwar));
    printf("\nCzas projektu: %f\n", PERT::CRPtime);

    return;
}

