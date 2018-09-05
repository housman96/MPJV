#include "Vect3D.h"

using namespace std;


// ============================================================
// CONSTRUCTEURS
// ============================================================

Vect3D::Vect3D(float x_, float y_, float z_) {
	x = x_;
	y = y_;
	z = z_;
}

Vect3D::Vect3D(const Vect3D &other) {
	x = other.x;
	y = other.y;
	z = other.z;
}


// ============================================================
// METHODES OUTIL
// ============================================================

Vect3D Vect3D::copy() {
	Vect3D newVect(*this);
	return newVect;
}


// ============================================================
// OPERATIONS
// ============================================================

Vect3D Vect3D::add(const Vect3D &other) {
	Vect3D newVect;
	newVect.x = x + other.x;
	newVect.y = y + other.y;
	newVect.z = z + other.z;
	return newVect;
}

Vect3D Vect3D::scale(const float k) {
	Vect3D newVect(*this);
	newVect.x *= k;
	newVect.y *= k;
	newVect.z *= k;
	return newVect;
}

Vect3D Vect3D::mult(const Vect3D &other) {
	Vect3D newVect;
	newVect.x = x * other.x;
	newVect.y = y * other.y;
	newVect.z = z * other.z;
	return newVect;
}

float Vect3D::dot(const Vect3D &other) {
	return x * other.x + y * other.y + z * other.z;
}

Vect3D Vect3D::cross(const Vect3D &other) {
	Vect3D newVect;
	newVect.x = y * other.z - z * other.y;
	newVect.y = z * other.x - x * other.z;
	newVect.z = x * other.y - y * other.x;
	return newVect;
}


// ============================================================
// METHODES LIEES A LA NORME
// ============================================================

float Vect3D::mag() {
	return sqrt(x * x + y * y + z * z);
}

float Vect3D::magSq() {
	return x * x + y * y + z * z;
}

Vect3D Vect3D::normalize() {
	Vect3D newVect(*this);
	float scaler = 1.0 / newVect.mag();
	newVect = newVect.scale(scaler);
	return newVect;
}


// ============================================================
// METHODES STATIQUES
// ============================================================

Vect3D Vect3D::proj(Vect3D &u, Vect3D &v) {
	Vect3D newVect(v);
	float scaler = u.dot(v) / v.magSq();
	newVect = newVect.scale(scaler);
	return newVect;
}

float Vect3D::dist(Vect3D &u, Vect3D &v) {
	return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y) + (u.z - v.z) * (u.z - v.z));
}

float Vect3D::angleBetween(Vect3D &u, Vect3D &v) {
	return acos(u.dot(v) / (u.mag() * v.mag()));
}


// ============================================================
// AFFICHAGE
// ============================================================

void Vect3D::log() {
	cout << "Vect3D : (" << x << "," << y << "," << z << ")" << endl;
}
