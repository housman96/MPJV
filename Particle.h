#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vect3D.h"
#include <iostream>
#include <cmath>


class Particle {
private:
	Vect3D position;
	Vect3D velocity;
	Vect3D acceleration;
	float inverseMass;
	float radius;
	float damping;

public:
	/* CONSTRUCTEURS */
	Particle(float = 1, float = 1, float = 1); /* Constructeur par defaut */
	Particle(const Particle &);                /* Constructeur de recopie */
	Particle(const Particle *);                /* Constructeur par pointeur */

	/* ASCESSEURS */
	Vect3D getPosition();
	Vect3D getVelocity();
	Vect3D getAcceleration();
	float getRadius();
	float getDamping();
	void setPosition(Vect3D);
	void setVelocity(Vect3D);
	void setAcceleration(Vect3D);
	void setRadius(float);
	void setDamping(float);

	/* AFFICHAGE */
	void log(); /* Affichage dans la console */

	/* INITIALISATION */
	void init(Vect3D, Vect3D, Vect3D); /* Fixe les valeurs initiales pour la position, la vitesse et l'accélération */

	/* MISE A JOUR */
	void applyForce(Vect3D); /* Deuxieme Loi de Newtom */
	void rebound();          /* Fait rebondir la particule quand elle touche le sol */
	void update(float);      /* Intègre la position et la vitesse */
};


#endif
