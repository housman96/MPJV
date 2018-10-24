#include "ParticleCable.h"
#include "Affichage.h"

ParticleCable::ParticleCable(Particle *p1, Particle *p2, float maxLenght, float restitution) : ParticleLink(p1, p2)
{
	this->maxLenght = maxLenght;
	this->restitution = restitution;
}


ParticleCable::~ParticleCable()
{
}

void ParticleCable::addContact() {
	if (maxLenght < currentLenght()) {

		Vect3D p1_pos = particles[0]->getPosition();
		Vect3D p2_pos = particles[1]->getPosition();
		Affichage::listContact.push_back(new ParticleContact(particles[0], restitution, p2_pos.sub(p1_pos).normalize(), (currentLenght() - maxLenght) / 2));
		Affichage::listContact.push_back(new ParticleContact(particles[1], restitution, p1_pos.sub(p2_pos).normalize(), (currentLenght() - maxLenght) / 2));
	}

}
