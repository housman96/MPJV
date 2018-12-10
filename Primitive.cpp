#include "Primitive.h"


Primitive::Primitive(Rigidbody *body_, const Matrix34 &offset_)
{
	body = body_;
	offset = offset_;
}
