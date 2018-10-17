#include "GravityGenerator.h"

GravityGenerator::GravityGenerator(const Vect3D &grav)
{
	this->gravity = grav;
}

GravityGenerator::GravityGenerator(const GravityGenerator &other)
{
	gravity = other.gravity;
}

GravityGenerator::GravityGenerator(const GravityGenerator *other)
{
	gravity = other->gravity;
}

void GravityGenerator::updateForce(Particle *p, float duration)
{
	Vect3D weight = gravity.scale(p->getMass());
	p->applyForce(weight);
}