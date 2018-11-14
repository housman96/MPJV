#include "Matrix34.h"



/* CONSTRUCTEURS */

Matrix34::Matrix34()
{
	tab = new float[12];
	for (int i = 0; i < 12; i++) {
		tab[i] = 0.;
	}
}

Matrix34::Matrix34(const Matrix34 &mat)
{
	tab = new float[12];
	for (int i = 0; i < 12; i++) {
		tab[i] = mat.tab[i];
	}
}

Matrix34::Matrix34(const Matrix34 *mat)
{
	tab = new float[12];
	for (int i = 0; i < 12; i++) {
		tab[i] = mat->tab[i];
	}
}


Matrix34::Matrix34(const float* newTab)
{
	tab = new float[12];
	int lastIndex = 12;
	if (sizeof(newTab) + 1 < 12)
	{
		lastIndex = sizeof(newTab) + 1;
	}
	for (int i = 0; i < lastIndex; i++) {
		tab[i] = newTab[i];
	}
	for (int i = lastIndex; i < 12; i++) {
		tab[i] = 0.;
	}
}

/* DESTRUCTEURS */

Matrix34::~Matrix34()
{
	if (tab) {
		delete[]  tab;
	}
}



/* SURCHARGE OPERATEUR */
Matrix34& Matrix34::operator=(const Matrix34& mat) {
	if (this != &mat) { // self-assignment check expected
		for (int i = 0; i < 12; i++) {
			tab[i] = mat.tab[i];
		}
	}
	return *this;
}

float& Matrix34::operator[](const int i) {
	if (i <= 12)
		return tab[i];
	std::cout << "error Mat34 [] out of range" << std::endl;
	return tab[0];
}

std::ostream& operator<<(std::ostream &strm, const Matrix34& mat) {
	strm << "[";
	for (size_t i = 0; i < 3; i++)
	{
		strm << "[";
		for (size_t j = 0; j < 4; j++)
		{
			strm << mat.getElement(i, j) << " ";
		}
		strm << "]" << std::endl;
	}
	strm << "]";
	return strm;
}

/* GETTER */

float Matrix34::getElement(const int row, const int col)const {
	if (row * 4 + col <= 11)
		return this->tab[row * 4 + col];
	else {
		if (row == 3) {
			if (col >= 0 && col <= 2) {
				return 0;
			}
			if (col == 3)
			{
				return 1;
			}
		}
	}
	std::cout << "error Mat34 getElement out of range" << std::endl;
	return -1;
}


/* OPERATIONS */

Vect3 Matrix34::mult(const Vect3 &vect)const {
	Vect3 res = new Vect3();

	float X = (vect.getX() * this->tab[0]) + (vect.getY() * this->tab[1]) + (vect.getZ() * this->tab[2]) + getElement(0, 3);
	float Y = (vect.getX() * this->tab[4]) + (vect.getY() * this->tab[5]) + (vect.getZ() * this->tab[6]) + getElement(1, 3);
	float Z = (vect.getX() * this->tab[8]) + (vect.getY() * this->tab[9]) + (vect.getZ() * this->tab[10]) + getElement(2, 3);

	res.setX(X);
	res.setY(Y);
	res.setZ(Z);

	return res;
}

Matrix34 Matrix34::mult(const Matrix34 &vect)const {
	Matrix34 res = new Matrix34();
	for (int i = 0; i < 12;i++) {
		int c = i % 4;
		int l = i / 4;

		for (size_t j = 0; j < 4; j++)
		{
			res[i] += this->getElement(l, j)*vect.getElement(j, c);
		}
	}
	return res;
}

Matrix34 Matrix34::setOrientation(const Quaternion q)
{
	Matrix34 res = new Matrix34();
	res[0] = 1 - 2 * (powf(q.j, 2) + powf(q.k, 2));
	res[1] = 2 * (q.i*q.j + q.r*q.k);
	res[2] = 2 * (q.i*q.k - q.r*q.j);
	res[3] = q.i;
	res[4] = 2 * (q.i*q.j - q.r*q.k);
	res[5] = 1 - 2 * (powf(q.i, 2) + powf(q.k, 2));
	res[6] = 2 * (q.k*q.j + q.r*q.i);
	res[7] = q.j;
	res[8] = 2 * (q.i*q.k + q.r*q.j);
	res[9] = 2 * (q.k*q.j - q.r*q.i);
	res[10] = 1 - 2 * (powf(q.j, 2) + powf(q.i, 2));
	res[11] = q.k;
	return res;
}
