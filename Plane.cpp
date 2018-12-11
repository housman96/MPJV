#include "Plane.h"


Plane::Plane(const Vect3 &normal_, const float offset_) : Primitive(NULL, Matrix34())
{
	type = PrimType::Plane;
	normal = normal_;
	offset = offset_;
}
