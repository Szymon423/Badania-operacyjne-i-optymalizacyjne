#include "include/CRP.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>

#define mtpl 1

using namespace std;

CRP::CRP() {
    CRP::N = 0;
    CRP::M = 0;
    CRP::processTime = 0;
    CRP::cycle = false;
}

CRP::~CRP() {}


 void CRP::importData(string fileName) {
      //metoda odpowiedzialna za wczytanie danych
      //odcyztanie danych z pliku
      ifstream file(fileName);

      //odczytanie pierwszej linijki z danych
      file >> CRP::N >> CRP::M;

      // wektor pomocniczy do utworzenia macierzy X
      vector <int> help(CRP::N, 0);

      // tworzenie macierzy X
      for (int i = 0; i < CRP::N; i++) {
          CRP::X.push_back(help);
      }

      // stworzenie macierzy C z wartościami początkowymi jak z wektora P
      // odczytanie drugiej linijki z danych
      int hlp_ = 0;
      for (int i=0; i<CRP::N; i++) {
          file >> hlp_;
          CRP::P.push_back(hlp_);
          CRP::C.push_back(hlp_);
      }

      // odczytanie pozostałych rzeczy
      for (int i=0; i<CRP::M; i++) {
          int a,b; file >> a >> b; CRP::X[a-1][b-1] = 1; 
      }
      file.close();
      return;
 }

 void CRP::printAdjacencyMatrix() {
     printf("    ");
     for (int i = 0; i < CRP::N; i++) {
         printf("%3d", i+1);
     }
     printf("\n__");
     for (int i = 0; i < CRP::N+1; i++) {
         printf("___");
     }
     printf("\n");
     for (int i = 0; i < N; i++) {
         printf("%2d |", i+1);
         for (int j = 0; j < CRP::N; j++) {
             printf("%3d", CRP::X[i][j]);
         }
         cout << endl;
     }
     return;
 }


 void CRP::printTaskTimes() {
     printf("\n");
     for (int i = 0; i < CRP::N; i++) {
         printf("%3d", CRP::P[i]);
     }
     printf("\n\n");
     return;
 }

void CRP::findProcessTime() {
    // zmienna pomocnicza do sprawdzania czy zachodzi cykl blokujący
    int cnt = 0;
    // iteracja M razy, aby uniknąć konieczności wyznaczania kolejności
    for(int rpt = 0; rpt<mtpl*CRP::M; rpt++) {
        // poszukiwanie jedynek w macierzy sąsiedztwa
        // iteracja przez wiersze
        cnt = 0;
        for (int a = 0; a<CRP::N; a++) {
            // iteracja przez kolumny
            for (int b = 0; b<CRP::N; b++) { 
                if (X[a][b] == 1) {
                    // CRP::C[b] = max(CRP::C[a] + CRP::P[b], CRP::C[b]);
                    if (CRP::C[a] + CRP::P[b] > CRP::C[b]) {
                        CRP::C[b] = CRP::C[a] + CRP::P[b];
                        cnt++;
                    }
                }
            }
        }
    }

    // sprawdzenie czy wykryto cykl blokujący
    if (cnt > 0) {
        printf("\nWykryto cykl, brak mozliwego rozwiazania...\n");
        CRP::cycle = true;
        return;
    }

    // szukanie największej wartości:
    CRP::processTime = CRP::C[0];
    for (int i = 0; i< CRP::N; i++) CRP::processTime = max(CRP::C[i], CRP::processTime);
    printf("\n\nProcess time: %f\n\n", CRP::processTime);
    return;
 }

void CRP::findTaskTimes() {
    // sprawdzenie czy wykryto cykl blokujący
    if (CRP::cycle) return;
    
    // przygotowanie wektorów z czasami
    vector <int> earlyStart(CRP::N, 0);
    vector <int> earlyFinish(CRP::N, 0);
    vector <int> lateStart(CRP::N, 0);
    vector <int> lateFinish(CRP::N, 0);

    // Przypisanie do wektora D odpowiednich wartości początkowych
    for (int i = 0; i < CRP::N; i++) {
        lateStart[i] = CRP::processTime - CRP::P[i];
    }

    // iteracja n razy, aby uniknąć konieczności wyznaczania kolejności
    for (int rpt = 0; rpt< mtpl*CRP::M; rpt++) {
        // iteracja przez kolumny
        for (int b = 0; b < CRP::N; b++) {
            // iteracja przez wiersze
            for (int a = 0; a < CRP::N; a++) {
                if (X[a][b] == 1) {
                    earlyStart[b] = max(earlyStart[b], C[a]);
                    lateStart[a] = min(lateStart[b] - P[a], lateStart[a]);
                }
            }
            earlyFinish[b] = earlyStart[b] + P[b];
        }
    }

    // obliczenie ostatecznych warości startu i finishu
    for(int i=0; i<CRP::N; i++) {
        lateFinish[i] = lateStart[i] + CRP::P[i];
    }
    vector <int> help(4, 0);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j<CRP::N; j++) {
            help[0] = earlyStart[j];    help[1] = earlyFinish[j];
            help[2] = lateStart[j];     help[3] = lateFinish[j];
            CRP::TaskTimes.push_back(help);
        }
    }

    // printowanie danych:
    printf("\nearlyStart earlyFinish lateStart lateFinish");
    for (int a = 0; a<CRP::N; a++) {
        printf("\n%8d %8d %8d %8d", CRP::TaskTimes[a][0], CRP::TaskTimes[a][1], CRP::TaskTimes[a][2], CRP::TaskTimes[a][3]);
    }
    return;
}

// funkcja do sortowania weirszy na podstawie jednej kolumny  w tym przypadku nr 1
bool sortcol(const vector<int>& v1, const vector<int>& v2) {
    //definicja kolumny względem której sortujemy wiersze 
    int colNum{ 1 }; // środkowa kolumna
    return v1[colNum] < v2[colNum];
}

void CRP::findCRP() {
    // sprawdzenie czy wykryto cykl blokujący
    if (CRP::cycle) return;

    // szukamy CRP
    // istotne jest określenie operacji krytycznych czyli takich dla których 
    // Total Float (całkowity luz) TF = 0, 
    // przy czym TF = LS - ES = LF - EF
    // int* TF = new int[N+1] {0};
    vector <int> CRP_sub (3, 0);

    for (int i = 0; i<CRP::N; i++) {
        // sprawdzenie warunku czy czynność należy do CRP
        if (CRP::TaskTimes[i][2] - CRP::TaskTimes[i][0] == 0) {
            // jeśli tak, to create helping vector i dodaj do TF
            CRP_sub[0] = i+1;  CRP_sub[1] = CRP::TaskTimes[i][0]; CRP_sub[2] = CRP::TaskTimes[i][1];
            CRP::CritPath.push_back(CRP_sub);
        }
    }

    // wiedząc, które czynności należą do CRP, teraz musimy je posortowąć względem czasu finishu:
    sort(CRP::CritPath.begin(), CRP::CritPath.end(), sortcol);

    // wyświetlenie CRP
    printf("\n\n");
    for (int i = 0; i<static_cast<int>(CRP::CritPath.size()); i++) {
        printf("%3d %3d %3d\n", CRP::CritPath[i][0], CRP::CritPath[i][1], CRP::CritPath[i][2]);
    }
    return;
}

