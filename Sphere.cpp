#include "Sphere.h"

Sphere::Sphere(Rigidbody* body_, const Matrix34& offset_, float radius_) : Primitive(body_, offset_)
{
	radius = radius_;
}
