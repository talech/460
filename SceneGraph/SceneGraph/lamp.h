/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#ifndef LAMP_H
#define LAMP_H

#include "shapes.h"


static void drawLamp(float r, float g, float b){
	GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat yellowish[] = {1.0, 1.0, 0.7, 1.0};
	GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat gray[] = {.6, .6, .6, 1.0};
	GLfloat color[] = {r,g,b,1.0};
	
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glTranslated(0,-4.45,0);
		glRotated(90,1,0,0);
		int list1 = makeDisk();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		drawShape(list1);
	glPopMatrix();
	
	glPushMatrix();
		glTranslated(0,-0.45,0);
		glRotated(90,1,0,0);
		glScaled(0.2, 0.2, 1);
		int list2 = makeCylinder();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		drawShape(list2);
	glPopMatrix();

	int list3 = makeHalfSphere();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellowish);
	drawShape(list3);

	

}

#endif