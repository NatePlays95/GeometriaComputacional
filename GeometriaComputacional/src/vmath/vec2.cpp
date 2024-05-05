#include "vec2.h"
#include <cmath>

#define PI 3.14159265

//Default Constructor
vec2::vec2() {
	this->x = 0;
	this->y = 0;
}

// constructor
vec2::vec2(double x_in, double y_in) {
	x = x_in; y = y_in;
}
// copy constructor
vec2::vec2(const vec2& v) {
	x = v.x; y = v.y;
}

// presets
vec2 const vec2::ZERO = vec2(0, 0);
vec2 const vec2::UP = vec2(0, -1);
vec2 const vec2::DOWN = vec2(0, 1);

// operators
//		with other vectors
vec2 operator+(const vec2& lhs, const vec2& rhs) {
	return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}
vec2 operator-(const vec2& lhs, const vec2& rhs) {
	return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}
// operators
//		with scalars
vec2 operator*(const double& scalar, const vec2& v) {
	return vec2(v.x * scalar, v.y * scalar);
}
vec2 operator*(const vec2& v, const double& scalar) {
	return vec2(v.x * scalar, v.y * scalar);
}
vec2 operator/(const vec2& v, const double& scalar) {
	return vec2(v.x / scalar, v.y / scalar);
}
// operators
//		for printing
std::ostream& operator<<(std::ostream& os, vec2 const& v) {
	return os << "vec2(" << v.x << ", " << v.y << ")";
}

// functions
double vec2::magSquared() {
	return this->x * this->x + this->y * this->y;
}
double vec2::mag() {
	return sqrt(magSquared());
}
double vec2::dot(const vec2& other) {
	return this->x * other.x + this->y * other.y;
}
double vec2::cross(const vec2& other) {
	return (this->x * other.y)  -  (this->y * other.x) ;
}

vec2 vec2::normalized() {		// corrigir bugs de -0
	return (*this / this->mag()) + vec2::ZERO;
}
vec2 vec2::floored() {
	return vec2(floor(this->x), floor(this->y));
}
vec2 vec2::clampedPositive() {
	double max_x_0 = x < 0.0 ? 0.0 : x;
	double max_y_0 = y < 0.0 ? 0.0 : y;
	return vec2(max_x_0, max_y_0);
}
vec2 vec2::project(vec2& base) {
	return base * (this->dot(base) / base.magSquared());
}
vec2 vec2::reflect(vec2& normal) {
	return *this - (normal * (this->dot(normal)) * 2);
}

double vec2::toAngle() {
	return atan2(this->y, this->x);
}

double vec2::cos() {
	return this->dot(vec2(0.0, 1.0)) / this->mag();
}

double vec2::sin() {
	//TODO
	return 0;
}

double vec2::cosPseudo() {
	//TODO
	return 0;
}

double vec2::sinPseudo() {
	//TODO	
	return 0;
}

//Diego
//0 <= PseudoAngle() < 8 (Unit Square)
//"Fowler Angles"
//TODO: checar se os pseudo angulos tao funcionando direitinho, ex. um For loop.
double vec2::toPseudoAngle() {
	double absX = abs(this->x);
	double absY = abs(this->y);
	

	if (absX == 0) {
		if (this->y == 0) return 0;
		else if (this->y > 0) return 2;
		else if (this->y < 0) return 6;
	}

	if (absY == 0) {
		if (this->x < 0) return 4;
		else if (this->x >= 0) return 0;
	}

	if (this->y >= 0) {
		//First or second quadrant
		if (this->x >= 0) {
			//First quadrant
			if (absX >= absY) {
				//Side Edge -> 0 <= value <= 1
				return absY/absX;
			}
			else {
				//Top Edge -> 1 < value <= 2
				return 2 - absX/absY;
			}
		}
		else {
			//Second quadrant
			if (absY < absX) {
				//Top Edge -> 2 < value < 3
				return 2 + absX/absY;
			}
			else {
				//Side Edge -> 3 <= value <= 4
				return 4 - absY/absX;
			}
		}
	}
	else {
		//Third or fourth quadrant
		if (this->x <= 0) {
			//Third quadrant
			if (absX >= absY) {
				//Side Egde -> 4 < value <= 5
				return 4 + absY / absX;
			}
			else {
				//Top Edge -> 5 < value <= 6
				return 6 - absX / absY;
			}
		}
		else {
			//Fourth quadrant
			if (absY > absX) {
				//Top Edge -> 6 < value < 7
				return 6 + absX / absY;
			}
			else {
				//Side Edge -> 7 <= value < 8
				return 8 - absY / absX;
			}
		}
	}
}

double vec2::toPseudoAngleGraham() {
	double p = this->x / (abs(this->x) + abs(this->y)); // -1 to 1 increasing with x
	if (this->y < 0) return 3 + p;						// 2 to 4 increasing with x
	else return 1 - p;									// 0 to 2 decreasing with x
}

//Diego
double vec2::toOrientedAngle() {
	//Polar Ordering: Order the points angularly in the CCW direction from the origin vector u = (1,0)
	if (this->y <= 0) {
		//First or second quadrant (0 <= value <= PI)
		return this->toAngle();
	}
	else {
		return (2 * PI) - this->toAngle();
	}
}