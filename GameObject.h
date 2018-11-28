#pragma once

enum class Type { Particle, Rigibody };
#include <GL/glut.h>

class GameObject
{
public:
	Type t;
	virtual void update(float) = 0;        /* Integre la position et la vitesse */
	virtual void draw() = 0;			   /* Draw le GameObject */
};

