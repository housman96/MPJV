#include "Particle.h"

using namespace std;

// ============================================================
// CONSTRUCTEURS
// ============================================================

Particle::Particle(Vect3D pos, Vect3D vel, float m)
{
	position = pos;
	velocity = vel;
	acceleration = new Vect3D(0, 0, 0);
	inverseMass = 1.0 / m;
	damping = 1.0;
}

Particle::Particle(const Particle &other)
{
	position = other.position;
	velocity = other.velocity;
	acceleration = other.acceleration;
	inverseMass = other.inverseMass;
	damping = other.damping;
}

Particle::Particle(const Particle *other)
{
	position = other->position;
	velocity = other->velocity;
	acceleration = other->acceleration;
	inverseMass = other->inverseMass;
	damping = other->damping;
}

// ============================================================
// ASCESSEURS
// ============================================================

void Particle::setDamping(float d) {
	this->damping = d;
}

Vect3D Particle::getPosition() {
	return position;
}

void Particle::setPosition(Vect3D position) {
	this->position = position;
}


// ============================================================
// AFFICHAGE
// ============================================================

void Particle::log() {
	cout << "Particle : " << endl;
	cout << "\tPos => ";
	position.log();
	cout << endl;
}


// ============================================================
// METHODES DE MISE A JOUR
// ============================================================

void Particle::applyForce(Vect3D force) {
	Vect3D f = force.scale(inverseMass);
	acceleration = acceleration.add(f);
}

void Particle::update(float t) {
	velocity = velocity.scale(pow(damping, t));
	velocity = velocity.add(acceleration.scale(t));
	position = position.add(velocity.scale(t));
	acceleration = acceleration.scale(0);
}

// ============================================================
// ASCESSEUR
// ============================================================

Vect3D Particle::getPosition(void)
{
	return position;
}

void Particle::setPosition(Vect3D position)
{
	this->position = position;
}