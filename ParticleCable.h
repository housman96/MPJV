#ifndef PARTICLECABLE_H
#define PARTICLECABLE_H

#include "Particle.h" 
#include "ParticleLink.h"
#include "ParticleContact.h"


class ParticleCable : public ParticleLink
{
private:
	float maxLenght;
	float restitution;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	ParticleCable(Particle *, Particle *, float, float);
	~ParticleCable();

	/* MISE A JOUR */
	void addContact();
};

#endif

