#include "ParticleRod.h"


// ============================================================
// CONSTRUCTEURS ET DESTRUCTEURS
// ============================================================

ParticleRod::ParticleRod(Particle *p1, Particle *p2, float lenght) : ParticleLink(p1, p2)
{
	this->lenght = lenght;
}


ParticleRod::~ParticleRod()
{
}

// ============================================================
// AJOUT DES CONTACTS
// ============================================================

void ParticleRod::addContact() {
	Vect3D p1_pos = particles[0]->getPosition();
	Vect3D p2_pos = particles[1]->getPosition();

	//on créer les des contacts avec une seul particule et avec des vecteur n dépendant de currentLenght()

	if (lenght < currentLenght()) {

		GameLoop::listContact.push_back(new ParticleContact(particles[0], 0, p2_pos.sub(p1_pos).normalize(), (currentLenght() - lenght) / 2));
		GameLoop::listContact.push_back(new ParticleContact(particles[1], 0, p1_pos.sub(p2_pos).normalize(), (currentLenght() - lenght) / 2));
	}

	else {
		if (lenght > currentLenght()) {
			GameLoop::listContact.push_back(new ParticleContact(particles[0], 0, p1_pos.sub(p2_pos).normalize(), -(currentLenght() - lenght) / 2));
			GameLoop::listContact.push_back(new ParticleContact(particles[1], 0, p2_pos.sub(p1_pos).normalize(), -(currentLenght() - lenght) / 2));
		}
	}
}
