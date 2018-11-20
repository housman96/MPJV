#include "GravityGenerator.h"


// ============================================================
// CONSTRUCTEURS
// ============================================================

GravityGenerator::GravityGenerator(const Vect3 &grav)
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


// ============================================================
// MISE A JOUR
// ============================================================

void GravityGenerator::updateForce(Particle *p, float duration)
{
	Vect3 weight = gravity.scale(p->getMass());
	p->applyForce(weight);
}

void GravityGenerator::updateForce(Rigidbody *p, float duration)
{
	Vect3 weight = gravity.scale(p->getMass());
	p->addForceAtBodyPoint(weight, Vect3());
}
