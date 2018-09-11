#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>
#include "Vect3D.h"

class Particle
{
private:
	Vect3D position;
	Vect3D velocity;
	Vect3D acceleration;
	float inverseMass;
	float damping;

public:
	Particle(Vect3D, Vect3D, float); /* Constructeur par defaut */
	Particle(const Particle &);      /* Constructeur de recopie */
	Particle(const Particle *);      /* Constructeur par pointeur */

	void setDamping(float);
	Vect3D getPosition(void);
	void setPosition(Vect3D);

	void log(); /* Affichage dans la console */

	void applyForce(Vect3D); /* Deuxieme Loi de Newtom */
	void update(float);      /* Intègre la position et la vitesse */
};


#endif
