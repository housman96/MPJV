#ifndef MATRIX33_H
#define MATRIX33_H

#include "Vect3.h"
#include <vector>
class Matrix33
{

private:
	float Det22(int, int)const;

public:

	/*DONNEES*/
	float* tab;

	/* CONSTRUCTEURS */
	Matrix33();
	Matrix33(const Matrix33 &);
	Matrix33(const Matrix33*);
	Matrix33(const float*);
	/* DESTRUCTEURS */
	~Matrix33();

	/* SURCHARGE OPERATEUR */
	float& operator[](const int);
	Matrix33& operator=(const Matrix33&);
	friend std::ostream& operator<<(std::ostream &strm, const Matrix33& mat);

	/*GETTER*/
	float getElement(const int i, const int j) const;

	/*OPERATION*/
	Vect3 mult(const Vect3 &)const;  /* Multiplication par un vecteur */
	Matrix33 mult(const Matrix33 &)const;  /* Multiplication par une matrice */
	float Det()const;
	Matrix33 inverse()const;
};



#endif