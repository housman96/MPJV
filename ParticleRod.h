#ifndef PARTICLEROD_H
#define PARTICLEROD_H

#include "Particle.h" 
#include "ParticleLink.h"
#include "ParticleContact.h"
#include "ParticleLink.h"
#include "GameLoop.h"


class ParticleRod : public ParticleLink
{
private:
	float lenght;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	ParticleRod(Particle *, Particle *, float);
	~ParticleRod();

	/* MISE A JOUR */
	void addContact();
};

#endif

