#include "Particle.h"

using namespace std;


// ============================================================
// CONSTRUCTEURS
// ============================================================

Particle::Particle(float m, float r, float d) {
	position = new Vect3D(0, 0, 0);
	velocity = new Vect3D(0, 0, 0);
	acceleration = new Vect3D(0, 0, 0);
	inverseMass = 1.0 / m;
	radius = r;
	damping = d;
}

Particle::Particle(const Particle &other) {
	position = other.position;
	velocity = other.velocity;
	acceleration = other.acceleration;
	inverseMass = other.inverseMass;
	radius = other.radius;
	damping = other.damping;
}

Particle::Particle(const Particle * other) {
	position = other->position;
	velocity = other->velocity;
	acceleration = other->acceleration;
	inverseMass = other->inverseMass;
	radius = other->radius;
	damping = other->damping;
}

// ============================================================
// ASCESSEURS
// ============================================================

Vect3D Particle::getPosition() {
	return position;
}

Vect3D Particle::getVelocity() {
	return velocity;
}

Vect3D Particle::getAcceleration() {
	return acceleration;
}

float Particle::getRadius() {
	return radius;
}

float Particle::getDamping() {
	return damping;
}

void Particle::setPosition(Vect3D pos) {
	this->position = pos;
}

void Particle::setVelocity(Vect3D vel) {
	this->velocity = vel;
}

void Particle::setAcceleration(Vect3D acc) {
	this->acceleration = acc;
}

void Particle::setRadius(float r) {
	this->radius = r;
}

void Particle::setDamping(float d) {
	this->damping = d;
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
// INITIALISATION
// ============================================================

void Particle::init(Vect3D pos, Vect3D vel, Vect3D acc) {
	this->setPosition(pos);
	this->setVelocity(vel);
	this->setAcceleration(acc);
}


// ============================================================
// MISE A JOUR
// ============================================================

void Particle::applyForce(Vect3D force) {
	Vect3D f = force.scale(inverseMass);
	acceleration = acceleration.add(f);
}

void Particle::rebound() {
	float velY = velocity.getY();
	if (position.getY() - radius < 0 && velY < 0) {
		velocity.setY(-velY);
	}
}

void Particle::update(float t) {
	velocity = velocity.scale(pow(damping, t));
	velocity = velocity.add(acceleration.scale(t));
	position = position.add(velocity.scale(t));
	acceleration = acceleration.scale(0);
}
