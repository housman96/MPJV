#include "Vect3.h"

using namespace std;


// ============================================================
// CONSTRUCTEURS
// ============================================================

Vect3::Vect3(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

Vect3::Vect3(const Vect3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vect3::Vect3(const Vect3* other)
{
	x = other->x;
	y = other->y;
	z = other->z;
}


// ============================================================
// ASCESSEURS
// ============================================================

float Vect3::getX()
{
	return x;
}

float Vect3::getY()
{
	return y;
}
float Vect3::getZ()
{
	return z;
}

void Vect3::setX(float x)
{
	this->x = x;
}

void Vect3::setY(float y)
{
	this->y = y;
}
void Vect3::setZ(float z)
{
	this->z = z;
}


// ============================================================
// AFFICHAGE
// ============================================================

void Vect3::log()
{
	cout << "Vect3 : (" << x << "," << y << "," << z << ")" << endl;
}


// ============================================================
// OPERATIONS
// ============================================================

Vect3 Vect3::add(const Vect3& other)
{
	Vect3 newVect;
	newVect.x = x + other.x;
	newVect.y = y + other.y;
	newVect.z = z + other.z;
	return newVect;
}

Vect3 Vect3::sub(const Vect3& other)
{
	Vect3 newVect;
	newVect.x = x - other.x;
	newVect.y = y - other.y;
	newVect.z = z - other.z;
	return newVect;
}

Vect3 Vect3::scale(const float k)
{
	Vect3 newVect(*this);
	newVect.x *= k;
	newVect.y *= k;
	newVect.z *= k;
	return newVect;
}

Vect3 Vect3::mult(const Vect3& other)
{
	Vect3 newVect;
	newVect.x = x * other.x;
	newVect.y = y * other.y;
	newVect.z = z * other.z;
	return newVect;
}

float Vect3::dot(const Vect3& other)
{
	return x * other.x + y * other.y + z * other.z;
}

Vect3 Vect3::cross(const Vect3& other)
{
	Vect3 newVect;
	newVect.x = y * other.z - z * other.y;
	newVect.y = z * other.x - x * other.z;
	newVect.z = x * other.y - y * other.x;
	return newVect;
}


// ============================================================
// MANIPULATION DE LA NORME
// ============================================================

float Vect3::mag()
{
	return sqrt(x * x + y * y + z * z);
}

float Vect3::magSq()
{
	return x * x + y * y + z * z;
}

Vect3 Vect3::normalize()
{
	Vect3 newVect(*this);
	float mag = newVect.mag();
	if (mag != 0) {
		float scaler = 1.0 / mag;
		newVect = newVect.scale(scaler);
	}
	return newVect;
}


// ============================================================
// METHODES STATIQUES
// ============================================================

Vect3 Vect3::proj(Vect3& u, Vect3& v)
{
	Vect3 newVect(v);
	float scaler = u.dot(v) / v.magSq();
	newVect = newVect.scale(scaler);
	return newVect;
}

float Vect3::dist(Vect3& u, Vect3& v)
{
	return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y) + (u.z - v.z) * (u.z - v.z));
}

float Vect3::angleBetween(Vect3& u, Vect3& v)
{
	return acos(u.dot(v) / (u.mag() * v.mag()));
}
