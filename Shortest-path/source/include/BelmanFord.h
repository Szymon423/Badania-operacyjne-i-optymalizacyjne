#pragma once

#include <vector>
#include <iostream>

using namespace std;

class BellmanFord {
private:
	int N;
	vector <vector <int>> X;
	vector <int> dist;

public:
	
private:

public:
	BellmanFord();
	~BellmanFord();
	void importData(string);
	void show();
	void doAllMagic();
};

