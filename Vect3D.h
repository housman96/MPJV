#ifndef VECT3D_H
#define VECT3D_H

#include <iostream>
#include <cmath>

/**
 * Une classe de vecteurs 3D
 */
class Vect3D
{
  private:
	float x;
	float y;
	float z;

  public:
	Vect3D(float = 0, float = 0, float = 0); /* Constructeur par défaut */
	Vect3D(const Vect3D &);					 /* Constructeur de recopie */
	Vect3D(const Vect3D *);					 /* Constructeur par pointeur */

	Vect3D add(const Vect3D &);   /* Addition de deux vecteurs */
	Vect3D scale(const float);	/* Multiplication par un scalaire */
	Vect3D mult(const Vect3D &);  /* Multiplication des composantes */
	float dot(const Vect3D &);	/* Produit scalaire */
	Vect3D cross(const Vect3D &); /* Produit vectoriel */

	float mag();		/* Norme du vecteur */
	float magSq();		/* Norme du vecteur au carré */
	Vect3D normalize(); /* Rend le vecteur unitaire */

	static Vect3D proj(Vect3D &, Vect3D &);		   /* Projection d'un vecteur sur un autre */
	static float dist(Vect3D &, Vect3D &);		   /* Distance entre deux points */
	static float angleBetween(Vect3D &, Vect3D &); /* Angle entre deux vecteurs */

	void log(); /* Affichage dans la console */

	float getX();
	float getY();
	float getZ();

	void setX(float x);
	void setY(float y);
	void setZ(float z);
};

#endif
