#pragma once
#include "Particle.h"
#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator
{
private:
	Particle *particles[2];
public:
	/*Constructeur et destructeur*/
	ParticleLink(Particle &, Particle &);
	~ParticleLink();

	float currentLenght()const;
};

