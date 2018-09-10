#include "Particle.h"

using namespace std;


// ============================================================
// CONSTRUCTEURS
// ============================================================

Particle::Particle(Vect3D pos, Vect3D vel, float m) {
	position = pos;
	velocity = vel;
	acceleration = new Vect3D(0, 0, 0);
	inverseMass = 1.0 / m;
}

Particle::Particle(const Particle &other) {
	position = other.position;
	velocity = other.velocity;
	acceleration = other.acceleration;
	inverseMass = other.inverseMass;
}

Particle::Particle(const Particle * other) {
	position = other->position;
	velocity = other->velocity;
	acceleration = other->acceleration;
	inverseMass = other->inverseMass;
}


// ============================================================
// ASCESSEURS
// ============================================================

Vect3D Particle::getPosition() {
	return position;
}

void Particle::setPosition(Vect3D position) {
	this->position = position;
}


// ============================================================
// METHODES DE MISE A JOUR
// ============================================================

void Particle::applyForce(Vect3D force) {
	Vect3D f = force;
	f.scale(inverseMass);
	acceleration = acceleration.add(f);
}


void Particle::update(float t) {
	velocity = velocity.add(acceleration.scale(t));
	position = position.add(velocity.scale(t));
}
