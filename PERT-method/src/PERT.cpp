#include "PERT.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <iomanip>


using namespace std;

PERT::PERT() {
    PERT::N = 0;
    PERT::M = 0;
    PERT::processTime = 0.0;
    PERT::cycle = false;
    PERT::CRPwar = 0.0;
    PERT::CRPtime = 0.0;
    PERT::XX = 0;
    PERT::Y = 0;    
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

    // odczytanie drugiej linijki z danych
    vector <int> hlp_(3, 0);
    float Toper {0};

    for (int i = 0; i < PERT::N; i++) {
        file >> hlp_[0] >> hlp_[1] >> hlp_[2];
        PERT::inputTripleTime.push_back(hlp_);

        Toper = (hlp_[0] + 4 * hlp_[1] + hlp_[2]) / 6.0;
        float calculateThis = (hlp_[2] - hlp_[0]) / 6.0;
        calculateThis *= calculateThis;
        PERT::war.push_back(calculateThis);
        PERT::taskDuration.push_back(Toper);
        PERT::earlyFinish.push_back(Toper);
        PERT::earlyStart.push_back(0);
        PERT::lateFinish.push_back(0);
        PERT::lateStart.push_back(0);
    }

    // odczytanie pozostałych rzeczy
    for (int i = 0; i < PERT::M; i++) {
        int a, b; file >> a >> b; PERT::X[a - 1][b - 1] = 1;
    }
    file >> PERT::XX >> PERT::Y;
    file.close();
    return;
}

void PERT::printAdjacencyMatrix() {
    printf("    ");
    for (int i = 0; i < PERT::N; i++) {
        printf("%3d", i + 1);
    }
    printf("\n__");
    for (int i = 0; i < PERT::N + 1; i++) {
        printf("___");
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%2d |", i + 1);
        for (int j = 0; j < PERT::N; j++) {
            printf("%3d", PERT::X[i][j]);
        }
        cout << endl;
    }
    return;
}


void PERT::printTaskTimes() {
    printf("\nTask times:\n");
    for (int i = 0; i < PERT::N; i++) {
        printf("%.2f   ", static_cast<float>(PERT::taskDuration[i]));
    }
    printf("\n\n");
    return;
}

void PERT::findProcessTime() {
    // zmienna pomocnicza do sprawdzania czy zachodzi cykl blokujący
    int cnt = 0;
    // iteracja M razy, aby uniknąć konieczności wyznaczania kolejności
    for (int rpt = 0; rpt<PERT::M; rpt++) {
        // poszukiwanie jedynek w macierzy sąsiedztwa
        // iteracja przez wiersze
        cnt = 0;
        for (int a = 0; a < PERT::N; a++) {
            // iteracja przez kolumny
            for (int b = 0; b < PERT::N; b++) {
                if (X[a][b] == 1) {
                    if (PERT::earlyFinish[a] + PERT::taskDuration[b] > PERT::earlyFinish[b]) {
                        PERT::earlyFinish[b] = PERT::earlyFinish[a] + PERT::taskDuration[b];
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
    PERT::processTime = PERT::earlyFinish[0];
    for (int i = 0; i < PERT::N; i++) PERT::processTime = max(static_cast<float>(PERT::earlyFinish[i]), PERT::processTime);
    printf("\n\nProcess time: %.2f\n\n", PERT::processTime);
    return;
}

void PERT::findTaskTimes() {
    // sprawdzenie czy wykryto cykl blokujący
    if (PERT::cycle) return;

    // Przypisanie do wektora lateStart odpowiednich wartości początkowych
    for (int i = 0; i < PERT::N; i++) {
        PERT::lateStart[i] = PERT::processTime - PERT::taskDuration[i];
    }

    // iteracja n razy, aby uniknąć konieczności wyznaczania kolejności
    for (int rpt = 0; rpt < PERT::M; rpt++) {
        // iteracja przez kolumny
        for (int b = 0; b < PERT::N; b++) {
            // iteracja przez wiersze
            for (int a = 0; a < PERT::N; a++) {
                if (X[a][b] == 1) {
                    PERT::lateStart[a] = min(PERT::lateStart[b] - PERT::taskDuration[a], PERT::lateStart[a]);
                }
            }
        }
    }

    // obliczenie pozostałych wartości LF oraz ES na podstawie znanych LS oraz EF
    for (int i = 0; i < PERT::N; i++) {
        PERT::lateFinish[i] = PERT::lateStart[i] + PERT::taskDuration[i];
        PERT::earlyStart[i] = PERT::earlyFinish[i] - PERT::taskDuration[i];
    }
    vector <float> help(4, 0);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < PERT::N; j++) {
            help[0] = PERT::earlyStart[j];    help[1] = PERT::earlyFinish[j];
            help[2] = PERT::lateStart[j];     help[3] = PERT::lateFinish[j];
            PERT::TaskTimes.push_back(help);
        }
    }

    // printowanie danych:
    printf("\nearlyStart earlyFinish lateStart lateFinish");
    for (int a = 0; a < PERT::N; a++) {
        printf("\n%9.2f %9.2f %9.2f %9.2f", PERT::TaskTimes[a][0], PERT::TaskTimes[a][1], PERT::TaskTimes[a][2], PERT::TaskTimes[a][3]);
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

    // szukamy CPM
    // istotne jest określenie operacji krytycznych czyli takich dla których 
    // Total Float (całkowity luz) TF = 0, 
    // przy czym TF = LS - ES = LF - EF
    // int* TF = new int[N+1] {0};
    vector <float> PERT_sub(4, 0.0);

    for (int i = 0; i < PERT::N; i++) {
        // sprawdzenie warunku czy czynność należy do CRP
        if (abs(PERT::TaskTimes[i][2] - PERT::TaskTimes[i][0]) < 0.1) {
            PERT_sub[0] = i + 1;
            PERT_sub[1] = PERT::TaskTimes[i][0];
            PERT_sub[2] = PERT::TaskTimes[i][1];
            PERT_sub[3] = PERT::war[i];
            PERT::CritPath.push_back(PERT_sub);
        }
    }

    // wiedząc, które czynności należą do PERT, teraz musimy je posortowąć względem czasu finishu:
    sort(PERT::CritPath.begin(), PERT::CritPath.end(), sortcol);

    // wyświetlenie PERT
    printf("\n\n");
    for (int i = 0; i < static_cast<int>(PERT::CritPath.size()); i++) {
        printf("%9.2f %9.2f %9.2f %9.2f\n", PERT::CritPath[i][0], PERT::CritPath[i][1], PERT::CritPath[i][2], PERT::CritPath[i][3]);
        PERT::CRPwar += PERT::CritPath[i][3];
        PERT::CRPtime += PERT::taskDuration[PERT::CritPath[i][0] - 1];
    }

    printf("\nCzas projektu: %9.2f", PERT::CRPtime);
    printf("\nOdchylenie standardowe: %9.2f\n", sqrt(PERT::CRPwar));
    return;
}


void PERT::dys() {
    double myDataSd = sqrt(PERT::CRPwar);
    double myDataX = PERT::XX;
    double myDataMean = PERT::CRPtime;

    double x, y, w, Z_MAX = 6, mean, sd, z;

    mean = myDataMean, x = myDataX, sd = myDataSd;

    if (mean < x) y = x - mean;
    else y = mean - x;

    z = y / sd;

    if (z == 0.0) {
        x = 0.0;
    }
    else {
        y = 0.5 * z;
        if (y > (Z_MAX * 0.5)) {
            x = 1.0;
        }
        else if (y < 1.0) {
            w = y * y;
            x = ((((((((0.000124818987 * w - 0.001075204047) * w
                + 0.005198775019) * w - 0.019198292004) * w
                + 0.059054035642) * w - 0.151968751364) * w
                + 0.319152932694) * w - 0.531923007300) * w
                + 0.797884560593) * y * 2.0;
        }
        else
        {
            y -= 2.0;
            x = (((((((((((((-0.000045255659 * y
                + 0.000152529290) * y - 0.000019538132) * y
                - 0.000676904986) * y + 0.001390604284) * y
                - 0.000794620820) * y - 0.002034254874) * y
                + 0.006549791214) * y - 0.010557625006) * y
                + 0.011630447319) * y - 0.009279453341) * y
                + 0.005353579108) * y - 0.002141268741) * y
                + 0.000535310849) * y + 0.999936657524;
        }
        if (z > 0.0)
            z = (x + 1.0) * 0.5;
        else
            z = (1.0 - x) * 0.5;
    }

    if ((myDataX - myDataMean) > 0) {
        std::cout.precision(2);
        std::cout << "Prawdopodobienstwo zakonczenia projektu w ciagu podanego czasu: " << z * 100 << "%";
    }
    else {
        std::cout.precision(2);
        std::cout << "Prawdopodobienstwo zakonczenia projektu w ciagu podanego czasu: " << (1 - z) * 100 << "%";
    }
}
double PERT::inv_dys(double p) {
    p = PERT::Y / 100;
    if (p < 0.5) {
        double LR = p / (1 - p);
        return 5.5310 * (std::pow(LR, 0.1193) - 1);
    }
    else {
        double LR = (1 - p) / p;
        return -5.5310 * (std::pow(LR, 0.1193) - 1);
    }

}
void PERT::time_day() {
    double t;
    double x = inv_dys(PERT::Y / 100);
    t = PERT::CRPtime + sqrt(PERT::CRPwar) * x;
    cout << setprecision(4) << "Czas projektu wyniesie:  " << t << " [dni]\n\n" << endl;
    return;

}



