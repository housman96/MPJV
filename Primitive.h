#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Rigidbody.h"
#include "Matrix34.h"


class Primitive
{
public:
	Rigidbody* body;
	Matrix34 offset;

	Primitive(Rigidbody*, const Matrix34&);
};


#endif