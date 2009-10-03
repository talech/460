/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/


#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include "algebra3.h"

class camera{
private:
	mat4 rotations;
	
	vec3 eyeOrig;
	vec3 upOrig;

	vec3 xAxis;
	vec3 yAxis;
	vec3 zAxis;

public:
		
	vec3 center;
	vec3 eye;
	vec3 up;

	camera();
	void rotateRightLeft(float angle);
	void rotateUpDown(float angle);
	void zoom(float value);
	void update();
	void print();
};

#endif