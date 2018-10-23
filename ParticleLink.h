#ifndef PARTICLELINK_H
#define PARTICLELINK_H

#include "Particle.h"
#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator
{
protected:
	Particle *particles[2];


public:
	/*Constructeur et destructeur*/
	ParticleLink(Particle &, Particle &);
	~ParticleLink();

	float currentLenght()const;
};

#endif

