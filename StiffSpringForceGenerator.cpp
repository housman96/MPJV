#include "StiffSpringForceGenerator.h"


// ============================================================
// CONSTRUCTEURS
// ============================================================

StiffSpringForceGenerator::StiffSpringForceGenerator(const Vect3 pos, const float k_, const float d_)
{
	this->anchorPos = pos;
	this->k = k_;
	this->d = d_;
}

StiffSpringForceGenerator::StiffSpringForceGenerator(const StiffSpringForceGenerator& other)
{
	anchorPos = other.anchorPos;
	k = other.k;
	d = other.d;
}

StiffSpringForceGenerator::StiffSpringForceGenerator(const StiffSpringForceGenerator* other)
{
	anchorPos = other->anchorPos;
	k = other->k;
	d = other->d;
}


// ============================================================
// MISE A JOUR
// ============================================================

void StiffSpringForceGenerator::updateForce(Particle* p, float duration)
{
	Vect3 p0 = p->getPosition();
	Vect3 v0 = p->getVelocity();
	float m = p->getMass();

	float gamma = 0.5 * sqrt(4 * k - d * d);
	Vect3 c = p0.scale(d / (2 * gamma));
	c = c.add(v0.scale(1. / gamma));

	Vect3 pt = p0.scale(cos(gamma * duration));
	pt = pt.add(c.scale(sin(gamma * duration)));
	pt = pt.scale(exp((-d * duration) / gamma));

	Vect3 acc = pt.sub(p0);
	acc = acc.scale(1. / (duration * duration));
	acc = acc.sub(v0);

	Vect3 force = acc.scale(m);
	p->applyForce(force);
}
