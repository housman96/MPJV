#include "Particle.h"

using namespace std;

// ============================================================
// CONSTRUCTEURS
// ============================================================

Particle::Particle(float m, float r) {
  position = new Vect3D(0, 0, 0);
  velocity = new Vect3D(0, 0, 0);
  acceleration = new Vect3D(0, 0, 0);
  mass = m;
  inverseMass = (m != 0. ? 1.0 / m : 1.);
  radius = r;
}

Particle::Particle(const Particle &other) {
  position = other.position;
  velocity = other.velocity;
  acceleration = other.acceleration;
  mass = other.mass;
  inverseMass = other.inverseMass;
  radius = other.radius;
}

Particle::Particle(const Particle *other) {
  position = other->position;
  velocity = other->velocity;
  acceleration = other->acceleration;
  mass = other->mass;
  inverseMass = other->inverseMass;
  radius = other->radius;
}

// ============================================================
// ASCESSEURS
// ============================================================

Vect3D Particle::getPosition() { return position; }

Vect3D Particle::getVelocity() { return velocity; }

Vect3D Particle::getAcceleration() { return acceleration; }

Vect3D Particle::getAccumForce() { return accumForce; }

float Particle::getMass() { return mass; }

float Particle::getInverseMass() { return inverseMass; }

float Particle::getRadius() { return radius; }

void Particle::setPosition(Vect3D pos) { this->position = pos; }

void Particle::setVelocity(Vect3D vel) { this->velocity = vel; }

void Particle::setAcceleration(Vect3D acc) { this->acceleration = acc; }

void Particle::setAccumForce(Vect3D accf) { this->accumForce = accf; }

void Particle::setMass(float m) { this->mass = m; }

void Particle::setInverseMass(float invm) { this->inverseMass = invm; }

void Particle::setRadius(float r) { this->radius = r; }

// ============================================================
// AFFICHAGE
// ============================================================

void Particle::log() {
  cout << "Particle : " << endl;
  cout << "\tPos => ";
  position.log();
  cout << "\tAccum => ";
  accumForce.log();
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

void Particle::applyForce(Vect3D &force) { accumForce = accumForce.add(force); }

void Particle::rebound() {
  float velY = velocity.getY();
  if (position.getY() - radius < 0 && velY < 0) {
    position.setY(radius * 2 - position.getY());
    velocity.setY(-velY);
  }
}

void Particle::update(float t) {
  acceleration = accumForce.scale(inverseMass);
  velocity = velocity.add(acceleration.scale(t));
  position = position.add(velocity.scale(t));
}

void Particle::clearAccum() { accumForce = accumForce.scale(0.); }
