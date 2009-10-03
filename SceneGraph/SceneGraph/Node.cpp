/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#include "node.h"
#include <iostream>

using namespace std;


/****************************
//Transformation Nodes 
*****************************/
Transform::Transform():Node(){
	translateX = 0;
	translateY = 0;
	translateZ = 0;
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	angleX = 0;
	angleY = 0;
	angleZ = 0;
	specular = 0;
	diffuse = 1;
	reflection = 0;
}

/****************************
//Object Nodes 
*****************************/
ObjectNode::ObjectNode(string n, int t, int s):Node(){
	transforms = new Transform();
	root = false;
	selected = false;
	name = n;
	type = t;
	shape = s;
	haveTexture = false;
	if(type == Chair)transforms->setColor(0.6,0.7,1.0);
	else if(type == Desk) transforms->setColor(0.4,0.5,1.0);
	else if(type == Lamp) transforms->setColor(.6, .6, .6);
	else if(type == Cabinet) transforms->setColor(1.0,0.0,0.0);
	else if(type == Sphere)transforms->setColor(0.0,1.0,0.0);
	else if(type == Cube)transforms->setColor(1.0,0.0,0.0);
	else if(type == Cylinder)transforms->setColor(1.0,1.0,0.0);
	else if(type == Half)transforms->setColor(0.0,0.0,1.0);
	else if(type == Disk)transforms->setColor(1.0,0.0,1.0);
	else if(type == Monitor)transforms->setColor(0.2,0.2,0.2);
	else if(type == RootNode)transforms->setColor(0.4, 0.4, 1.0);
	else if(type == MeshO) transforms->setColor(0.0,1.0,0.0);
	cout<<"Node '"<<name<<"' Created\n";
}

ObjectNode::~ObjectNode(){
	delete transforms; transforms = 0;
}

int
ObjectNode::childNum(ObjectNode* node){
	for(int i=0; i<children.size(); i++){
		if(children[i] == node) return i;
	}
}

void
ObjectNode::setRoot(){
	root = true;
}
void
ObjectNode::addChild(ObjectNode* node){
	children.push_back(node);
	node->setParent(this);
}

void
ObjectNode::setParent(ObjectNode* node){
	parent = node;
}

void
ObjectNode::deleteChild(ObjectNode* node){
	int i = this->childNum(node);
	children.erase(children.begin()+i);
}

void
ObjectNode::deleteAllChildren(){
	for(int i=0; i<children.size(); i++){
		if(children[i]->numChildren() == 0)
			this->deleteChild(children[i]);
		else
			children[i]->deleteAllChildren();
	}
}

bool 
ObjectNode::hasChild(ObjectNode* node){
	for(int i=0; i<children.size(); i++){
		if(children[i] == node) return true;
	}
	return false;
}

ObjectNode*
ObjectNode::nextChild(ObjectNode *currentChild){
	int childs = this->numChildren();
	if(childs>0){
		int num = this->childNum(currentChild);
		if(num+1 == childs)
			return this;
		else
			return children[num+1];
	}
	else{
		return this;
	}
}

void
ObjectNode::drawObject(int select){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	if(type != Light){
		glTranslated(transforms->getTransX(),transforms->getTransY(),transforms->getTransZ());
		glRotated(transforms->getAngleX(),1,0,0);
		glRotated(transforms->getAngleY(),0,1,0);
		glRotated(transforms->getAngleZ(),0,0,1);
		glScaled(transforms->getScaleX(),transforms->getScaleY(),transforms->getScaleZ());
	}
	else{
		glPushMatrix();
			glTranslated(transforms->getTransX(),transforms->getTransY(),transforms->getTransZ());
			glRotated(transforms->getAngleX(),1,0,0);
			glRotated(transforms->getAngleY(),0,1,0);
			glRotated(transforms->getAngleZ(),0,0,1);
			glScaled(transforms->getScaleX(),transforms->getScaleY(),transforms->getScaleZ());
			glGetDoublev(GL_MODELVIEW_MATRIX,mat[0]);
		glPopMatrix();
	}
	if(numChildren() == 0){
		drawMe(select);
	}
	else{
		for(int i=0; i<children.size(); i++){
			children[i]->drawObject(select);
		}
		drawMe(select);
	}
	glPopMatrix();
	
}

void
ObjectNode::drawMe(int select){
	if(type != Light && shape != Object){
		glGetDoublev(GL_MODELVIEW_MATRIX,mat[0]);
		
		/*std::cout<<"MAT NODE:\n"; 
		for(int i=0; i<16; i++){
			std::cout<<mat[i]<<" ";
		}
		std::cout<<"\n";*/
		GLfloat color[] = {transforms->getR(), transforms->getG(), transforms->getB(), 1.0};
		GLfloat color2[] = {transforms->getR2(), transforms->getG2(), transforms->getB2(), 1.0};
		
		/*if(type == Desk){
			if(selected && select == 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			drawDesk();
		}
		else */if(type == Lamp){ 
			if(selected && select == 2)
				drawLamp(transforms->getR2(), transforms->getG2(), transforms->getB2());
			else
				drawLamp(transforms->getR(), transforms->getG(), transforms->getB());
		}
		else if(type == Cabinet){ 
			if(selected && select == 2)
				drawCabinet(transforms->getR2(), transforms->getG2(), transforms->getB2());
			else
				drawCabinet(transforms->getR(), transforms->getG(), transforms->getB());
		}
		else if(type == Monitor){ 
			if(selected && select == 2){
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				drawMonitor(transforms->getR2(), transforms->getG2(), transforms->getB2());}
			else{
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				drawMonitor(transforms->getR(), transforms->getG(), transforms->getB());}
			
		}
		else if(type == Sphere){
			if(selected && select == 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			int list = makeUnitSphere();
			drawShape(list);
			/*GLfloat colorx[] = {1, 1, 1, 1.0};
			GLfloat colory[] = {0, 1, 0, 1.0};
			GLfloat colorz[] = {.5, .5, 1, 1.0};
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorz);
			glBegin(GL_LINES);
				glVertex3f(0,0,10);
				glVertex3f(0,0,-10);
			glEnd();
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colory);
			glBegin(GL_LINES);
				glVertex3f(0,10,0);
				glVertex3f(0,-10,0);
			glEnd();
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorx);
			glBegin(GL_LINES);
				glVertex3f(10,0,0);
				glVertex3f(-10,0,0);
			glEnd();*/
			
		}
		else if(type == Cube){
			GLfloat color[] = {transforms->getR(), transforms->getG(), transforms->getB(), 1.0};
			if(selected && select == 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			glutSolidCube(1.0f);
			/*GLfloat colorx[] = {1, 1, 1, 1.0};
			GLfloat colory[] = {0, 1, 0, 1.0};
			GLfloat colorz[] = {.5, .5, 1, 1.0};
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorz);
			glBegin(GL_LINES);
				glVertex3f(0,0,10);
				glVertex3f(0,0,-10);
			glEnd();
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colory);
			glBegin(GL_LINES);
				glVertex3f(0,10,0);
				glVertex3f(0,-10,0);
			glEnd();
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorx);
			glBegin(GL_LINES);
				glVertex3f(10,0,0);
				glVertex3f(-10,0,0);
			glEnd();*/

			
		}
		else if(type == Cylinder){
			if(selected && select == 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			int list = makeCylinder();
			drawShape(list);
		
		}
		else if(type == Half){
			if(selected && select == 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			int list = makeHalfSphere();
			drawShape(list);
		}
		else if(type == Disk){
			if(selected && select == 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			int list = makeDisk();
			drawShape(list);
			
		}
		else if(type == MeshO){
			if(selected && select == 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			myMesh->drawMesh();
		}
		else if(type == RootNode){
		
			if(selected && select == 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			//glBindTexture(GL_TEXTURE_2D, texture[0]);
			drawPlane(texture[0]);
		}
	}

}

void
ObjectNode::cloneChildren(ObjectNode* newNodeParent){
	for(int i=0;i<numChildren();i++){
		ObjectNode* newNode = new ObjectNode(children[i]->nodeName(),children[i]->getObject(),children[i]->getShape());
		newNodeParent->addChild(newNode);
		newNode->transforms->setColor(children[i]->transforms->getR(),children[i]->transforms->getG(),children[i]->transforms->getB());
		newNode->transforms->setAngleX(children[i]->transforms->getAngleX());
		newNode->transforms->setAngleY(children[i]->transforms->getAngleY());
		newNode->transforms->setAngleZ(children[i]->transforms->getAngleZ());
		newNode->transforms->setScaleX(children[i]->transforms->getScaleX());
		newNode->transforms->setScaleY(children[i]->transforms->getScaleY());
		newNode->transforms->setScaleZ(children[i]->transforms->getScaleZ());
		newNode->transforms->setTransX(children[i]->transforms->getTransX()+2);
		newNode->transforms->setTransY(children[i]->transforms->getTransY());
		newNode->transforms->setTransZ(0);

		if(children[i]->numChildren() > 0)
			children[i]->cloneChildren(newNode);
	}
}

// Loads A Bitmap Image
AUX_RGBImageRec*
ObjectNode::LoadBMP(char* Filename){
	FILE* pFile = NULL;										// File Handle

	if (!Filename){										// Make Sure A Filename Was Given
		return NULL;									// If Not Return NULL
	}

	pFile=fopen(Filename,"r");							// Check To See If The File Exists

	if (pFile){											// Does The File Exist?
		fclose(pFile);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

int 
ObjectNode::LoadGLTextures(char* Filename, int num){							// Load Bitmaps And Convert To Textures

	int Status=false;									// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0]=LoadBMP(Filename)){
		Status=true;									// Set The Status To TRUE

		cout<<"Node: "<<glGetError()<<endl;
		glGenTextures(1, &texture[num]);					// Create The Texture
		cout<<"Node: "<<glGetError()<<endl;

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[num]);
		
		
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// when texture area is small, bilinear filter the closest mipmap
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
		// when texture area is large, bilinear filter the first mipmap
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		

	}

	//if (TextureImage[0]){									// If Texture Exists
	//	if (TextureImage[0]->data){							// If Texture Image Exists
	//		free(TextureImage[0]->data);					// Free The Texture Image Memory
	//	}
	//	free(TextureImage[0]);								// Free The Image Structure
	//}
	return Status;										// Return The Status
}



//Chair Constructor
void 
ObjectNode::chair_construct(){
	ObjectNode* seat = new ObjectNode("Cube",6,2);
	seat->transforms->setTransY(0.9);
	seat->transforms->setScaleY(0.2);
	children.push_back(seat);
	seat->setParent(this);

	ObjectNode* backrest = new ObjectNode("Cube",6,2);
	backrest->transforms->setTransX(-0.4);
	backrest->transforms->setTransY(1.5);
	backrest->transforms->setScaleX(0.2);
	children.push_back(backrest);
	backrest->setParent(this);

	ObjectNode* leg1 = new ObjectNode("Cube",6,2);
	leg1->transforms->setTransX(0.4);
	leg1->transforms->setTransY(0.4);
	leg1->transforms->setTransZ(0.4);
	leg1->transforms->setScaleX(0.2);
	leg1->transforms->setScaleY(0.8);
	leg1->transforms->setScaleZ(0.2);
	children.push_back(leg1);
	leg1->setParent(this);

	ObjectNode* leg2 = new ObjectNode("Cube",6,2);
	leg2->transforms->setTransX(-0.4);
	leg2->transforms->setTransY(0.4);
	leg2->transforms->setTransZ(0.4);
	leg2->transforms->setScaleX(0.2);
	leg2->transforms->setScaleY(0.8);
	leg2->transforms->setScaleZ(0.2);
	children.push_back(leg2);
	leg2->setParent(this);

	ObjectNode* leg3 = new ObjectNode("Cube",6,2);
	leg3->transforms->setTransX(-0.4);
	leg3->transforms->setTransY(0.4);
	leg3->transforms->setTransZ(-0.4);
	leg3->transforms->setScaleX(0.2);
	leg3->transforms->setScaleY(0.8);
	leg3->transforms->setScaleZ(0.2);
	children.push_back(leg3);
	leg3->setParent(this);

	ObjectNode* leg4 = new ObjectNode("Cube",6,2);
	leg4->transforms->setTransX(0.4);
	leg4->transforms->setTransY(0.4);
	leg4->transforms->setTransZ(-0.4);
	leg4->transforms->setScaleX(0.2);
	leg4->transforms->setScaleY(0.8);
	leg4->transforms->setScaleZ(0.2);
	children.push_back(leg4);
	leg4->setParent(this);
}

//Desk Constructor
void 
ObjectNode::desk_construct(){
	ObjectNode* top = new ObjectNode("Cube",6,2);
	top->transforms->setTransY(1.4);
	top->transforms->setScaleX(2.0);
	top->transforms->setScaleY(0.3);
	top->transforms->setScaleZ(4.0);
	children.push_back(top);
	top->setParent(this);

	ObjectNode* leg1 = new ObjectNode("Cube",6,2);
	leg1->transforms->setTransX(0.85);
	leg1->transforms->setTransY(0.625);
	leg1->transforms->setTransZ(1.85);
	leg1->transforms->setScaleX(0.3);
	leg1->transforms->setScaleY(1.25);
	leg1->transforms->setScaleZ(0.3);
	children.push_back(leg1);
	leg1->setParent(this);

	ObjectNode* leg2 = new ObjectNode("Cube",6,2);
	leg2->transforms->setTransX(-0.85);
	leg2->transforms->setTransY(0.625);
	leg2->transforms->setTransZ(1.85);
	leg2->transforms->setScaleX(0.3);
	leg2->transforms->setScaleY(1.25);
	leg2->transforms->setScaleZ(0.3);
	children.push_back(leg2);
	leg2->setParent(this);

	ObjectNode* leg3 = new ObjectNode("Cube",6,2);
	leg3->transforms->setTransX(-0.85);
	leg3->transforms->setTransY(0.625);
	leg3->transforms->setTransZ(-1.85);
	leg3->transforms->setScaleX(0.3);
	leg3->transforms->setScaleY(1.25);
	leg3->transforms->setScaleZ(0.3);
	children.push_back(leg3);
	leg3->setParent(this);

	ObjectNode* leg4 = new ObjectNode("Cube",6,2);
	leg4->transforms->setTransX(0.85);
	leg4->transforms->setTransY(0.625);
	leg4->transforms->setTransZ(-1.85);
	leg4->transforms->setScaleX(0.3);
	leg4->transforms->setScaleY(1.25);
	leg4->transforms->setScaleZ(0.3);
	children.push_back(leg4);
	leg4->setParent(this);
}