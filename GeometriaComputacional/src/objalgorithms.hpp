
#include "algorithms.h"
#include "objutils.hpp"


using namespace std;

vector<Mesh*>* jarvisObj(vector<Mesh*>* meshes) {
	vector<Mesh*>* convexedMeshes = new vector<Mesh*>();

	for (Mesh* mesh : *meshes) {
		//cout << "MESHHHH: " << mesh->getName() << endl;
		Mesh* newMesh = new Mesh();
		newMesh->setName(mesh->getName());

		//deconstruct each "object", just get all the points
		vector<vec2>* vertices = mesh->getVertices();

		//do the jarvis method
		vector<vec2> convexHull = jarvis(vertices);

		//reconstruct a single face with all the points
		MeshFace* newFace = new MeshFace();
		unsigned int currentVertexIndex = 0;
		for (vec2 point : convexHull) {
			newMesh->addVertex(point);
			newFace->vertexIndices.push_back(currentVertexIndex);
			currentVertexIndex += 1;
		}
		newMesh->addFace(newFace);

		//save each individual object
		convexedMeshes->push_back(newMesh);
	}

	return convexedMeshes;
}