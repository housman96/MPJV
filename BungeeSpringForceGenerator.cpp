#include "BungeeSpringForceGenerator.h"


// ============================================================
// CONSTRUCTEURS ET DESTRUCTEUR
// ============================================================

BungeeSpringForceGenerator::BungeeSpringForceGenerator(Particle* p, const float k_, const float l0_)
{
	this->otherP = p;
	this->k = k_;
	this->l0 = l0_;
}

BungeeSpringForceGenerator::BungeeSpringForceGenerator(const BungeeSpringForceGenerator& other)
{
	otherP = other.otherP;
	k = other.k;
	l0 = other.l0;
}

BungeeSpringForceGenerator::BungeeSpringForceGenerator(const BungeeSpringForceGenerator* other)
{
	otherP = other->otherP;
	k = other->k;
	l0 = other->l0;
}

BungeeSpringForceGenerator::~BungeeSpringForceGenerator()
{
	delete otherP;
}


// ============================================================
// MISE A JOUR
// ============================================================

void BungeeSpringForceGenerator::updateForce(Particle* p, float duration)
{
	Vect3 springForce;
	Vect3 d = p->getPosition().sub(otherP->getPosition());
	float mag = d.mag();

	if (mag <= l0) {
		springForce = new Vect3(0, 0, 0);
	} else {
		springForce = d.normalize();
		springForce = springForce.scale(-k * (mag - l0));
	}

	p->applyForce(springForce);
}
