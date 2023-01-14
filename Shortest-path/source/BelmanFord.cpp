#include "BellmanFord.h"
#include <fstream>

BellmanFord::BellmanFord() : N(0), cnt(0) {
}

BellmanFord::~BellmanFord() {
}

void BellmanFord::importData(const string& path) {
	ifstream f(path);

	// odczytanie wartości N
	f >> BellmanFord::N;
	int help{ 0 };
	vector <int> helpV(BellmanFord::N, 0);

	for (int a = 0; a < BellmanFord::N; a++) {
		// stworzenie wektora pomocniczego do uzupełnienia macierzy X
		for (int b = 0; b < BellmanFord::N; b++) {
			f >> help;
			helpV.at(b) = help;
		}
		BellmanFord::X.push_back(helpV);

		// utworzenie wektora dist o odpowiedniej długości
		// tam gdzie jest zero, oznacza, że nie ma krawędzi
		// dlatego wektor uzupełniamy względnie dużą liczbą
		if (a == 0) {
			BellmanFord::dist.push_back(0);
		}
		else {
			BellmanFord::dist.push_back(99999);
		}
	}
	f.close();
}


void BellmanFord::doAllMagic() {
	for (int i = 0; i < BellmanFord::N; i++) {
		for (int a = 0; a < BellmanFord::N; a++) {
			for (int b = 0; b < BellmanFord::N; b++) {
				if (BellmanFord::X.at(a).at(b) > 0) {
					BellmanFord::dist[b] = min(BellmanFord::dist[b], BellmanFord::dist[a] + X.at(a).at(b));
					BellmanFord::cnt++;
				}
			}
		}
	}
	return;
}


void BellmanFord::show() {
	cout << "Nr wezla \tDystans" << endl;
	for (int a = 0; a < BellmanFord::N; a++) {
		cout << a + 1 << " \t\t" << BellmanFord::dist.at(a) << endl;
	}
	cout << endl << "Liczba operacji dla Bellmana Forda: " << BellmanFord::cnt << endl;
	return;
}

