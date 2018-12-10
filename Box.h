#ifndef BOX_H
#define BOX_H

#include "Primitive.h"
#include "Vect3.h"


class Box : public Primitive
{
public:
	Vect3 halfSizes;

	Box(Rigidbody*, const Matrix34&, const Vect3&);
};


#endif 