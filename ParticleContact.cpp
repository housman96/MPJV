#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle &p1, Particle &p2, float c_) {
	particles[0] = &p1;
	particles[1] = &p2;
	c = c_;

	Vect3D p1_pos = p1.getPosition();
	Vect3D p2_pos = p2.getPosition();
	n = p1_pos.sub(p2_pos).normalize();

	d = (p1.getRadius() + p2.getRadius()) - (Vect3D::dist(p1_pos, p2_pos)); //d = 2*r - dist pa pb
}

void ParticleContact::resolve(float duree) {
	if (calcVs() < 0) {
		resolveInterpenetration();
		resolveVelocity();
	}
}

float ParticleContact::calcVs() {
	Vect3D p1_pos = particles[0]->getPosition();
	Vect3D p2_pos = particles[1]->getPosition();
	return p1_pos.sub(p2_pos).dot(n);
}

void ParticleContact::resolveVelocity() {
	Vect3D g0 = particles[1]->getVelocity().mult(particles[1]->getMass());
	Vect3D g1 = particles[0]->getVelocity().mult(particles[0]->getMass());
	Vect3D vel0 = particles[0]->getVelocity().add(g0.mult(particles[0]->getInverseMass()));
	Vect3D vel1 = particles[1]->getVelocity().add(g1.mult(particles[1]->getInverseMass()));
	particles[0]->setVelocity(vel0);
	particles[1]->setVelocity(vel1);
}



void ParticleContact::resolveInterpenetration() {
	Vect3D pos0 = n.mult(d * particles[1]->getMass() / (particles[1]->getMass()*particles[0]->getMass()));
	Vect3D pos1 = n.mult(-d * particles[0]->getMass() / (particles[1]->getMass()*particles[0]->getMass()));

	particles[0]->setPosition(particles[0]->getPosition + pos0);
	particles[1]->setPosition(particles[1]->getPosition + pos1);
}
