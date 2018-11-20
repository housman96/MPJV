#ifndef DRAGGENERATOR_H
#define DRAGGENERATOR_H

#include "ParticleForceGenerator.h"
#include "Vect3.h"


class DragGenerator : public ParticleForceGenerator
{
private:
	float k1;
	float k2;

public:
	/* CONSTRUCTEURS ET DESTRUCTEUR */
	DragGenerator(const float &, const float &); /* Constructeur par defaut */
	DragGenerator(const DragGenerator &);        /* Constructeur de recopie */
	DragGenerator(const DragGenerator *);        /* Constructeur par pointeur */

	/* MISE A JOUR */
	void updateForce(Particle *, float);
	void updateForce(Rigidbody *p, float duration);
};

#endif
