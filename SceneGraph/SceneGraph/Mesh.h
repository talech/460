/*****************************
Tamara Levy
CIS 460
October 23, 2008
SceneGraph - Room Editor
******************************/
/*****************************
Mesh.h
Is a container.
It stores the geometry of the mesh, this includes
vertices, face list and the corresponding normals.
******************************/

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <Fl/Gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "algebra3.h"
#include "tests.h"

using namespace std;

class Mesh{
private:
	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vector<vec2>> faces;
	bool convex;
	
public:
	Mesh(bool conv);
	Mesh();
	void addVertex(vec3 v);
	void addNormal(vec3 vn);
	void addFace(vector<vec2> f);
	void drawMesh();
	vec3 getVertex(int i){return vertices[i];}
	int lastNorm(){return normals.size()-1;}
	int lastVertex(){return vertices.size()-1;}
	int numFaces(){return faces.size();}
	bool isConvex(){return convex;}

	void findBoundingBox(vec3& max, vec3& min);
	float Test_RayMeshIntersect(const double P0[3], const double V0[3],
		const double matrix[16],vec3& normOut, vec3& inPoint);

};

#endif