#ifndef VECT3D_H
#define VECT3D_H

#include <iostream>
#include <cmath>


class Vect3D {
private:
	float x;
	float y;
	float z;

public:
	Vect3D(float = 0, float = 0, float = 0); /* Constructeur par défaut */
	Vect3D(const Vect3D &);                  /* Constructeur de recopie */

	Vect3D add(const Vect3D &);
	Vect3D scale(const float);
	Vect3D mult(const Vect3D &);
	float dot(const Vect3D &);
	float mag();
	float magSq();
	Vect3D normalize();
	static Vect3D proj(Vect3D &, Vect3D &);
	static float dist(Vect3D &, Vect3D &);
	static float angleBetween(Vect3D &, Vect3D &);
	Vect3D cross(const Vect3D &);

	void log();
};


#endif
