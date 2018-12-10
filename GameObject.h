#pragma once

enum class Type { Particle, Rigibody };
#include <GL/glut.h>

class GameObject
{

public:
	Vect3 position;
	Vect3 velocity;
	float mass;
	float inverseMass;
	Type t;
	Vect3 accumForce;

	virtual bool operator==(GameObject*) = 0;
	virtual void update(float) = 0;        /* Integre la position et la vitesse */
	virtual void draw() = 0;			   /* Draw le GameObject */
};

