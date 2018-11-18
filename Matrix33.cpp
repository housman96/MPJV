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


Matrix33::Matrix33(const float* newTab)
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



/* SURCHARGE OPERATEUR */
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
	std::cout << "error Mat33 [] out of range" << std::endl;
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
		strm << "]" << std::endl;
	}
	strm << "]";
	return strm;
}

/* GETTER */

float Matrix33::getElement(const int row, const int col)const {
	if (row * 3 + col <= 8)
		return this->tab[row * 3 + col];

	std::cout << "error Mat33 getElement out of range" << std::endl;
	return -1;
}


/* OPERATIONS */

Vect3 Matrix33::mult(const Vect3 &vect)const {
	Vect3 res = new Vect3();

	float X = (vect.getX() * this->tab[0]) + (vect.getY() * this->tab[1]) + (vect.getZ() * this->tab[2]);
	float Y = (vect.getX() * this->tab[3]) + (vect.getY() * this->tab[4]) + (vect.getZ() * this->tab[5]);
	float Z = (vect.getX() * this->tab[6]) + (vect.getY() * this->tab[7]) + (vect.getZ() * this->tab[8]);

	res.setX(X);
	res.setY(Y);
	res.setZ(Z);

	return res;
}

Matrix33 Matrix33::mult(const Matrix33 &vect)const {
	Matrix33 res = new Matrix33();
	for (int i = 0; i < 9;i++) {
		int c = i % 3;
		int l = i / 3;

		for (size_t j = 0; j < 3; j++)
		{
			res[i] += this->getElement(l, j)*vect.getElement(j, c);
		}
	}
	return res;
}

Matrix33 Matrix33::mult(const float f)const {
	Matrix33 res = new Matrix33();
	for (int i = 0; i < 9;i++) {
		res[i] = res[i] * f;
	}
	return res;
}

float Matrix33::Det22(int row, int col)const {
	std::vector<float> tempTab;
	for (size_t i = 0; i < 9; i++)
	{
		int c = i % 3;
		int l = i / 3;
		if (l != row && c != col) {
			tempTab.push_back(tab[i]);
		}
	}

	return tempTab[0] * tempTab[3] - tempTab[1] * tempTab[2];
}

float Matrix33::Det()const {
	float res = 0.;
	res = tab[0] * Det22(0, 0) - tab[1] * Det22(0, 1) + tab[2] * Det22(0, 2);
	return res;
}

Matrix33 Matrix33::Transposition()const {
	Matrix33 res = new Matrix33();
	for (size_t i = 0; i < 9; i++)
	{
		int c = i % 3;
		int l = i / 3;
		res[i] = getElement(c, l);
	}
	return res;
}

Matrix33 Matrix33::inverse()const {
	Matrix33 res = new Matrix33();
	float f = 1 / Det();
	for (size_t i = 0; i < 9; i++)
	{
		int c = i % 3;
		int l = i / 3;
		res[i] = Det22(l, c)*f;
		if (i % 2 != 0) {
			res[i] = -res[i];
		}
	}
	return res.Transposition();
}

Matrix33 Matrix33::setOrientation(const Quaternion q)
{
	Matrix33 res = new Matrix33();
	res[0] = 1 - 2 * (powf(q.j, 2) + powf(q.k, 2));
	res[1] = 2 * (q.i*q.j + q.r*q.k);
	res[2] = 2 * (q.i*q.k - q.r*q.j);
	res[3] = 2 * (q.i*q.j - q.r*q.k);
	res[4] = 1 - 2 * (powf(q.i, 2) + powf(q.k, 2));
	res[5] = 2 * (q.k*q.j + q.r*q.i);
	res[6] = 2 * (q.i*q.k + q.r*q.j);
	res[7] = 2 * (q.k*q.j - q.r*q.i);
	res[8] = 1 - 2 * (powf(q.j, 2) + powf(q.i, 2));

	return res;
}


/* TENSEURS */

Matrix33 Matrix33::BoxTensor(float m, float dx, float dy, float dz)
{
	Matrix33 tensor = new Matrix33();
	tensor[0] = (m * (dy * dy + dz * dz)) / 12.;
	tensor[4] = (m * (dx * dx + dz * dz)) / 12.;
	tensor[8] = (m * (dx * dx + dy * dy)) / 12.;
	return tensor;
}

Matrix33 Matrix33::SphereTensor(float m, float r)
{
	Matrix33 tensor = new Matrix33();
	float val = (2 * m * r * r) / 5.;
	tensor[0] = val;
	tensor[4] = val;
	tensor[8] = val;
	return tensor;
}