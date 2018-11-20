#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vect3.h"
#include "GameObject.h"
#include <cmath>
#include <iostream>


class Particle : public GameObject
{
private:
	Vect3 position;
	Vect3 velocity;
	Vect3 acceleration;
	Vect3 accumForce;
	float mass;
	float inverseMass;
	float radius;

public:
	/* CONSTRUCTEURS */
	Particle(float = 1, float = 1); /* Constructeur par defaut */
	Particle(const Particle &);     /* Constructeur de recopie */
	Particle(const Particle *);     /* Constructeur par pointeur */
	Particle(GameObject* g);

	/* ASCESSEURS */
	Vect3 getPosition();
	Vect3 getVelocity();
	Vect3 getAcceleration();
	Vect3 getAccumForce();
	float getRadius();
	float getInverseMass();
	float getMass();
	void setPosition(Vect3);
	void setVelocity(Vect3);
	void setAcceleration(Vect3);
	void setAccumForce(Vect3);
	void setRadius(float);
	void setInverseMass(float);
	void setMass(float);


	/* AFFICHAGE */
	void log(); /* Affichage dans la console */

	/* INITIALISATION */
	void init(Vect3, Vect3, Vect3); /* Fixe les valeurs initiales pour la position, la vitesse et l'acceleration */

	/* MISE A JOUR */
	void applyForce(Vect3 &); /* Deuxieme Loi de Newtom */
	void rebound();            /* Fait rebondir la particule quand elle touche le sol */
	void update(float);        /* Integre la position et la vitesse */
	void clearAccum();         /* Vide accumForce */
	void draw();
};

#endif
