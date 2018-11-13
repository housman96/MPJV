#ifndef STIFFSPRINGFORCEGENERATOR_H
#define STIFFSPRINGFORCEGENERATOR_H

#include "Vect3.h"
#include "ParticleForceGenerator.h"


class StiffSpringForceGenerator : public ParticleForceGenerator
{
private:
	Vect3 anchorPos;
	float k;
	float d;

public:
  /* CONSTRUCTEURS ET DESTRUCTEUR */
	StiffSpringForceGenerator(const Vect3, const float, const float); /* Constructeur par dÃ©faut */
	StiffSpringForceGenerator(const StiffSpringForceGenerator &);      /* Constructeur de recopie */
	StiffSpringForceGenerator(const StiffSpringForceGenerator *);      /* Constructeur par pointeur */

	virtual void updateForce(Particle *, float);
};

#endif
