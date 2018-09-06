#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>
#include "Vect3D.h"


class Particle {
private:
	Vect3D position;
	Vect3D velocity;
	Vect3D acceleration;
	float inverseMass;
	float damping;


public:
	Particle(Vect3D, Vect3D, float); /* Constructeur par défaut */
	Particle(const Particle &);      /* Constructeur de recopie */
	Particle(const Particle *);      /* Constructeur par pointeur */

	void setDamping(float);

	void applyForce(Vect3D);

	void update(float);

	void log();
};


#endif
