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
#include <algorithm>
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


void runAllOperations(const vector<string>& data, long long results[4][3]) {
	vector<string> v, dataCopy = data;
	list<string> l;
	set<string> s;


	results[0][0] = measureTime([&]() { v = data; });
	results[0][1] = measureTime([&]() {l.assign(data.begin(), data.end()); });
	s.clear();
	results[0][2] = measureTime([&]() {s.insert(data.begin(), data.end()); });


	results[1][0] += measureTime([&]() { sort(v.begin(), v.end()); });
	results[1][1] += measureTime([&]() {l.sort(); });
	results[1][2] += -1;

	results[2][0] += measureTime([&]() { v.insert(v.begin() + v.size() / 2, "TESTCODE"); });
	results[2][1] += measureTime([&]() {auto it = l.begin(); advance(it, l.size() / 2); l.insert(it, "TESTCODE"); });
	results[2][2] += measureTime([&]() {s.insert("TESTCODE"); });

	results[3][0] += measureTime([&]() {v.erase(v.begin() + v.size() / 2); });
	results[3][1] += measureTime([&]() {auto it = l.begin(); advance(it, l.size() / 2); l.erase(it); });
	results[3][2] += measureTime([&]() {s.erase(*next(s.begin(), s.size() / 2)); });
}

int main() {
	string filename = "codes.txt";
	vector<string> data = loadData(filename);
	cout << "Data loaded with size: " << data.size() << endl;

	const int numRuns = 15;
	long long results[4][3] = { 0 };

	for (int i = 0; i < numRuns; ++i) {
		runAllOperations(data, results);
	}

	cout << "Number of simulation: " << numRuns << endl;
	cout << "Operation    Vector     List       Set" << endl;
	cout << "Read        " << results[0][0] / numRuns << "     " << results[0][1] / numRuns << "     " << results[0][2] / numRuns << endl;
	cout << "Sort        " << results[1][0] / numRuns << "     " << results[1][1] / numRuns << "     -1" << endl;
	cout << "Insert      " << results[2][0] / numRuns << "     " << results[2][1] / numRuns << "     " << results[2][2] / numRuns << endl;
	cout << "Delete      " << results[3][0] / numRuns << "     " << results[3][1] / numRuns << "     " << results[3][2] / numRuns << endl;

	return 0;
}