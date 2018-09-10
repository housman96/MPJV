#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vect3D.h"

class Particle
{
private:
	Vect3D position;
	Vect3D velocity;
	Vect3D acceleration;
	float inverseMass;

public:
	Particle(Vect3D, Vect3D, float); /* Constructeur par defaut */
	Particle(const Particle &);			 /* Constructeur de recopie */
	Particle(const Particle *);			 /* Constructeur par pointeur */

	void applyForce(Vect3D);
	void applyGrav(Vect3D);

	void update(float);

	/*ASCESSEUR*/

	Vect3D getPosition(void);
	void setPosition(Vect3D position);
};

#endif
