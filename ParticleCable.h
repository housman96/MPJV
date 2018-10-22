#pragma once
#include "Particle.h" 
#include "ParticleLink.h"

class ParticleCable : public ParticleLink
{
private:
	float maxLenght;
	float restituion;

public:
	ParticleCable(Particle &, Particle &);
	~ParticleCable();
};

