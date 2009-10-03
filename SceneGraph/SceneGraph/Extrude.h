/*****************************
Tamara Levy
CIS 460
October 24, 2008
SceneGraph - Room Editor
******************************/

#ifndef EXTRUDE_H
#define EXTRUDE_H

#include <vector>
#include "algebra3.h"
#include "Mesh.h"

using namespace std;

class Extrude{
private:
	vector<vec3> polygon;
	float distance;
	int sides;

	bool isConvex();
	vec4 getNormal(vec4 vert1, vec4 vert2, vec4 vert3);

public:
	Extrude(vector<vec3> p, float d, int s);
	Mesh* createMesh();
};

#endif