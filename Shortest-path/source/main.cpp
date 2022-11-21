#include <iostream>
#include <chrono>
#include "BellmanFord.h"
#include "Djikstra.h"


int main() {
	// realizacja algorytmu
	BellmanFord bf;
	bf.importData("data.txt");
	auto startBF = chrono::high_resolution_clock::now();
	bf.doAllMagic();
	auto stopBF = chrono::high_resolution_clock::now();
	bf.show();

	//wyświetlanie czasu
	auto durationBF = chrono::duration_cast<chrono::microseconds>(stopBF - startBF);
	cout << endl << "Czas trwania obliczen dla Bellmana Forda: " << durationBF.count() << " mikrosekund" << endl;	

	// realizacja algorytmu
	Dijkstra dj;
	dj.importData("data.txt");
	dj.source(0);
	auto startDJ = chrono::high_resolution_clock::now();
	dj.doAllMagic();
	auto stopDJ = chrono::high_resolution_clock::now();
	dj.show();

	//wyświetlanie czasu
	auto durationDJ = chrono::duration_cast<chrono::microseconds>(stopDJ - startDJ);
	cout << endl << "Czas trwania obliczen dla Dijkstry: " << durationDJ.count() << " mikrosekund" << endl;

	return 0;
}
