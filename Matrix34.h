#ifndef Matrix34_H
#define Matrix34_H

#include "Vect3.h"
#include "Quaternion.h"
#include "Matrix33.h"
#include <math.h>
#include <vector>
#include <GL/glut.h>

class Matrix34
{

private:

public:

	/*DONNEES*/
	float* tab;

	/* CONSTRUCTEURS */
	Matrix34();
	Matrix34(const Matrix34 &);
	Matrix34(const Matrix34*);
	Matrix34(const float*);
	/* DESTRUCTEURS */
	~Matrix34();

	/* SURCHARGE OPERATEUR */
	float& operator[](const int);
	Matrix34& operator=(const Matrix34&);
	friend std::ostream& operator<<(std::ostream &strm, const Matrix34& mat);

	/*GETTER*/
	float getElement(const int i, const int j) const;

	/*OPERATION*/
	Vect3 mult(const Vect3 &)const;  /* Multiplication par un vecteur */
	Matrix34 mult(const Matrix34 &)const;  /* Multiplication par une matrice */
	Matrix33 getMat33(int row, int col)const;
	float Det()const;
	Matrix34 Transposition()const;
	Matrix34 inverse()const;
	static Matrix34 setOrientation(const Quaternion, const Vect3);
	Matrix34 Transposition(float*)const;
	GLfloat* Matrix34::toGlutMat();
};

#endif
