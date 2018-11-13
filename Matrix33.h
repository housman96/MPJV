#ifndef MATRIX33_H
#define MATRIX33_H

#include "Vect3.h"

class Matrix33
{



public:

	/*DONNEES*/
	float* tab;

	/* CONSTRUCTEURS */
	Matrix33();
	Matrix33(const Matrix33 &);
	Matrix33(const Matrix33*);
	Matrix33(float*);
	/* DESTRUCTEURS */
	~Matrix33();

	/* OPERATIONS */
	float& operator[](const int);
	Matrix33& operator=(const Matrix33&);
	friend std::ostream& operator<<(std::ostream &strm, const Matrix33& mat);
	float getElement(int i, int j) const;
	Vect3 mult(Vect3 &);  /* Multiplication des composantes */
	Matrix33 mult(Matrix33 &);  /* Multiplication des composantes */
};



#endif