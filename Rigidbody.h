#pragma once

#include "Vect3.h"
#include "GameObject.h"

class Rigidbody : public GameObject
{
public:
	Rigidbody();
	~Rigidbody();
	float getMass();
	void applyForce(Vect3);
	void update(float);
};

