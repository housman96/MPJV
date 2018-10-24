#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle *p1, Particle *p2, float c_)
{
	particles[0] = p1;
	particles[1] = p2;
	c = c_;

	Vect3D p1_pos = p1->getPosition();
	Vect3D p2_pos = p2->getPosition();
	n = p1_pos.sub(p2_pos).normalize();

	d = (p1->getRadius() + p2->getRadius()) - (Vect3D::dist(p1_pos, p2_pos)); //d = 2*r - dist pa pb
	Vs = calcVs();
}



ParticleContact::ParticleContact(Particle *p1, float c_, Vect3D n, float d)
{
	particles[0] = p1;
	particles[1] = NULL;
	c = c_;

	Vect3D p1_pos = p1->getPosition();

	this->n = n;

	this->d = d; //d = 2*r - dist pa pb
	this->Vs = calcVs();
}

void ParticleContact::resolve()
{
	printf("hello");
	resolveInterpenetration();
	if (calcVs() < 0) {

		resolveVelocity();
	}
}

float ParticleContact::calcVs()
{
	float res;

	Vect3D p1_vel = particles[0]->getVelocity();
	if (particles[1] != NULL) {
		Vect3D p2_vel = particles[1]->getVelocity();
		res = p1_vel.sub(p2_vel).dot(n);
	} else {
		res = p1_vel.dot(n);
	}
	return res;
}



void ParticleContact::resolveVelocity()
{

	if (particles[1] != NULL) {
		float m0 = particles[0]->getMass();
		float m1 = particles[1]->getMass();
		particles[0]->setVelocity(particles[0]->getVelocity().add(n.scale(m0*Vs*(-1 - c) / (m0 + m1))));
		particles[1]->setVelocity(particles[1]->getVelocity().add(n.scale(m1*Vs*(1 + c) / (m0 + m1))));
	} else {
		if (Vs < 0) {
			Vs = -Vs;
		}
		particles[0]->setVelocity(particles[0]->getVelocity().add(n.scale(Vs*(1 + c))));
		std::cout << "test" << std::endl;
	}
}



void ParticleContact::resolveInterpenetration()
{
	if (particles[1] != NULL) {
		Vect3D pos0 = n.scale(d * particles[1]->getMass() / (particles[1]->getMass() + particles[0]->getMass()));
		Vect3D pos1 = n.scale(-d * particles[0]->getMass() / (particles[1]->getMass() + particles[0]->getMass()));

		particles[0]->setPosition(particles[0]->getPosition().add(pos0));
		particles[1]->setPosition(particles[1]->getPosition().add(pos1));
	} else {
		particles[0]->setPosition(particles[0]->getPosition().add(n.scale(d)));
	}

}
