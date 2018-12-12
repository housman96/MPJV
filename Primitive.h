#ifndef PRIMITIVE_H
#define PRIMITIVE_H

enum class PrimType { Plane, Box, Sphere };

#include "Rigidbody.h"
#include "Matrix34.h"

class Primitive
{
public:
	PrimType type;
	Rigidbody* body;
	Matrix34 offset;

	Primitive(Rigidbody*, const Matrix34&);
};


#endif