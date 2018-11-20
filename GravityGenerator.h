#ifndef GRAVITYGENERATOR_H
#define GRAVITYGENERATOR_H

#include "ParticleForceGenerator.h"
#include "Rigidbody.h"
#include "Vect3.h"


class GravityGenerator : public ParticleForceGenerator
{
private:
	Vect3 gravity;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	GravityGenerator(const Vect3 &);	        /* Constructeur par defaut */
	GravityGenerator(const GravityGenerator &); /* Constructeur de recopie */
	GravityGenerator(const GravityGenerator *); /* Constructeur par pointeur */

	/* MISE A JOUR */
	void updateForce(Particle *, float);
	void updateForce(Rigidbody *p, float duration);
};

#endif
