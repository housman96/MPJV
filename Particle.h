#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vect3D.h"
#include <cmath>
#include <iostream>


class Particle
{
private:
	Vect3D position;
	Vect3D velocity;
	Vect3D acceleration;
	Vect3D accumForce;
	float mass;
	float inverseMass;
	float radius;

public:
  /* CONSTRUCTEURS */
	Particle(float = 1, float = 1); /* Constructeur par defaut */
	Particle(const Particle &);     /* Constructeur de recopie */
	Particle(const Particle *);     /* Constructeur par pointeur */

	/* ASCESSEURS */
	Vect3D getPosition();
	Vect3D getVelocity();
	Vect3D getAcceleration();
	Vect3D getAccumForce();
	float getRadius();
	float getInverseMass();
	float getMass();
	void setPosition(Vect3D);
	void setVelocity(Vect3D);
	void setAcceleration(Vect3D);
	void setAccumForce(Vect3D);
	void setRadius(float);
	void setInverseMass(float);
	void setMass(float);

	/* AFFICHAGE */
	void log(); /* Affichage dans la console */

	/* INITIALISATION */
	void init(Vect3D, Vect3D, Vect3D); /* Fixe les valeurs initiales pour la position, la vitesse et l'acceleration */

	/* MISE A JOUR */
	void applyForce(Vect3D &); /* Deuxieme Loi de Newtom */
	void rebound();            /* Fait rebondir la particule quand elle touche le sol */
	void update(float);        /* Integre la position et la vitesse */
	void clearAccum();         /* Vide accumForce */
};

#endif
