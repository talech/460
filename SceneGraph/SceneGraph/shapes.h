/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#ifndef SHAPES_H
#define SHAPES_H

static int makeUnitSphere(){
	int listID = glGenLists(1);
	GLUquadricObj* q = gluNewQuadric();
	glNewList(listID, GL_COMPILE);
	gluSphere(q, 0.5f, 16 , 16);
	glEndList();
	gluDeleteQuadric(q);
	return listID;
}

static int makeCylinder(){
	int listID = glGenLists(1);
	GLUquadricObj* q = gluNewQuadric();
	glNewList(listID, GL_COMPILE);
	gluCylinder(q, 0.5f, 0.5f, 4, 16, 16);
	glEndList();
	gluDeleteQuadric(q);
	return listID;
}

static int makeDisk(){
	int listID = glGenLists(1);
	GLUquadricObj* q = gluNewQuadric();
	glNewList(listID, GL_COMPILE);
	gluDisk(q, 0.1f,0.5f,16,16);
	glEndList();
	gluDeleteQuadric(q);
	return listID;
}



static int makeHalfSphere(){
	int listID = glGenLists(1);
	GLUquadricObj* q = gluNewQuadric();
	glNewList(listID, GL_COMPILE);

	GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
	
	/// set up clip plane
	double clip_plane1[]={0.0,-10.0,0.0,0.5};
	glClipPlane(GL_CLIP_PLANE0,clip_plane1);
	glEnable(GL_CLIP_PLANE0);
	// draw sphere
	gluSphere(q,0.5f,16,16);

	glDisable(GL_CLIP_PLANE0);
	
	glEndList();
	gluDeleteQuadric(q);
	
	
	return listID;
}

	
static void drawShape(int list){ 
	
	glCallList(list);
	
}

#endif