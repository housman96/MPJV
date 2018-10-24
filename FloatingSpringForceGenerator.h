#ifndef FLOATINGSPRINGFORCEGENERATOR_H
#define FLOATINGSPRINGFORCEGENERATOR_H

#include "Vect3D.h"
#include "ParticleForceGenerator.h"

class FloatingSpringForceGenerator : public ParticleForceGenerator
{
private:
	Vect3D waterPos;
	float liquidDensity;
	float maxObjectDepth;
	float objectVolume;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	FloatingSpringForceGenerator(const Vect3D, const float, const float, const float); /* Constructeur par defaut */
	FloatingSpringForceGenerator(const FloatingSpringForceGenerator &);                /* Constructeur de recopie */
	FloatingSpringForceGenerator(const FloatingSpringForceGenerator *);                /* Constructeur par pointeur */

	/* MISE A JOUR */
	virtual void updateForce(Particle *, float);
};

#endif
