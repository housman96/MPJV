#include "Box.h"


Box::Box(Rigidbody* body_, const Matrix34& offset_, const Vect3& halfSizes_) : Primitive(body_, offset_)
{
	halfSizes = halfSizes_;
}
