#ifndef MATRIX33_H
#define MATRIX33_H

#include <iostream>


class Matrix33
{
private:
	float** values;

public:
	Matrix33(float, float, float, float, float, float, float, float, float);
	~Matrix33();

	void log();
	float getVal(int, int);
};

#endif