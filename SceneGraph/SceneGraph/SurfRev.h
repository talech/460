/*****************************
Tamara Levy
CIS 460
October 24, 2008
SceneGraph - Room Editor
******************************/

#ifndef SURFREV_H
#define SURFREV_H

#include <vector>
#include "algebra3.h"
#include "Mesh.h"

using namespace std;

class Surfrev{
private:
	vector<vec3> polyline;
	int slices;
	int points;

	vec4 getNormal(vec4 vert1, vec4 vert2, vec4 vert3);

public:
	Surfrev(vector<vec3> p, int s, int p0);
	Mesh* createMesh();

};

#endif