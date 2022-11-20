#include "Djikstra.h"
#include <fstream>

#define bigNum 99999

Djikstra::Djikstra() {
	Djikstra::N = 0;
	Djikstra::src = 0;
	Djikstra::cycle = false;
}

Djikstra::~Djikstra() {

}

void Djikstra::importData(string path) {
	ifstream f(path);

	// odczytanie wartości N
	f >> Djikstra::N;
	int help{ 0 };
	vector <int> helpV(Djikstra::N, 0);
	Djikstra::cycle = false;

	for (int a = 0; a < Djikstra::N; a++) {
		// stworzenie wektora pomocniczego do uzupełnienia macierzy X
		for (int b = 0; b < Djikstra::N; b++) {
			f >> help;
			helpV.at(b) = help;
		}
		Djikstra::X.push_back(helpV);

		// utworzenie wektora dist o odpowiedniej długości
		// tam gdzie jest zero, oznacza, że nie ma krawędzi
		// dlatego wektor uzupełniamy względnie dużą liczbą
		Djikstra::dist.push_back(bigNum);
		Djikstra::isOk.push_back(false);
		Djikstra::path.push_back(-1);
	}
	f.close();
	return;
}


void Djikstra::doAllMagic() {
	//cout << endl;
	for (int a = 0; a < Djikstra::N; a++) {
		// znalezienie sąsiada z minimalną odległością
		int nearesNeighbour = Djikstra::minNeighbour();
		Djikstra::isOk.at(nearesNeighbour) = true;
			
		for (int b = 0; b < Djikstra::N; b++) {
			if (Djikstra::X.at(nearesNeighbour).at(b) > 0 && !Djikstra::isOk.at(b) && Djikstra::dist.at(nearesNeighbour) != bigNum) {
				if (Djikstra::dist.at(nearesNeighbour) + X.at(nearesNeighbour).at(b) < Djikstra::dist.at(b)){
					Djikstra::dist.at(b) = Djikstra::dist.at(nearesNeighbour) + X.at(nearesNeighbour).at(b);
					Djikstra::path.at(b) = nearesNeighbour;
				}	
			}
		}
	}
	return;
}


void Djikstra::show() {
	cout << "Najkrotsze sciezki z wierzchołka " << Djikstra::src << endl;
	cout << "dlugosc trasy\t\t Najkrotsza sciezka" << endl;
	
	for (int i = 0; i < Djikstra::N; i++) {
		if (i != Djikstra::src) {
			if (Djikstra::dist.at(i) == bigNum) Djikstra::dist.at(i) = -1;
			cout << Djikstra::dist.at(i) << " \t\t";
			if (Djikstra::dist.at(i) != -1)	Djikstra::printPath(i, Djikstra::path);
		}
		cout << endl;
	}
	return;
}

void Djikstra::printPath(int currentVertex, vector <int> path_) {
	if (currentVertex == -1) return;
	printPath(path_[currentVertex], path_);
	cout << " " << currentVertex << " ";
}


int Djikstra::minNeighbour() {
	int minVal{ bigNum };
	int minIndex{ 0 };
	for (int i = 0; i < Djikstra::N; i++) {
		if (Djikstra::dist.at(i) < minVal && !Djikstra::isOk.at(i)) {
			minVal = Djikstra::dist.at(i);
			minIndex = i;
		}
	}
	return minIndex;
}


void Djikstra::source(int _src) {
	Djikstra::src = _src;
	Djikstra::dist.at(_src) = 0;
	Djikstra::isOk.at(_src) = false;
}
