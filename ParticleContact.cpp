#include "ParticleContact.h"

// ============================================================
// CONSTRUCTEURS
// ============================================================

ParticleContact::ParticleContact(Particle *p1, Particle *p2, float c_) {
	particles[0] = p1;
	particles[1] = p2;
	c = c_;

	Vect3 p1_pos = p1->getPosition();
	Vect3 p2_pos = p2->getPosition();
	n = p1_pos.sub(p2_pos).normalize();

	d = (p1->getRadius() + p2->getRadius()) - (Vect3::dist(p1_pos, p2_pos)); //d = r1+r2 - dist pa pb
	Vs = calcVs();
}



ParticleContact::ParticleContact(Particle *p1, float c_, Vect3 n, float d) {
	particles[0] = p1;
	particles[1] = NULL;
	c = c_;

	Vect3 p1_pos = p1->getPosition();

	this->n = n;

	this->d = d;
	this->Vs = calcVs();
}

// ============================================================
// RESOLUTION DES CONTACTS
// ============================================================

void ParticleContact::resolve() {
	//si le VS<0 on r�soud le contact
	if (calcVs() < 0) {
		resolveInterpenetration();
		resolveVelocity();
	}
}

float ParticleContact::calcVs() {
	float res;
	Vect3 p1_vel = particles[0]->getVelocity();
	if (particles[1] != NULL) {
		Vect3 p2_vel = particles[1]->getVelocity();
		res = p1_vel.sub(p2_vel).dot(n);	//Vs=(p1-p2).n
	}
	else {
		res = p1_vel.dot(n);	//on a pas p2 donc on ne prend que p1 (� v�rifier)
	}
	return res;
}



void ParticleContact::resolveVelocity() {

	if (particles[1] != NULL) {
		//set des nouvelles velocites
		float m0 = particles[0]->getMass();
		float m1 = particles[1]->getMass();
		particles[0]->setVelocity(particles[0]->getVelocity().add(n.scale(m0*Vs*(-1 - c) / (m0 + m1))));	//V' =  V+Vs'*m0/(m0+m1) =  V+Vs(-1-c)*m0/(m0+m1)

		particles[1]->setVelocity(particles[1]->getVelocity().add(n.scale(m1*Vs*(1 + c) / (m0 + m1))));
	}
	else {
		//on prend la valeur absolu de Vs pour �tre s�r que l'impulsion soit selon n 
		if (Vs < 0) {
			Vs = -Vs;
		}
		particles[0]->setVelocity(particles[0]->getVelocity().add(n.scale(Vs*(1 + c))));	//on ne prend pas en compre la masse car on a pas acc�s � p2 (� v�rifier)
	}
}



void ParticleContact::resolveInterpenetration() {
	if (particles[1] != NULL) {
		Vect3 pos0 = n.scale(d * particles[1]->getMass() / (particles[1]->getMass() + particles[0]->getMass()));
		Vect3 pos1 = n.scale(-d * particles[0]->getMass() / (particles[1]->getMass() + particles[0]->getMass()));

		particles[0]->setPosition(particles[0]->getPosition().add(pos0));
		particles[1]->setPosition(particles[1]->getPosition().add(pos1));
	}
	else {
		particles[0]->setPosition(particles[0]->getPosition().add(n.scale(d)));	//on ne prend pas en compre la masse car on a pas acc�s � p2 (� v�rifier)
	}

}
