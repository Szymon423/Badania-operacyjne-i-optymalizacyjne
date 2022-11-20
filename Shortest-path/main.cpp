#include <iostream>
#include <chrono>
#include "BellmanFord.h"
#include "Djikstra.h"


int main() {
	
	// pomiar czasu dla Bellmana Forda:
	auto startBF = chrono::high_resolution_clock::now();

	// realizacja algorytmu
	BellmanFord bf;
	bf.importData("data.txt");
	bf.doAllMagic();
	auto stopBF = chrono::high_resolution_clock::now();
	bf.show();

	//wyświetlanie czasu
	
	auto durationBF = chrono::duration_cast<chrono::microseconds>(stopBF - startBF);
	cout << endl << "Czas trwania obliczen dla Bellmana Forda: " << durationBF.count() << " mikrosekund" << endl;

	// pomiar czasu dla Djikstry:
	auto startDJ = chrono::high_resolution_clock::now();

	// realizacja algorytmu
	Djikstra dj;
	dj.importData("data.txt");
	dj.source(0);
	dj.doAllMagic();
	auto stopDJ = chrono::high_resolution_clock::now();
	dj.show();

	//wyświetlanie czasu
	
	auto durationDJ = chrono::duration_cast<chrono::microseconds>(stopDJ - startDJ);
	cout << endl << "Czas trwania obliczen dla Bellmana Forda: " << durationDJ.count() << " mikrosekund" << endl;

	return 0;
}
