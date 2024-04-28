#pragma once
#include "vmath.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class ObjUtils {
public:
	static vector<vec2> loadFromFile(string filename) {
		string filepath = "assets/" + filename;
		cout << "filepath: " << filepath << endl;
		vector<vec2> object;
		ifstream inFile(filepath);
		if (!inFile.is_open()) {
			cerr << "Erro ao abrir o arquivo." << endl;
			return object;
		}
		string line;
		while (std::getline(inFile, line)) {
			cout << "line: " << line << endl;
		}
		inFile.close();
		return object;
	}
};
