#include "Rigidbody.h"



Rigidbody::Rigidbody()
{
	t = Type::Rigibody;
}


Rigidbody::~Rigidbody()
{
}

float Rigidbody::getMass()
{
	return 0.0f;
}

void Rigidbody::applyForce(Vect3)
{
}

void Rigidbody::update(float)
{
}