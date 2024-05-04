#include "vmath.h"
#include "algorithms.h"
#include "tarefa.h"

#include <vector>

using namespace std;




void tarefa2_q3() {
	vec2 v1 = vec2(1.5, 2.5);
	vec2 v2 = vec2(-0.4, 0.8);
	cout << "v1: " << v1 << endl << "v2: " << v2 << endl << endl;

	cout << "soma v1 + v2:  " << v1 + v2 << endl;
	cout << "subtracao v1 - v2:  " << v1 - v2 << endl << endl;

	cout << "multiplicacao v1 * 2:  " << v1 * 2 << endl;
	cout << "divisao v2 / 2:  " << v2 / 2 << endl;

	cout << "magnitude |v1|:  " << v1.mag() << endl; //2.91547...
	cout << "prod. escalar v1 * v2:  " << v1.dot(v2) << endl; //1.4
	cout << "prod. vetorial v1 x v2:  " << v1.cross(v2) << endl; //2.2

	cout << endl << "-- Casos Patologicos --" << endl;
	cout << "prod. escalar ortogonal (2.5, 0)*(0, 2.5):  " << vec2(2.5, 0).dot(vec2(0, 2.5)) << endl;
	cout << "prod. escalar colinear (1.5, 2.5)*(-3, -5) = -1*5*10:  " << vec2(4, 3).dot(vec2(-8, -6)) << endl;
	cout << "prod. escalar nulo (1.5, 2.5)*(0, 0):  " << v1.dot(vec2::ZERO) << endl;
	cout << "prod. vetorial paralelo (1.5, 2.5)x(-3, -5):  " << v1.cross(v1 * 2) << endl;
	cout << "prod. vetorial ortogonal ccw (2.5, 0)x(0, 2.5):  " << vec2(2.5, 0).cross(vec2(0, 2.5)) << endl;
	cout << "prod. vetorial ortogonal cw (2.5, 0)x(0, -2.5):  " << vec2(2.5, 0).cross(vec2(0, -2.5)) << endl;
}

void tarefa2_q5() {
	//square
	vector<vec2>* square = new vector<vec2>();
	square->push_back(vec2(3, -2));
	square->push_back(vec2(8, -2));
	square->push_back(vec2(8, -7));
	square->push_back(vec2(3, -7));

	vector<vec2>* triangle = new vector<vec2>();
	triangle->push_back(vec2(2, 3));
	triangle->push_back(vec2(3, 5));
	triangle->push_back(vec2(4, 3));

	vec2 p1(5, -4);  //inside
	vec2 p2(10, -9); //outside

	bool isP1Inside = pointInShapeRaycast(square, p1);
	bool isP2Inside = pointInShapeRaycast(square, p2);

	cout << "teste de raycast, 1 = dentro ||| 0 = fora:" << endl;
	cout << p1 << " dentro? " << isP1Inside << endl;
	cout << p2 << " dentro? " << isP2Inside << endl;
	cout << "casos patologicos" << endl;
	vec2 p3(2, -2);
	cout << p3 << " fora, alinhado a aresta: " << pointInShapeRaycast(square, p3) << endl;
	vec2 p4(3, -5);
	cout << p4 << " em cima da aresta esquerda: " << pointInShapeRaycast(square, p4) << endl;
	p4 = vec2(8, -5);
	cout << p4 << " em cima da aresta direita: " << pointInShapeRaycast(square, p4) << endl;
	vec2 p5(8 - 0.0001, -5);
	cout << p5 << " dentro, muito proximo da aresta: " << pointInShapeRaycast(square, p5) << endl;
	vec2 p6(3, -2);
	cout << p6 << " em cima de um dos vertices, alinhado a aresta: " << pointInShapeRaycast(square, p6) << endl;
	vec2 p7(0, 5);
	cout << p7 << " passando por uma ponta de 2 arestas (triangulo): " << pointInShapeRaycast(triangle, p7) << endl;
	cout << endl;
}