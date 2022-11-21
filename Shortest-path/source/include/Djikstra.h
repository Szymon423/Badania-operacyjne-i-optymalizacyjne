#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Dijkstra {
private:
	int N;
	vector <vector <int>> X;
	vector <int> dist;
	vector <bool> isOk;
	vector <int> path;
	bool cycle;
	int src;
	int cnt;
	
public:

private:
	int minNeighbour();
	void printPath(int, vector <int>);
public:
	Dijkstra();
	~Dijkstra();
	void importData(string);
	void show();
	void doAllMagic();
	void source(int);
};

