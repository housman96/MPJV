#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <cmath>
#include "Vect3.h"


class Quaternion
{

public:
	float r, i, j, k;
	/*CONSTRUCTEURS*/
	Quaternion(float = 0, float = 0, float = 0, float = 0);
	Quaternion(const Quaternion &);
	Quaternion(const Quaternion *);

	/*AFFICHAGE*/
	void log();

	/*OPERATIONS*/
	Quaternion normalize();
	Quaternion add(const Quaternion &);
	Quaternion scale(const float);
	Quaternion mult(const Quaternion &);
	void rotate(Vect3);
	void updateAngularVelocity(Vect3, float);
};

#endif