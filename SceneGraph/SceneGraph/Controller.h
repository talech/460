/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glut.h>


#include <string>
#include <vector>
#include "node.h"
#include "Mesh.h"
#include "Extrude.h"
#include "Surfrev.h"
#include "algebra3.h"
#include "parser.h"
#include "rayTracer.h"

class Controller{
private:
	ObjectNode* root;
	
	
	void NextNodeHelp();
	void PrintHelp(ObjectNode* node);
		
public:
	Controller();
	ObjectNode* selected;
	void removeNode();
	void addNode(string n, int t, int s);
	void NextNode();
	void PrevNode();
	void PrintGraph();
	void draw();
	void translate(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotate(float x, float y, float z);
	void color(float r, float g, float b);
	int shape(){return selected->getShape();}
	int counter;
	bool rootSelected(){return selected == root; }
	void clone();
	
	bool addMesh(const std::string& filename);
	void loadTexture(char* Filename, int num){ root->LoadGLTextures(Filename, num);}
	
	void render();

	void setDiffuse(float d){ selected->transforms->setDiffuse(d);}
	void setSpecular(float s){ selected->transforms->setSpecular(s);}
	void setReflection(float r){ selected->transforms->setReflection(r);}
};


#endif


