#ifndef BUNGEESPRINGFORCEGENERATOR_H
#define BUNGEESPRINGFORCEGENERATOR_H

#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vect3D.h"


class BungeeSpringForceGenerator : public ParticleForceGenerator
{
private:
	Particle* otherP;
	float k;
	float l0;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	BungeeSpringForceGenerator(Particle *, const float, const float); /* Constructeur par dÃ©faut */
	BungeeSpringForceGenerator(const BungeeSpringForceGenerator &);   /* Constructeur de recopie */
	BungeeSpringForceGenerator(const BungeeSpringForceGenerator *);   /* Constructeur par pointeur */
	~BungeeSpringForceGenerator();

	/* MISE A JOUR */
	virtual void updateForce(Particle*, float);
};

#endif
