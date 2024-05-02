#pragma once
#include "vmath.h"
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct MeshFace {
	vector<unsigned int> vertexIndices;
};

class Mesh {
protected:
	string name;
	vector<vec2> vertices;
	vector<MeshFace*> faces; //edges are faces
public:
	~Mesh() {
		for (MeshFace* face : faces) delete face;
		faces.clear();
	}

	string getName() { return name; }
	void setName(const string& newName) { name = newName; }
	vector<vec2>* getVertices() { return &vertices; }
	vector<MeshFace*>* getFaces() { return &faces; }
	void addVertex(vec2 v) { vertices.push_back(v); }
	void addFace(MeshFace* f) { faces.push_back(f); }
};

class ObjUtils {
public:

	// filename é formatado como "<nome>.obj"
	static vector<Mesh*>* loadFromFile(string filename) {
		string filepath = "assets/" + filename;
		cout << "loading obj from filepath: " << filepath << endl;
		vector<Mesh*>* meshes = new vector<Mesh*>();
		
		ifstream inFile(filepath);
		if (!inFile.is_open()) {
			cerr << "Erro ao abrir o arquivo." << endl;
			return meshes;
		}

		string line;
		Mesh* currentMesh = nullptr;
		while (std::getline(inFile, line)) {
			cout << "line: " << line << endl;
			if (line.empty() || line[0] == '#') continue;
	
			istringstream iss(line);
			string token;
			iss >> token;

			if (token == "o") {
				currentMesh = new Mesh();
				meshes->push_back(currentMesh);
				// pegar nome
				string name = line.substr(2); // exclui
				currentMesh->setName(name);
				cout << currentMesh->getName() << endl;
				continue;
			}
			if (currentMesh == nullptr) continue;

			if (token == "v") {
				double x, y;
				iss >> x; iss >> y;
				vec2 point(x, y);
				currentMesh->addVertex(point);
			}

			if (token == "f") {
				MeshFace* face = new MeshFace();
				while (!iss.eof()) { //while not reached End of File
					string faceStr;
					iss >> faceStr;
					string vertexIndexStr = faceStr.substr(0, faceStr.find('/'));
					istringstream viiss(vertexIndexStr);
					int vertexIndex;
					viiss >> vertexIndex;
					face->vertexIndices.push_back(vertexIndex);
				}
				currentMesh->addFace(face);
			}

			continue;

		}
		inFile.close();
		return meshes;
	}

	// filename é formatado como "<nome>.obj"
	static int saveToFile(vector<Mesh*>* meshes, string filename) {
		string filepath = "output/" + filename;
		cout << "saving obj to filepath: " << filepath << endl;
		
		ofstream outFile(filepath);
		if (!outFile.is_open()) {
			cerr << "Erro ao abrir o arquivo." << endl;
			return 1;
		}

		for (Mesh* currentMesh : *meshes) {
			outFile << "o " << currentMesh->getName() << endl;

			for (vec2 vertex : *(currentMesh->getVertices())) {
				outFile << "v " << vertex.x << " " << vertex.y << " 0.0" << endl;
			}

			for (MeshFace* face : *(currentMesh->getFaces())) {
				outFile << "f ";
				for (int vertexIndex : face->vertexIndices) {
					outFile << vertexIndex << " ";
				}
				outFile << endl;
			}
		}

		outFile.close();
		return 0;
	}
};
