#ifndef PARTICLEFORCEGENERATOR_H
#define PARTICLEFORCEGENERATOR_H

#include "Particle.h"


class ParticleForceGenerator
{

public:
	/* MISE A JOUR */
	virtual void updateForce(Particle *p, float duration) = 0;
};

#endif