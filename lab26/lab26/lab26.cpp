// Melissa Ochoa Flores
// COMSC 210
// Data structures race 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


vector<string> loadData(const string& filename) {
	vector<string> data;
	ifstream file(filename);
	string line;
	while (getline(file, line)) {
		data.push_back(line);
	}
}


int main() {
	string filename = "codes.txt";
	vector<string> data = loadData(filename);
	cout << "Data loaded with size: " << data.size() << endl;
}