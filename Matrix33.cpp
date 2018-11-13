#include "Matrix33.h"

/* CONSTRUCTEURS */

Matrix33::Matrix33()
{
	tab = new float[9];
	for (int i = 0; i < 9; i++) {
		tab[i] = 0.;
	}
}

Matrix33::Matrix33(const Matrix33 &mat)
{
	tab = new float[9];
	for (int i = 0; i < 9; i++) {
		tab[i] = mat.tab[i];
	}
}

Matrix33::Matrix33(const Matrix33 *mat)
{
	tab = new float[9];
	for (int i = 0; i < 9; i++) {
		tab[i] = mat->tab[i];
	}
}


Matrix33::Matrix33(float* newTab)
{
	tab = new float[9];
	int lastIndex = 9;
	if (sizeof(newTab) + 1 < 9)
	{
		lastIndex = sizeof(newTab) + 1;
	}
	for (int i = 0; i < lastIndex; i++) {
		tab[i] = newTab[i];
	}
	for (int i = lastIndex; i < 9; i++) {
		tab[i] = 0.;
	}
}

/* DESTRUCTEURS */

Matrix33::~Matrix33()
{
	if (tab) {
		delete[]  tab;
	}
}


/* OPERATIONS */

Matrix33& Matrix33::operator=(const Matrix33& mat) {
	if (this != &mat) { // self-assignment check expected
		for (int i = 0; i < 9; i++) {
			tab[i] = mat.tab[i];
		}
	}
	return *this;
}

float& Matrix33::operator[](const int i) {
	if (i <= 9)
		return tab[i];
	std::cout << "error [] out of range" << std::endl;
	return tab[0];
}

std::ostream& operator<<(std::ostream &strm, const Matrix33& mat) {
	strm << "[";
	for (size_t i = 0; i < 3; i++)
	{
		strm << "[";
		for (size_t j = 0; j < 3; j++)
		{
			strm << mat.getElement(i, j) << " ";
		}
		strm << "]";
	}
	strm << "]";
	return strm;
}

float Matrix33::getElement(int i, int j)const {
	if (i * 3 + j <= 8)
		return this->tab[i * 3 + j];

	std::cout << "error getElement out of range" << std::endl;
	return -1;
}

Vect3 Matrix33::mult(Vect3 &vect) {
	Vect3 res = new Vect3();

	float X = (vect.getX() * this->tab[0]) + (vect.getY() * this->tab[1]) + (vect.getZ() * this->tab[2]);
	float Y = (vect.getX() * this->tab[3]) + (vect.getY() * this->tab[4]) + (vect.getZ() * this->tab[5]);
	float Z = (vect.getX() * this->tab[6]) + (vect.getY() * this->tab[7]) + (vect.getZ() * this->tab[8]);

	res.setX(X);
	res.setY(Y);
	res.setZ(Z);

	return res;
}

Matrix33 Matrix33::mult(Matrix33 &vect) {
	Matrix33 res = new Matrix33();
	for (int i = 0; i < 9;i++) {
		int l = i % 3;
		int c = i / 3;

		for (size_t j = 0; j < 3; j++)
		{
			float t1 = this->getElement(l, j);
			float t2 = vect.getElement(j, c);
			float t = t1 * t2;

			res[i] += t;

		}
	}
	return res;
}
