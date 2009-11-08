/*****************************
Tamara Levy
CIS 460
November, 2008
Updated: Nov 7, 2009
Ray Tracer
******************************/

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "algebra3.h"
#include "tests.h"
#include "Node.h"
#include "Matrix.h"
#include "bmp_io.h"
#include "config.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

#include <FL/Fl_Window.h>
#include <FL/Fl_Progress.H>



using namespace std;

#define TRACEDEPTH	5

#define PI			3.141592653589793238462f
#define EPSILON		0.0001f

class Tracer{
private:
	ofstream myfile;
	char *file_out_name;
	Config* config;
	ObjectNode* root;
	float WX1, WX2, WY1, WY2, DX, DY, SX, SY;
	int width, height;
	float smallestT[TRACEDEPTH];
	void IntersectTest(vec3& origin, vec3& dir, vec3& color,ObjectNode* obj,int t_depth);
	bool IntersectTestShadow(vec3 &origin, vec3 &dir,ObjectNode* obj);
	void getColor(vec3 &dir,vec3& color, vec3& normal,vec3& point,ObjectNode* obj,int t_depth);
	void RayTrace(vec3& origin, vec3& dir, vec3& color,ObjectNode* obj,int t_depth);
	bool RayTraceShadow(vec3 &origin, vec3 &dir,ObjectNode* obj);

	


public:
	Tracer(ObjectNode* r, char* fileName, Config* c);
	void setDimensions(int w, int h);
	void InitRender();
	void Render(void* data);
	

};

#endif