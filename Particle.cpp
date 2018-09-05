#include "Particle.h"

using namespace std;


// ============================================================
// CONSTRUCTEURS
// ============================================================

Particle::Particle(Vect3D pos, Vect3D vel, float m) {
	position = pos.copy();
	velocity = vel.copy();
	acceleration = new Vect3D(0, 0, 0);
	inverseMass = 1.0 / m;
}

Particle::Particle(const Particle &other) {
	position = other.position.copy();
	velocity = other.velocity.copy();
	acceleration = other.acceleration.copy();
	inverseMass = other.inverseMass;
}


float Particle::inverseMass() {
	return inverseMass;
}
