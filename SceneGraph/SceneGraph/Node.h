/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/


#ifndef NODE_H
#define NODE_H

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <Fl/Gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glaux.h>	

#include "objects.h"
#include "Mesh.h"




using namespace std;

enum objectType{ROOT,OBJECT,SHAPE,MESHO,LIGHT};
enum object{RootNode,Chair,Desk,Lamp,Cabinet,Sphere,
			Cube,Cylinder,Half,Disk,MeshO,Monitor,Light};
static GLuint texture[2];
//Abstract Class Node
class Node{
};

/****************************
//Transformation Nodes 
*****************************/
class Transform: public Node{
private:
	float translateX;
	float translateY;
	float translateZ;
	float scaleX;
	float scaleY;
	float scaleZ;
	float angleX;
	float angleY;
	float angleZ;
	float color[3];
	float color2[3];
	float specular;
	float diffuse;
	float reflection;

public:
	Transform();
	void setTransX(float num){translateX += num;}
	void setTransY(float num){translateY += num;}
	void setTransZ(float num){translateZ += num;}
	void setScaleX(float num){scaleX = num;}
	void setScaleY(float num){scaleY = num;}
	void setScaleZ(float num){scaleZ = num;}
	void setAngleX(float num){angleX = num;}
	void setAngleY(float num){angleY = num;}
	void setAngleZ(float num){angleZ = num;}
	void setColor(float numR, float numG, float numB){
		color[0] = numR;
		color[1] = numG;
		color[2] = numB;
		color2[0] = 1-numR;
		color2[1] = 1-numG;
		color2[2] = 1-numB;}

	void setDiffuse(float num){diffuse = num;}
	void setSpecular(float num){specular = num;}
	void setReflection(float num){reflection = num;}

	float getTransX(){return translateX;}
	float getTransY(){return translateY;}
	float getTransZ(){return translateZ;}
	float getScaleX(){return scaleX;}
	float getScaleY(){return scaleY;}
	float getScaleZ(){return scaleZ;}
	float getAngleX(){return angleX;}
	float getAngleY(){return angleY;}
	float getAngleZ(){return angleZ;}
	float getR(){return color[0];}
	float getG(){return color[1];}
	float getB(){return color[2];}
	float getR2(){return color2[0];}
	float getG2(){return color2[1];}
	float getB2(){return color2[2];}

	float getDiffuse(){return diffuse;}
	float getSpecular(){return specular;}
	float getReflection(){return reflection;}
};


/****************************
//Object Nodes 
*****************************/

class ObjectNode: public Node{
protected:
	vector<ObjectNode*> children;
	ObjectNode* parent;
	
	bool root;
	string name;
	int type;
	int shape;
	bool selected;

	void drawMe(int select);

	//For texture loading
	
	AUX_RGBImageRec* LoadBMP(char* Filename);
	
	bool haveTexture;
	double mat[5][16];
	
	
	

public:
	Transform* transforms;
	Mesh* myMesh;
	ObjectNode(string n, int t, int s);
	~ObjectNode();
	int numChildren(){ return children.size();}
	int childNum(ObjectNode* node);
	string nodeName(){return name;}
	void setRoot();
	void setSelected(){selected = true;}
	void unSelect(){selected = false;}
	void setParent(ObjectNode* node);
	void addChild(ObjectNode* node);
	void deleteChild(ObjectNode* node);
	void deleteAllChildren();
	bool hasChild(ObjectNode* node);
	bool isRoot(){ return root;}
	ObjectNode* getParent(){ return parent;}
	ObjectNode* nextChild(ObjectNode* currentChild);
	ObjectNode* getChild(int i){return children[i];}
	void drawObject(int select);
	ObjectNode* firstChild(){ return children[0];}
	int getShape(){return shape;}
	int getObject(){return type;}
	void cloneChildren(ObjectNode* newNodeParent);
	
	void addMesh(Mesh* m){myMesh = m;}

	int LoadGLTextures(char* Filename, int num);	

	void getMatrix(double* m,int k){
		for(int i=0; i<16; i++)
			m[i] = mat[k][i];
	}
	
	



};

#endif