
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vect3.h"
#include "GameObject.h"
#include "Quaternion.h"
#include "Matrix33.h"
#include "Matrix34.h"


class Rigidbody : public GameObject
{
private:
	float linDamping;
	float angDamping;
	Quaternion orientation;
	Vect3 rotation;
	Vect3 accumTorque;
	Matrix33 localInverseInertiaTensor;
	Matrix33 inverseInertiaTensor;

	void calcDerivedData();
	void clearAccum();

public:
	Matrix34 transformMatrix;
	bool operator==(GameObject* a) {
		if (a->t == Type::Rigibody) {
			return this == &(*a);
		}
		else {
			return false;
		}

	}

	Rigidbody(float = 1, float = 1, float = 1);
	Rigidbody(const Rigidbody&);
	Rigidbody(const Rigidbody*);

	float getMass();

	void init(Vect3&, Vect3&, Quaternion&, Vect3&);
	void boxInertialTensor(float, float, float, float);
	void sphereInertialTensor(float, float);

	void addForceAtPoint(Vect3&, Vect3&);
	void addForceAtBodyPoint(Vect3&, Vect3&);
	void update(float);
	void draw();
};

#endif
