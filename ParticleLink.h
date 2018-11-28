#ifndef PARTICLELINK_H
#define PARTICLELINK_H

#include "Particle.h"
#include "ParticleContactGenerator.h"


class ParticleLink : public ParticleContactGenerator
{
protected:
	Particle **particles;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	ParticleLink(Particle *, Particle *);
	~ParticleLink();

	/* METHODE */
	float currentLenght() const;
};

#endif

