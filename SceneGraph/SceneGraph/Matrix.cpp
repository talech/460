#include "Matrix.h"

Matrix::Matrix(const double m[16]){
	for(int i=0; i<16; i++){
		matrix[i] = m[i];
	}

	det = DetMatrix();
	transposeMatrix();
}

double
Matrix::DetMatrix(){
	float determinant = (matrix[0] * matrix[5] * matrix[10] * matrix[15]) + 
				(matrix[0] * matrix[9] * matrix[14] * matrix[7]) + 
				(matrix[0] * matrix[13] * matrix[6] * matrix[11])+	
				(matrix[4] * matrix[1] * matrix[14] * matrix[11]) + 
				(matrix[4] * matrix[9] * matrix[2] * matrix[15]) + 
				(matrix[4] * matrix[13] * matrix[10] * matrix[3]) +
				(matrix[8] * matrix[1] * matrix[6] * matrix[15]) + 
				(matrix[8] * matrix[5] * matrix[14] * matrix[3]) + 
				(matrix[8] * matrix[13] * matrix[2] * matrix[7]) + 	
				(matrix[12] * matrix[1] * matrix[10] * matrix[7]) + 
				(matrix[12] * matrix[5] * matrix[2] * matrix[11]) + 
				(matrix[12] * matrix[9] * matrix[6] * matrix[3])+
				((-1)*(matrix[0] * matrix[5] * matrix[14] * matrix[11])) +
				((-1)*(matrix[0] * matrix[9] * matrix[6] * matrix[15])) + 
				((-1)*(matrix[0] * matrix[13] * matrix[10] * matrix[7]))+ 	
				((-1)*(matrix[4] * matrix[1] * matrix[10] * matrix[15])) + 
				((-1)*(matrix[4] * matrix[9] * matrix[14] * matrix[3])) + 
				((-1)*(matrix[4] * matrix[13] * matrix[2] * matrix[11]))+	
				((-1)*(matrix[8] * matrix[1] * matrix[14] * matrix[7])) + 
				((-1)*(matrix[8] * matrix[5] * matrix[2] * matrix[15])) + 
				((-1)*(matrix[8] * matrix[13] * matrix[6] * matrix[3])) +	
				((-1)*(matrix[12] * matrix[1] * matrix[6] * matrix[11])) + 
				((-1)*(matrix[12] * matrix[5] * matrix[10] * matrix[3])) + 
				((-1)*(matrix[12] * matrix[9] * matrix[2] * matrix[7])); 
	return determinant;
}

bool
Matrix::InvertMatrix(){
	if(det == 0) return false;
	else{
		inverse[0] = ((matrix[5]*matrix[10]*matrix[15])+(matrix[9]*matrix[14]*matrix[7])+(matrix[13]*matrix[6]*matrix[11])-(matrix[5]*matrix[14]*matrix[11])-(matrix[9]*matrix[6]*matrix[15])-(matrix[13]*matrix[10]*matrix[7]))/det;
		inverse[4] = ((matrix[4]*matrix[14]*matrix[11])+(matrix[8]*matrix[6]*matrix[15])+(matrix[4]*matrix[10]*matrix[7])-(matrix[4]*matrix[10]*matrix[15])-(matrix[8]*matrix[14]*matrix[7])-(matrix[12]*matrix[6]*matrix[11]))/det;
		inverse[8] = ((matrix[4]*matrix[9]*matrix[15])+(matrix[8]*matrix[13]*matrix[7])+(matrix[12]*matrix[5]*matrix[11])-(matrix[4]*matrix[13]*matrix[11])-(matrix[8]*matrix[5]*matrix[15])-(matrix[12]*matrix[9]*matrix[7]))/det;
		inverse[12] = ((matrix[4]*matrix[13]*matrix[10])+(matrix[8]*matrix[5]*matrix[14])+(matrix[12]*matrix[9]*matrix[6])-(matrix[4]*matrix[9]*matrix[14])-(matrix[8]*matrix[13]*matrix[6])-(matrix[12]*matrix[5]*matrix[10]))/det;
		inverse[1] = ((matrix[1]*matrix[14]*matrix[11])+(matrix[9]*matrix[2]*matrix[15])+(matrix[13]*matrix[10]*matrix[3])-(matrix[1]*matrix[10]*matrix[15])-(matrix[9]*matrix[14]*matrix[3])-(matrix[13]*matrix[2]*matrix[11]))/det;
		inverse[5] = ((matrix[0]*matrix[10]*matrix[15])+(matrix[8]*matrix[14]*matrix[3])+(matrix[12]*matrix[2]*matrix[11])-(matrix[0]*matrix[14]*matrix[11])-(matrix[8]*matrix[2]*matrix[15])-(matrix[12]*matrix[10]*matrix[3]))/det;
		inverse[9] = ((matrix[0]*matrix[13]*matrix[11])+(matrix[8]*matrix[1]*matrix[15])+(matrix[12]*matrix[9]*matrix[3])-(matrix[0]*matrix[9]*matrix[15])-(matrix[8]*matrix[13]*matrix[3])-(matrix[12]*matrix[1]*matrix[11]))/det;
		inverse[13] = ((matrix[0]*matrix[9]*matrix[14])+(matrix[8]*matrix[13]*matrix[2])+(matrix[12]*matrix[1]*matrix[10])-(matrix[0]*matrix[13]*matrix[10])-(matrix[8]*matrix[1]*matrix[14])-(matrix[12]*matrix[9]*matrix[2]))/det;
		inverse[2] = ((matrix[1]*matrix[6]*matrix[15])+(matrix[5]*matrix[14]*matrix[3])+(matrix[13]*matrix[2]*matrix[7])-(matrix[1]*matrix[14]*matrix[7])-(matrix[5]*matrix[2]*matrix[15])-(matrix[13]*matrix[6]*matrix[3]))/det;
		inverse[6] = ((matrix[0]*matrix[14]*matrix[7])+(matrix[4]*matrix[2]*matrix[15])+(matrix[12]*matrix[6]*matrix[3])-(matrix[0]*matrix[6]*matrix[15])-(matrix[4]*matrix[14]*matrix[3])-(matrix[12]*matrix[2]*matrix[7]))/det;
		inverse[10] = ((matrix[0]*matrix[5]*matrix[15])+(matrix[4]*matrix[13]*matrix[3])+(matrix[12]*matrix[1]*matrix[7])-(matrix[0]*matrix[13]*matrix[7])-(matrix[4]*matrix[1]*matrix[15])-(matrix[12]*matrix[5]*matrix[3]))/det;
		inverse[14] = ((matrix[0]*matrix[13]*matrix[6])+(matrix[4]*matrix[1]*matrix[14])+(matrix[12]*matrix[5]*matrix[2])-(matrix[0]*matrix[5]*matrix[14])-(matrix[4]*matrix[13]*matrix[2])-(matrix[12]*matrix[1]*matrix[6]))/det;
		inverse[3] = ((matrix[1]*matrix[10]*matrix[7])+(matrix[5]*matrix[2]*matrix[11])+(matrix[9]*matrix[6]*matrix[3])-(matrix[1]*matrix[6]*matrix[11])-(matrix[5]*matrix[10]*matrix[3])-(matrix[9]*matrix[2]*matrix[7]))/det;
		inverse[7] = ((matrix[0]*matrix[6]*matrix[11])+(matrix[4]*matrix[10]*matrix[3])+(matrix[8]*matrix[2]*matrix[7])-(matrix[0]*matrix[10]*matrix[7])-(matrix[4]*matrix[2]*matrix[11])-(matrix[8]*matrix[6]*matrix[3]))/det;
		inverse[11] = ((matrix[0]*matrix[9]*matrix[7])+(matrix[4]*matrix[1]*matrix[11])+(matrix[8]*matrix[5]*matrix[3])-(matrix[0]*matrix[5]*matrix[11])-(matrix[4]*matrix[9]*matrix[3])-(matrix[8]*matrix[1]*matrix[7]))/det;
		inverse[15] = ((matrix[0]*matrix[5]*matrix[10])+(matrix[4]*matrix[9]*matrix[2])+(matrix[8]*matrix[1]*matrix[6])-(matrix[0]*matrix[9]*matrix[6])-(matrix[4]*matrix[1]*matrix[10])-(matrix[8]*matrix[5]*matrix[2]))/det;
		
		transposeInverse();
		return true;
	}
}

vec4
Matrix::multiply(vec4 vector){
	vec4 newVec;
	newVec[0] = (matrix[0]*vector[0])+(matrix[4]*vector[1])+(matrix[8]*vector[2])+(matrix[12]*vector[3]);
	newVec[1] = (matrix[1]*vector[0])+(matrix[5]*vector[1])+(matrix[9]*vector[2])+(matrix[13]*vector[3]);
	newVec[2] = (matrix[2]*vector[0])+(matrix[6]*vector[1])+(matrix[10]*vector[2])+(matrix[14]*vector[3]);
	newVec[3] = (matrix[3]*vector[0])+(matrix[7]*vector[1])+(matrix[11]*vector[2])+(matrix[15]*vector[3]);
	return newVec;
}

vec4
Matrix::multiplyTranspose(vec4 vector){
	vec4 newVec;
	newVec[0] = (transpose[0]*vector[0])+(transpose[4]*vector[1])+(transpose[8]*vector[2])+(transpose[12]*vector[3]);
	newVec[1] = (transpose[1]*vector[0])+(transpose[5]*vector[1])+(transpose[9]*vector[2])+(transpose[13]*vector[3]);
	newVec[2] = (transpose[2]*vector[0])+(transpose[6]*vector[1])+(transpose[10]*vector[2])+(transpose[14]*vector[3]);
	newVec[3] = (transpose[3]*vector[0])+(transpose[7]*vector[1])+(transpose[11]*vector[2])+(transpose[15]*vector[3]);
	return newVec;
}

vec4
Matrix::multiplyInverse(vec4 vector){
	vec4 newVec;
	newVec[0] = (inverse[0]*vector[0])+(inverse[4]*vector[1])+(inverse[8]*vector[2])+(inverse[12]*vector[3]);
	newVec[1] = (inverse[1]*vector[0])+(inverse[5]*vector[1])+(inverse[9]*vector[2])+(inverse[13]*vector[3]);
	newVec[2] = (inverse[2]*vector[0])+(inverse[6]*vector[1])+(inverse[10]*vector[2])+(inverse[14]*vector[3]);
	newVec[3] = (inverse[3]*vector[0])+(inverse[7]*vector[1])+(inverse[11]*vector[2])+(inverse[15]*vector[3]);
	return newVec;
}

vec4
Matrix::multiplyInverseTranspose(vec4 vector){
	vec4 newVec;
	newVec[0] = (inverseTranspose[0]*vector[0])+(inverseTranspose[4]*vector[1])+(inverseTranspose[8]*vector[2])+(inverseTranspose[12]*vector[3]);
	newVec[1] = (inverseTranspose[1]*vector[0])+(inverseTranspose[5]*vector[1])+(inverseTranspose[9]*vector[2])+(inverseTranspose[13]*vector[3]);
	newVec[2] = (inverseTranspose[2]*vector[0])+(inverseTranspose[6]*vector[1])+(inverseTranspose[10]*vector[2])+(inverseTranspose[14]*vector[3]);
	newVec[3] = (inverseTranspose[3]*vector[0])+(inverseTranspose[7]*vector[1])+(inverseTranspose[11]*vector[2])+(inverseTranspose[15]*vector[3]);
	return newVec;
}

bool
Matrix::removeTrans(){
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;

	transposeMatrix();
	bool ret = InvertMatrix();
	transposeInverse();
	return ret;

}

void
Matrix::transposeMatrix(){
	transpose[0] = matrix[0];	transpose[4] = matrix[1];
	transpose[1] = matrix[4];	transpose[5] = matrix[5];
	transpose[2] = matrix[8];	transpose[6] = matrix[9];
	transpose[3] = matrix[12];	transpose[7] = matrix[13];

	transpose[8] = matrix[2];	transpose[12] = matrix[3];
	transpose[9] = matrix[6];	transpose[13] = matrix[7];
	transpose[10] = matrix[10];	transpose[14] = matrix[11];
	transpose[11] = matrix[14];	transpose[15] = matrix[15];

}

void
Matrix::transposeInverse(){
	inverseTranspose[0] = inverse[0];	inverseTranspose[4] = inverse[1];
	inverseTranspose[1] = inverse[4];	inverseTranspose[5] = inverse[5];
	inverseTranspose[2] = inverse[8];	inverseTranspose[6] = inverse[9];
	inverseTranspose[3] = inverse[12];	inverseTranspose[7] = inverse[13];

	inverseTranspose[8] = inverse[2];	inverseTranspose[12] = inverse[3];
	inverseTranspose[9] = inverse[6];	inverseTranspose[13] = inverse[7];
	inverseTranspose[10] = inverse[10];	inverseTranspose[14] = inverse[11];
	inverseTranspose[11] = inverse[14];	inverseTranspose[15] = inverse[15];

}