#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <cmath>
#include "Vect3.h"


class Quaternion
{
private:
	float r, i, j, k;

public:
	Quaternion(float = 0, float = 0, float = 0, float = 0);
	Quaternion(const Quaternion &);

	void log();

	Quaternion normalize();
	Quaternion add(const Quaternion &);
	Quaternion scale(const float);
	Quaternion mult(const Quaternion &);
	void rotate(Vect3);
	void updateAngularVelocity(Vect3, float);
};

#endif