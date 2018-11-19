#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vect3.h"
#include "Quaternion.h"
#include "Matrix33.h"
#include "Matrix34.h"


class Rigidbody
{
private:
	float mass;
	float inverseMass;
	float linDamping;
	float angDamping;
	Vect3 position;
	Vect3 velocity;
	Vect3 accumForce;
	Quaternion orientation;
	Vect3 rotation;
	Vect3 accumTorque;
	Matrix34 transformMatrix;
	Matrix33 localInverseInertiaTensor;
	Matrix33 inverseInertiaTensor;

	void calcDerivedData();
	void clearAccum();

public:
	Rigidbody(float = 1, float = 1, float = 1);
	Rigidbody(const Rigidbody&);
	Rigidbody(const Rigidbody*);

	void init(Vect3&, Vect3&, Quaternion&, Vect3&);
	void boxInertialTensor(float, float, float, float);
	void sphereInertialTensor(float, float);

	void addForceAtPoint(Vect3&, Vect3&);
	void addForceAtBodyPoint(Vect3&, Vect3&);
	void update(float);
};

#endif