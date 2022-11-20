#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Djikstra {
private:
	int N;
	vector <vector <int>> X;
	vector <int> dist;
	vector <bool> isOk;
	vector <int> path;
	bool cycle;
	int src;
	
public:

private:
	int minNeighbour();
	void printPath(int, vector <int>);
public:
	Djikstra();
	~Djikstra();
	void importData(string);
	void show();
	void doAllMagic();
	void source(int);
};

