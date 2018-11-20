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
	for (int i = 0; i < 12; i++) {
		tab[i] = newTab[i];
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
Matrix34& Matrix34::operator=(const Matrix34& mat)
{
	if (this != &mat) { // self-assignment check expected
		for (int i = 0; i < 12; i++) {
			tab[i] = mat.tab[i];
		}
	}
	return *this;
}

float& Matrix34::operator[](const int i)
{
	if (i <= 12) {
		int c = i % 4;
		int l = i / 4;
		return tab[i];
	}

	std::cout << "error Mat34 [] out of range" << std::endl;
	return tab[0];
}

std::ostream& operator<<(std::ostream &strm, const Matrix34& mat)
{
	strm << "[";
	for (size_t i = 0; i < 3; i++) {
		strm << "[";
		for (size_t j = 0; j < 4; j++) {
			strm << mat.getElement(i, j) << " ";
		}
		strm << "]" << std::endl;
	}
	strm << "]";
	return strm;
}

/* GETTER */

float Matrix34::getElement(const int row, const int col)const
{
	if (row * 4 + col <= 11)
		return this->tab[row * 4 + col];
	else {
		if (row == 3) {
			if (col >= 0 && col <= 2) {
				return 0;
			}
			if (col == 3) {
				return 1;
			}
		}
	}
	std::cout << "error Mat34 getElement out of range" << std::endl;
	return -1;
}


/* OPERATIONS */

Vect3 Matrix34::mult(const Vect3 &vect)const
{
	Vect3 res = new Vect3();

	float X = (vect.getX() * this->tab[0]) + (vect.getY() * this->tab[1]) + (vect.getZ() * this->tab[2]) + getElement(0, 3);
	float Y = (vect.getX() * this->tab[4]) + (vect.getY() * this->tab[5]) + (vect.getZ() * this->tab[6]) + getElement(1, 3);
	float Z = (vect.getX() * this->tab[8]) + (vect.getY() * this->tab[9]) + (vect.getZ() * this->tab[10]) + getElement(2, 3);

	res.setX(X);
	res.setY(Y);
	res.setZ(Z);

	return res;
}

Matrix34 Matrix34::mult(const Matrix34 &vect)const
{
	Matrix34 res = new Matrix34();
	for (int i = 0; i < 12; i++) {
		int c = i % 4;
		int l = i / 4;

		for (size_t j = 0; j < 4; j++) {
			res[i] += this->getElement(l, j)*vect.getElement(j, c);
		}
	}
	return res;
}

Matrix33 Matrix34::getMat33(int row, int col)const
{
	float tempTab[9];
	int temp = 0;
	for (size_t i = 0; i < 16; i++) {
		int c = i % 4;
		int l = i / 4;
		if (l != row && c != col) {
			tempTab[temp] = getElement(l, c);
			temp++;
		}
	}
	return new Matrix33(tempTab);
}


Matrix34 Matrix34::setOrientation(const Quaternion q, const Vect3 pos)
{
	float x = q.i;
	float y = q.j;
	float z = q.k;
	float w = q.r;


	Matrix34 res = new Matrix34();
	res[0] = 1 - 2 * (powf(y, 2) + powf(z, 2));
	res[1] = 2 * (x*y + w * z);
	res[2] = 2 * (x*z - w * y);
	res[3] = pos.getX();
	res[4] = 2 * (x*y - w * z);
	res[5] = 1 - 2 * (powf(x, 2) + powf(z, 2));
	res[6] = 2 * (z*y + w * x);
	res[7] = pos.getY();
	res[8] = 2 * (x*z + w * y);
	res[9] = 2 * (z*y - w * x);
	res[10] = 1 - 2 * (powf(y, 2) + powf(x, 2));
	res[11] = pos.getZ();


	return res;
}

float Matrix34::Det() const
{
	float res = 0;
	for (int i = 0; i <= 3; i++) {
		res += tab[i] * getMat33(0, i).Det()*powf(-1, i);
	}
	return res;
}

Matrix34 Matrix34::Transposition()const
{
	Matrix34 res = new Matrix34();
	for (size_t i = 0; i < 12; i++) {
		int c = i % 4;
		int l = i / 4;
		res[i] = getElement(l, c);
	}
	return res;
}

Matrix34 Matrix34::Transposition(float* f)const
{
	Matrix34 res = new Matrix34();
	for (size_t i = 0; i < 12; i++) {
		int c = i % 4;
		int l = i / 4;
		res[i] = f[c * 4 + l];
	}
	return res;
}

Matrix34 Matrix34::inverse() const
{
	float res[16];

	if (Det() != 0) {
		float f = 1 / Det();
		for (size_t i = 0; i < 16; i++) {
			int c = i % 4;
			int l = i / 4;
			res[i] = getMat33(l, c).Det()*f*powf(-1, l + c);
		}
	}
	return Transposition(res);
}

GLfloat* Matrix34::toGlutMat()
{
	GLfloat* res = new GLfloat[16];
	for (int i = 0; i < 16; i++) {
		int c = i % 4;
		int l = i / 4;
		res[i] = getElement(c, l);
	}
	return res;
}
