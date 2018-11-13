#ifndef VECT3_H
#define VECT3_H

#include <iostream>
#include <cmath>


class Vect3
{
private:
	float x; /* Composante X */
	float y; /* Composante Y */
	float z; /* Composante Z */

public:
	/* CONSTRUCTEURS */
	Vect3(float = 0, float = 0, float = 0); /* Constructeur par défaut */
	Vect3(const Vect3 &);					 /* Constructeur de recopie */
	Vect3(const Vect3 *);					 /* Constructeur par pointeur */

	/* ASCESSEURS */
	float getX();
	float getY();
	float getZ();
	void setX(float);
	void setY(float);
	void setZ(float);

	/* AFFICHAGE */
	void log(); /* Affichage dans la console */

	/* OPERATIONS */
	Vect3 add(const Vect3 &);   /* Addition de deux vecteurs */
	Vect3 sub(const Vect3 &);   /* Soustraction de deux vecteurs */
	Vect3 scale(const float);	  /* Multiplication par un scalaire */
	Vect3 mult(const Vect3 &);  /* Multiplication des composantes */
	float dot(const Vect3 &);	  /* Produit scalaire */
	Vect3 cross(const Vect3 &); /* Produit vectoriel */

	/* MANIPULATION DE LA NORME */
	float mag();		/* Norme du vecteur */
	float magSq();		/* Norme du vecteur au carré */
	Vect3 normalize(); /* Rend le vecteur unitaire */

	/* METHODES STATIQUES */
	static Vect3 proj(Vect3 &, Vect3 &);		   /* Projection d'un vecteur sur un autre */
	static float dist(Vect3 &, Vect3 &);		   /* Distance entre deux points */
	static float angleBetween(Vect3 &, Vect3 &); /* Angle entre deux vecteurs */
};

#endif
