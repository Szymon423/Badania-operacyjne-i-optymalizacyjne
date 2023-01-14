#include "Djikstra.h"
#include <fstream>

#define bigNum 99999

Dijkstra::Dijkstra() {
	Dijkstra::N = 0;
	Dijkstra::src = 0;
	Dijkstra::cycle = false;
	Dijkstra::cnt = 0;
}

Dijkstra::~Dijkstra() {

}

void Dijkstra::importData(const string& path) {
	ifstream f(path);

	// odczytanie wartości N
	f >> Dijkstra::N;
	int help{ 0 };
	vector <int> helpV(Dijkstra::N, 0);
	Dijkstra::cycle = false;

	for (int a = 0; a < Dijkstra::N; a++) {
		// stworzenie wektora pomocniczego do uzupełnienia macierzy X
		for (int b = 0; b < Dijkstra::N; b++) {
			f >> help;
			helpV.at(b) = help;
		}
		Dijkstra::X.push_back(helpV);

		// utworzenie wektora dist o odpowiedniej długości
		// tam gdzie jest zero, oznacza, że nie ma krawędzi
		// dlatego wektor uzupełniamy względnie dużą liczbą
		Dijkstra::dist.push_back(bigNum);
		Dijkstra::isOk.push_back(false);
		Dijkstra::path.push_back(-1);
	}
	f.close();
	return;
}


void Dijkstra::doAllMagic() {
	//cout << endl;
	for (int a = 0; a < Dijkstra::N; a++) {
		// znalezienie sąsiada z minimalną odległością
		int nearesNeighbour = Dijkstra::minNeighbour();
		Dijkstra::isOk.at(nearesNeighbour) = true;
			
		for (int b = 0; b < Dijkstra::N; b++) {
			if (Dijkstra::X.at(nearesNeighbour).at(b) > 0 && !Dijkstra::isOk.at(b) && Dijkstra::dist.at(nearesNeighbour) != bigNum) {
				if (Dijkstra::dist.at(nearesNeighbour) + X.at(nearesNeighbour).at(b) < Dijkstra::dist.at(b)){
					Dijkstra::dist.at(b) = Dijkstra::dist.at(nearesNeighbour) + X.at(nearesNeighbour).at(b);
					Dijkstra::path.at(b) = nearesNeighbour;
					Dijkstra::cnt++;
				}	
			}
		}
	}
	return;
}


void Dijkstra::show() {
	cout << "Najkrotsze sciezki z wierzchołka " << Dijkstra::src << endl;
	cout << "dlugosc trasy\t\t Najkrotsza sciezka" << endl;
	
	for (int i = 0; i < Dijkstra::N; i++) {
		if (i != Dijkstra::src) {
			if (Dijkstra::dist.at(i) == bigNum) Dijkstra::dist.at(i) = -1;
			cout << Dijkstra::dist.at(i) << " \t\t";
			if (Dijkstra::dist.at(i) != -1)	Dijkstra::printPath(i, Dijkstra::path);
		}
		cout << endl;
	}
	cout << endl << "Liczba operacji dla Djikstry: " << Dijkstra::cnt << endl;
	return;
}

void Dijkstra::printPath(int currentVertex, vector <int> path_) {
	if (currentVertex == -1) return;
	printPath(path_[currentVertex], path_);
	cout << " " << currentVertex << " ";
}


int Dijkstra::minNeighbour() {
	int minVal{ bigNum };
	int minIndex{ 0 };
	for (int i = 0; i < Dijkstra::N; i++) {
		if (Dijkstra::dist.at(i) < minVal && !Dijkstra::isOk.at(i)) {
			minVal = Dijkstra::dist.at(i);
			minIndex = i;
		}
	}
	return minIndex;
}


void Dijkstra::source(int _src) {
	Dijkstra::src = _src;
	Dijkstra::dist.at(_src) = 0;
	Dijkstra::isOk.at(_src) = false;
}
