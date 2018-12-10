#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"


class Sphere : public Primitive
{
public:
	float radius;

	Sphere(Rigidbody*, const Matrix34&, float);
};


#endif