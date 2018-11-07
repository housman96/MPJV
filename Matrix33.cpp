#include "Matrix33.h"

using namespace std;


Matrix33::Matrix33(float val00, float val01, float val02, float val10, float val11, float val12, float val20, float val21, float val22)
{
	values = new float*[3];
	for (int i = 0; i < 3; i++) {
		values[i] = new float[3];
	}

	values[0][0] = val00;
	values[0][1] = val01; 
	values[0][2] = val02;
	values[1][0] = val10;
	values[1][1] = val11;
	values[1][2] = val12;
	values[2][0] = val20;
	values[2][1] = val21;
	values[2][2] = val22;
}

Matrix33::~Matrix33()
{
	//for (int i = 0; i < 3; i++) {
	//	delete[] values[i];
	//}
	//delete[] values;
}

void Matrix33::log()
{
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			cout << values[j][i] << " ";
		}
		cout << endl;
	}
}

float Matrix33::getVal(int row, int col)
{
	return values[row][col];
}
