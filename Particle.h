#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vect3D.h"


class Particle {
private:
	Vect3D position;
	Vect3D velocity;
	Vect3D acceleration;
	float inverseMass;


public:
	Particle(Vect3D, float);
	Particle(const Particle &);

	void update();
};


#endif
