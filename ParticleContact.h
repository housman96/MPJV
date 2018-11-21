#ifndef PARTICLECONTACT_H
#define PARTICLECONTACT_H

#include "Particle.h"
#include "Vect3.h"


class ParticleContact
{
private:
	Particle **particles; /* Les deux particules en contact */
	float c;                /* Coefficient de restitution */
	float d;                /* Interpenetration */
	Vect3 n;               /* Normale au point de contact */
	float Vs;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	ParticleContact(Particle *, Particle *, float);
	ParticleContact(Particle *, float, Vect3, float);

	~ParticleContact();

	/* MISE A JOUR */
	void resolve();
	float calcVs();
	void resolveVelocity();
	void resolveInterpenetration();
};

#endif
