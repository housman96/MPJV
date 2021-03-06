#include "Rigidbody.h"

using namespace std;


Rigidbody::Rigidbody(float m, float linD, float angD)
{
	t = Type::Rigibody;
	mass = m;
	inverseMass = (m != 0. ? 1. / m : 1.);
	linDamping = linD;
	angDamping = angD;
	position = Vect3();
	velocity = Vect3();
	accumForce = Vect3();
	accumTorque = Vect3();
	orientation = Quaternion();
	rotation = Vect3();
	transformMatrix = Matrix34();
	inverseInertiaTensor = Matrix33();
	localInverseInertiaTensor = Matrix33();
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
	localInverseInertiaTensor = Matrix33::BoxTensor(m, dx, dy, dz).inverse();
	calcDerivedData();
}

void Rigidbody::sphereInertialTensor(float m, float r)
{
	localInverseInertiaTensor = Matrix33::SphereTensor(m, r).inverse();
	calcDerivedData();
}


void Rigidbody::addForceAtPoint(Vect3& force, Vect3& point)
{
	Vect3 localPoint = point.sub(position);
	accumForce = accumForce.add(force);
	accumTorque = accumTorque.add(localPoint.cross(force));
}

void Rigidbody::addForceAtBodyPoint(Vect3& force, Vect3& point)
{
	Vect3 worldPoint = position.add(point);
	addForceAtPoint(force, worldPoint);
}

void Rigidbody::update(float t)
{
	// 1) Calcul de l'acceleration lineaire
	Vect3 linAcc = accumForce.scale(inverseMass);
	// 2) Calcul de l'acceleration angulaire 
	Vect3 angAcc = inverseInertiaTensor.mult(accumTorque);
	// 3) Maj velocite lineaire et prise en compte du damping
	velocity = velocity.scale(powf(linDamping, t));
	velocity = velocity.add(linAcc.scale(t));
	// 4) Maj velocite angulaire et prise en compte du damping
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
	inverseInertiaTensor = transformMatrix.getMat33(3, 3).inverse();
	inverseInertiaTensor = inverseInertiaTensor.mult(localInverseInertiaTensor);
	inverseInertiaTensor = inverseInertiaTensor.mult(transformMatrix.getMat33(3, 3));
}

void Rigidbody::clearAccum()
{
	accumForce = accumForce.scale(0.);
	accumTorque = accumTorque.scale(0.);
}

float Rigidbody::getMass()
{
	return mass;
}

void Rigidbody::draw()
{
	float dx = 1.0f;
	float dy = 1.0f;
	float dz = 1.0f;

	glPushMatrix();

	GLfloat * matRot = Matrix34::setOrientation(orientation, position).toGlutMat();
	glMultMatrixf(matRot);

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	// Top face (y = 1.0f)
	// Define vertices in counter-clockwise (CCW) order with normal pointing out
	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(dx, dy, -dz);
	glVertex3f(-dx, dy, -dz);
	glVertex3f(-dx, dy, dz);
	glVertex3f(dx, dy, dz);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(dx, -dy, dz);
	glVertex3f(-dx, -dy, dz);
	glVertex3f(-dx, -dy, -dz);
	glVertex3f(dx, -dy, -dz);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(dx, dy, dz);
	glVertex3f(-dx, dy, dz);
	glVertex3f(-dx, -dy, dz);
	glVertex3f(dx, -dy, dz);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(dx, -dy, -dz);
	glVertex3f(-dx, -dy, -dz);
	glVertex3f(-dx, dy, -dz);
	glVertex3f(dx, dy, -dz);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-dx, dy, dz);
	glVertex3f(-dx, dy, -dz);
	glVertex3f(-dx, -dy, -dz);
	glVertex3f(-dx, -dy, dz);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(dx, dy, -dz);
	glVertex3f(dx, dy, dz);
	glVertex3f(dx, -dy, dz);
	glVertex3f(dx, -dy, -dz);
	glEnd();  // End of drawing color-cube

	glPopMatrix();

	delete matRot;
}