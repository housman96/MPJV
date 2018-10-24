#include "AnchoredSpringForceGenerator.h"


// ============================================================
// CONSTRUCTEURS
// ============================================================
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(const Vect3D point_, const float k_, const float l0_)
{
	this->point = point_;
	this->k = k_;
	this->l0 = l0_;
}

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(const AnchoredSpringForceGenerator &other)
{
	point = other.point;
	k = other.k;
	l0 = other.l0;
}

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(const AnchoredSpringForceGenerator *other)
{
	point = other->point;
	k = other->k;
	l0 = other->l0;
}


// ============================================================
// MISE A JOUR
// ============================================================

void AnchoredSpringForceGenerator::updateForce(Particle *p, float duration)
{
	Vect3D d = p->getPosition().sub(point);
	Vect3D springForce = d.normalize();
	springForce = springForce.scale(-k * (d.mag() - l0));
	p->applyForce(springForce);
}
