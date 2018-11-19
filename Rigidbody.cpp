#include "Rigidbody.h"

using namespace std;


Rigidbody::Rigidbody(float m, float linD, float angD)
{
  t = Type::Rigibody;
	mass = m;
	inverseMass = (m != 0. ? 1. / m : 1.);
	linDamping = linD;
	angDamping = angD;
	position = new Vect3();
	velocity = new Vect3();
	accumForce = new Vect3();
	accumTorque = new Vect3();
	orientation = new Quaternion();
	rotation = new Vect3();
	transformMatrix = new Matrix34();
	inverseInertiaTensor = new Matrix33();
	localInverseInertiaTensor = new Matrix33();
}

Rigidbody::Rigidbody(const Rigidbody& other)
{
  t = Type::Rigibody;
	mass = other.mass;
	inverseMass = other.inverseMass;
	linDamping = other.linDamping;
	angDamping = other.angDamping;
	position = other.position;
	velocity = other.velocity;
	accumForce = other.accumForce;
	accumTorque = other.accumTorque;
	orientation = other.orientation;
	rotation = other.rotation;
	transformMatrix = other.transformMatrix;
	inverseInertiaTensor = other.inverseInertiaTensor;
	localInverseInertiaTensor = other.localInverseInertiaTensor;
}

Rigidbody::Rigidbody(const Rigidbody* other)
{
  t = Type::Rigibody;
	mass = other->mass;
	inverseMass = other->inverseMass;
	linDamping = other->linDamping;
	angDamping = other->angDamping;
	position = other->position;
	velocity = other->velocity;
	accumForce = other->accumForce;
	accumTorque = other->accumTorque;
	orientation = other->orientation;
	rotation = other->rotation;
	transformMatrix = other->transformMatrix;
	inverseInertiaTensor = other->inverseInertiaTensor;
	localInverseInertiaTensor = other->localInverseInertiaTensor;
}


void Rigidbody::init(Vect3& pos, Vect3& vel, Quaternion& orien, Vect3& rot)
{
	position = pos;
	velocity = vel;
	orientation = orien;
	rotation = rot;
}

void Rigidbody::boxInertialTensor(float m, float dx, float dy, float dz)
{
	localInverseInertiaTensor = Matrix33::BoxTensor(m, dx, dy, dz);
	localInverseInertiaTensor = inverseInertiaTensor.inverse();
	calcDerivedData();
}

void Rigidbody::sphereInertialTensor(float m, float r)
{
	localInverseInertiaTensor = Matrix33::SphereTensor(m, r);
	localInverseInertiaTensor = inverseInertiaTensor.inverse();
	calcDerivedData();
}


void Rigidbody::addForceAtPoint(Vect3& force, Vect3& point)
{
	Vect3 localPoint = point.sub(position);
	accumForce = accumForce.add(force);
	accumTorque = accumForce.add(localPoint.cross(force));
}

void Rigidbody::addForceAtBodyPoint(Vect3& force, Vect3& point)
{
	Vect3 worldPoint = position.add(point);
	addForceAtBodyPoint(force, worldPoint);
}

void Rigidbody::update(float t)
{
	// 1) Calcul de l'acceleration lineaire
	Vect3 linAcc = accumForce.scale(inverseMass);
	// 2) Calcul de l'acceleration angulaire 
	Vect3 angAcc = inverseInertiaTensor.mult(accumTorque);
	// 3) Maj velocity lineaire et prise en compte du damping
	velocity = velocity.scale(powf(linDamping, t));
	velocity = velocity.add(linAcc.scale(t));
	// 4) Maj velocity angulaire et prise en compte du damping
	rotation = rotation.scale(powf(angDamping, t));
	rotation = rotation.add(angAcc.scale(t));
	// 5) Maj position
	position = position.add(velocity.scale(t));
	// 6) Maj orientation
	orientation.updateAngularVelocity(rotation, t);
	// 7) Recalcul "transformMatrix" et "inverseInertiaTensor"
	calcDerivedData();
	// 8) Vider les accumulateurs
	clearAccum();
}

void Rigidbody::calcDerivedData()
{
	transformMatrix = Matrix34::setOrientation(orientation, position);
	inverseInertiaTensor = transformMatrix.getMat33(3,3).inverse();
	inverseInertiaTensor = inverseInertiaTensor.mult(localInverseInertiaTensor);
	inverseInertiaTensor = inverseInertiaTensor.mult(transformMatrix.getMat33(3, 3));
}

void Rigidbody::clearAccum()
{
	accumForce = accumForce.scale(0.);
	accumTorque = accumTorque.scale(0.);

float Rigidbody::getMass()
{
	return 0.0f;
}

