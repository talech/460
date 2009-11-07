#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "algebra3.h"


class Matrix{
private:
	double det;
	double matrix[16];
	double inverse[16];
	double transpose[16];
	double inverseTranspose[16];
	double DetMatrix();
	bool inverted;
public:
	Matrix(const double m[16]);
	Matrix(double d, const double m[16], const double in[16],
		const double t[16], const double iT[16]);
	bool removeTrans();
	bool InvertMatrix();
	bool InvertedMatrix(){ return inverted;}
	double getDet(){return det;}
	double getInverse(int i){return inverse[i];}
	vec4 multiply(vec4 vector);
	vec4 multiplyTranspose(vec4 vector);
	vec4 multiplyInverse(vec4 vector);
	vec4 multiplyInverseTranspose(vec4 vector);
	void transposeMatrix();
	void transposeInverse();
	Matrix* copyMatrix();



};



#endif