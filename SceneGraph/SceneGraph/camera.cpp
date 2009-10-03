/*
 * Camera.cpp
 * 
 */

#include "camera.h"

camera::camera(){
	xAxis[0] = 1;
	xAxis[1] = 0;
	xAxis[2] = 0;

	yAxis[0] = 0;
	yAxis[1] = 1;
	yAxis[2] = 0;

	zAxis[0] = 0;
	zAxis[1] = 0;
	zAxis[2] = 1;

	rotations = identity3D();
	
	center[0] = 0;
	center[1] = 1.0;
	center[2] = 0;
		
	//eye on horizontal surface of sphere
	eye[0] = 0.0;
	eye[1] = 5.0;
	eye[2] = 15.0;

	eyeOrig[0] = 0.0;
	eyeOrig[1] = 5.0;
	eyeOrig[2] = 15.0;

	up = yAxis;
	upOrig = yAxis;
}

void camera::rotateRightLeft(float angle){
	// positive angle -> rotate right
	// negative angle -> rotate left
	
	rotations = rotations * rotation3D(yAxis, angle);
	eye =  rotations * eyeOrig;
	up = rotations * upOrig;
}

void camera::rotateUpDown(float angle){
	// positive angle -> rotate up
	// negative angle -> rotate down
	angle = angle * (-1);
	rotations = rotations * rotation3D(xAxis, angle);
	eye = rotations * eyeOrig;
	up = rotations * upOrig;
}

void camera::zoom(float value){
	// positive value -> zoom in
	// negative value -> zoom out
		

	eyeOrig[2] = eyeOrig[2] + value;
	
	eye = rotations * eyeOrig;
	up = rotations * upOrig;
}

void camera::print(){
	std::cout<< "Eye: "<<std::endl; //eye.print();
	std::cout<<std::endl;
	std::cout<< "Up: "<<std::endl; //up.print();
	std::cout<< "Rotation: "<<std::endl; //rotations.print();
	std::cout<<std::endl;
}