#ifndef SPRINGFORCEGENERATOR_H
#define SPRINGFORCEGENERATOR_H

#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vect3.h"


class SpringForceGenerator : public ParticleForceGenerator
{
private:
	Particle * otherP;
	float k;
	float l0;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	SpringForceGenerator(Particle *, const float, const float); /* Constructeur par defaut */
	SpringForceGenerator(const SpringForceGenerator &);		    /* Constructeur de recopie */
	SpringForceGenerator(const SpringForceGenerator *);		    /* Constructeur par pointeur */
	~SpringForceGenerator();

	/* MISE A JOUR */
	virtual void updateForce(Particle *, float);
};

#endif
