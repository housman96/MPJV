#ifndef PARTICLEFORCEGENERATOR_H
#define PARTICLEFORCEGENERATOR_H

#include "Particle.h"
#include <typeinfo>
#include "Rigidbody.h"


class ParticleForceGenerator
{

public:
	/* MISE A JOUR */
	void updateForce(GameObject *p, float duration) {
		if (p->t == Type::Particle) {
			updateForce((Particle*)p, duration);
		}
		if (p->t == Type::Rigibody) {
			updateForce((Rigidbody*)p, duration);
		}
	};
	virtual void updateForce(Particle *p, float duration) = 0;
	virtual void updateForce(Rigidbody *p, float duration) = 0;
};

#endif