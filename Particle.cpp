#include "Particle.h"

using namespace std;


// ============================================================
// CONSTRUCTEURS
// ============================================================

Particle::Particle(float m, float r)
{
	t = Type::Particle;
	position = new Vect3(0, 0, 0);
	velocity = new Vect3(0, 0, 0);
	acceleration = new Vect3(0, 0, 0);
	mass = m;
	inverseMass = (m != 0. ? 1.0 / m : 1.);
	radius = r;
}

Particle::Particle(const Particle& other)
{
	t = Type::Particle;
	position = other.position;
	velocity = other.velocity;
	acceleration = other.acceleration;
	mass = other.mass;
	inverseMass = other.inverseMass;
	radius = other.radius;
}

Particle::Particle(const Particle* other)
{
	t = Type::Particle;
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

Vect3 Particle::getPosition()
{
	return position;
}

Vect3 Particle::getVelocity()
{
	return velocity;
}

Vect3 Particle::getAcceleration()
{
	return acceleration;
}

Vect3 Particle::getAccumForce()
{
	return accumForce;
}

float Particle::getMass()
{
	return mass;
}

float Particle::getInverseMass()
{
	return inverseMass;
}

float Particle::getRadius()
{
	return radius;
}

void Particle::setPosition(Vect3 pos)
{
	this->position = pos;
}

void Particle::setVelocity(Vect3 vel)
{
	this->velocity = vel;
}

void Particle::setAcceleration(Vect3 acc)
{
	this->acceleration = acc;
}

void Particle::setAccumForce(Vect3 accf)
{
	this->accumForce = accf;
}

void Particle::setMass(float m)
{
	this->mass = m;
}

void Particle::setInverseMass(float invm)
{
	this->inverseMass = invm;
}

void Particle::setRadius(float r)
{
	this->radius = r;
}


// ============================================================
// AFFICHAGE
// ============================================================

void Particle::log()
{
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

void Particle::init(Vect3 pos, Vect3 vel, Vect3 acc)
{
	this->setPosition(pos);
	this->setVelocity(vel);
	this->setAcceleration(acc);
}


// ============================================================
// MISE A JOUR
// ============================================================

void Particle::applyForce(Vect3& force)
{
	accumForce = accumForce.add(force);
}

void Particle::rebound()
{
	float velY = velocity.getY();
	if (position.getY() - radius < 0 && velY < 0) {
		position.setY(radius * 2 - position.getY());
		velocity.setY(-velY);
	}
}

void Particle::update(float t)
{
	rebound();
	acceleration = accumForce.scale(inverseMass);
	velocity = velocity.add(acceleration.scale(t));
	position = position.add(velocity.scale(t));
	clearAccum();
}

void Particle::clearAccum()
{
	accumForce = accumForce.scale(0.);
}

void Particle::draw()
{
	glPushMatrix();
	glColor3b(0, 0, 50);
	glTranslatef(part.getPosition().getX(), part.getPosition().getY(), part.getPosition().getZ());
	glutSolidSphere(part.getRadius(), 50, 50);
	glPopMatrix();
}
