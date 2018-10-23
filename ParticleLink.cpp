#include "ParticleLink.h"



ParticleLink::ParticleLink(Particle &p1, Particle &p2)
{
	particles[0] = &p1;
	particles[1] = &p2;
}


ParticleLink::~ParticleLink()
{
	delete[] & particles;
}

float ParticleLink::currentLenght() const {
	return Vect3D::dist(particles[0]->getPosition(), particles[1]->getPosition());
}