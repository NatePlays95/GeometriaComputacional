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
double vec2::toPseudoAngle() {
	if (this->y <= 0) {
		//First or second quadrant
		if (this->x >= 0) {
			//First quadrant
			if (this->x == 0 && this->y == 0) {
				return 0;
			}
			else if (this->x >= std::abs(this->y)) {
				//Side Edge -> 0 <= value <= 1
				return (std::abs(this->y)) / this->x;
			}
			else {
				//Top Edge -> 1 < value <= 2
				return 2 - (this->x / std::abs(this->y));
			}
		}
		else {
			//Second quadrant
			if (this->y < this->x) {
				//Top Edge -> 2 < value < 3
				return 2 + (this->x / this->y);
			}
			else {
				//Side Edge -> 3 <= value <= 4
				return 4 - (this->y / this->x);
			}
		}
	}
	else {
		//Third or fourth quadrant
		if (this->x <= 0) {
			//Third quadrant
			if (std::abs(this->x) >= this->y) {
				//Side Egde -> 4 < value <= 5
				return 4 + (this->y / std::abs(this->x));
			}
			else {
				//Top Edge -> 5 < value <= 6
				return 6 - (std::abs(this->x) / this->y);
			}
		}
		else {
			//Fourth quadrant
			if (this->y > this->x) {
				//Top Edge -> 6 < value < 7
				return 6 + (this->x / this->y);
			}
			else {
				//Side Edge -> 7 <= value < 8
				return 8 - (this->y / this->x);
			}
		}
	}
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