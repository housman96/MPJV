#include "Quaternion.h"

using namespace std;


Quaternion::Quaternion(float r_, float i_, float j_, float k_)
{
	r = r_;
	i = i_;
	j = j_;
	k = k_;
}

Quaternion::Quaternion(const Quaternion& other)
{
	r = other.r;
	i = other.i;
	j = other.j;
	k = other.k;
}


void Quaternion::log()
{
	cout << "Quaternion : (" << r << "," << i << "," << j << "," << k << ")" << endl;
}


Quaternion Quaternion::normalize()
{
	float d = r * r + i * i + j * j + k * k;
	if (d == 0) {
		return Quaternion(1, 0, 0, 0);
	} else {
		d = 1.0f / sqrt(d);
		return Quaternion(d*r, d*i, d*j, d*k);
	}

}

Quaternion Quaternion::add(const Quaternion& other)
{
	return Quaternion(r + other.r, i + other.i, j + other.j, k + other.k);
}

Quaternion Quaternion::scale(const float scaler)
{
	return Quaternion(scaler * r, scaler * i, scaler * j, scaler * k);
}

Quaternion Quaternion::mult(const Quaternion& other)
{
	float newR = other.r * r - other.i * i - other.j * j - other.k * k;
	float newI = other.r * i + other.i * r - other.j * k + other.k * j;
	float newJ = other.r * j + other.i * k + other.j * r - other.k * i;
	float newK = other.r * k - other.i * j + other.j * i + other.k * r;
	return Quaternion(newR, newI, newJ, newK);
}

void Quaternion::rotate(Vect3 v)
{
	Quaternion q(0, v.getX(), v.getY(), v.getZ());
	*this = this->mult(q);
}

void Quaternion::updateAngularVelocity(Vect3 v, float t)
{
	Quaternion q(0, v.getX(), v.getY(), v.getZ());
	q = q.mult(*this).scale(t / 2.f);
	*this = this->add(q);
}