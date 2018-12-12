#ifndef PLANE_H
#define PLANE_H

#include "Primitive.h"
#include "Vect3.h"


class Plane : public Primitive
{
public:
	Vect3 normal;
	float offset;

	Plane(const Vect3 &, const float);
};


#endif