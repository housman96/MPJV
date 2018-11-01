#include "ParticleCable.h"
#include "GameLoop.h"

// ============================================================
// CONSTRUCTEURS ET DESTRUCTEURS
// ============================================================

ParticleCable::ParticleCable(Particle *p1, Particle *p2, float maxLenght, float restitution) : ParticleLink(p1, p2)
{
	this->maxLenght = maxLenght;
	this->restitution = restitution;
}


ParticleCable::~ParticleCable()
{
}


// ============================================================
// AJOUT DE CONTACTS
// ============================================================

void ParticleCable::addContact() {
	if (maxLenght < currentLenght()) {

		Vect3 p1_pos = particles[0]->getPosition();
		Vect3 p2_pos = particles[1]->getPosition();

		//on créer les des contacts avec une seul particule et avec des vecteur n vers le centre du cable

		GameLoop::listContact.push_back(new ParticleContact(particles[0], restitution, p2_pos.sub(p1_pos).normalize(), (currentLenght() - maxLenght) / 2));
		GameLoop::listContact.push_back(new ParticleContact(particles[1], restitution, p1_pos.sub(p2_pos).normalize(), (currentLenght() - maxLenght) / 2));

	}

}
