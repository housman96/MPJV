#include "SpringForceGenerator.h"


// ============================================================
// CONSTRUCTEURS ET DESTRUCTEUR
// ============================================================

SpringForceGenerator::SpringForceGenerator(Particle *p, const float k_, const float l0_)
{
	otherP = p;
	k = k_;
	l0 = l0_;
}

SpringForceGenerator::SpringForceGenerator(const SpringForceGenerator& other)
{
	otherP = other.otherP;
	k = other.k;
	l0 = other.l0;
}

SpringForceGenerator::SpringForceGenerator(const SpringForceGenerator* other)
{
	otherP = other->otherP;
	k = other->k;
	l0 = other->l0;
}

SpringForceGenerator::~SpringForceGenerator()
{
	delete otherP;
}


// ============================================================
// MISE A JOUR
// ============================================================

void SpringForceGenerator::updateForce(Particle* p, float duration)
{
	Vect3 d = p->getPosition().sub(otherP->getPosition());
	Vect3 springForce = d.normalize();
	springForce = springForce.scale(-k * (d.mag() - l0));
	p->applyForce(springForce);
}

void SpringForceGenerator::updateForce(Rigidbody * p, float duration)
{
}
