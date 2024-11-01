// Melissa Ochoa Flores
// COMSC 210
// Data structures race 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <list>
#include <set>
using namespace std;


vector<string> loadData(const string& filename) {
	vector<string> data;
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		data.push_back(line);
	}
}

template<typename Func>
long long measureTime(Func func, int repeat = 10) {
	long long totalDuration = 0;
	for (int i = 0; i < reapeat; ++i) {
		auto start = chrono::high_resolution_clock::now();
		func();
		auto end = chrono::high_resolution_clock::now();
		totalDuration += chrono::duration_cast<chrono::microseconds>(end - start).count();
	}
	return totalDuration / repeat;
}


void raceRead(const vector<string>& data, vector<string>& v, list<string>& l, set<string>& s, long long results[3]) {
	v.reserve(data.size());
	results[0] = measureTime([&]() { v = data; });
	results[1] = measureTime([&]() {l.assign(data.begin(), data.end()); });
	results[2] = measureTime([&]() {s.insert(data.begin(), data.end()); });
}

int main() {
	string filename = "codes.txt";
	vector<string> data = loadData(filename);
	cout << "Data loaded with size: " << data.size() << endl;
}