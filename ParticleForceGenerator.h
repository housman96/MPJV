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
		if ((typeid(*p).hash_code() == typeid(new Particle()).hash_code())) {
			updateForce((Particle*)p, duration);
		}
		if (typeid(*p).hash_code() == typeid(new Rigidbody()).hash_code()) {
			updateForce((Rigidbody*)p, duration);
		}
	};
	virtual void updateForce(Particle *p, float duration) = 0;
	virtual void updateForce(Rigidbody *p, float duration) = 0;
};

#endif