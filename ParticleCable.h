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
	ParticleCable(Particle &, Particle &, float maxLenght, float restitution);
	~ParticleCable();

	void addContact();
};

#endif

