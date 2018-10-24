#ifndef GRAVITYGENERATOR_H
#define GRAVITYGENERATOR_H

#include "ParticleForceGenerator.h"
#include "Vect3D.h"


class GravityGenerator : public ParticleForceGenerator
{
private:
	Vect3D gravity;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	GravityGenerator(const Vect3D &);	        /* Constructeur par defaut */
	GravityGenerator(const GravityGenerator &); /* Constructeur de recopie */
	GravityGenerator(const GravityGenerator *); /* Constructeur par pointeur */

	/* MISE A JOUR */
	virtual void updateForce(Particle *, float);
};

#endif
