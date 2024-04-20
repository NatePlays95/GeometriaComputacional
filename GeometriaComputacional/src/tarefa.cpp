#include "vmath.h"
#include "tarefa.h"

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