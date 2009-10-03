/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#ifndef CABINET_H
#define CABINET_H
#include "algebra3.h"

static vec4 getNormal(vec4 vert1, vec4 vert2, vec4 vert3){
	vec4 a = vec4((vert2-vert1)[0], (vert2-vert1)[1], (vert2-vert1)[2],1);
	vec4 b = vec4((vert3-vert1)[0], (vert3-vert1)[1], (vert3-vert1)[2],1);
	vec4 res = a^b;
	res = res/res.length();
	res = res * (-1);
	return res;
}

static void drawCabinet(float r, float g, float b){
	GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
	GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat color[] = {r,g,b,1.0};
	
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_NORMALIZE);
			
	// draw cube
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glScaled(1.0,2.0, 1.0);
	
	vec4 v1(0,0,0,1);
	vec4 v2(1,0,0,1);
	vec4 v3(1,1,0,1);
	vec4 normal = getNormal(v1,v2,v3);
	
	
	glBegin(GL_QUADS);
		glNormal3f(normal[0],normal[1],normal[2]);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,1,0);
        glVertex3f(0,1,0);
	glEnd();

	
	vec4 v4(1,1,1,1);
	vec4 v5(0,1,1,1);
	normal = getNormal(v3,v4,v5);
	
	glBegin(GL_QUADS);	
		glNormal3f(normal[0],normal[1],normal[2]);
        glVertex3f(0,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,1,1);
        glVertex3f(0,1,1);
	glEnd();

	vec4 v6(1,0,1,1);
	normal = getNormal(v5,v4,v6);
	
	glBegin(GL_QUADS);	
		glNormal3f(normal[0],normal[1],normal[2]);
        glVertex3f(0,1,1);
        glVertex3f(1,1,1);
        glVertex3f(1,0,1);
        glVertex3f(0,0,1);
	glEnd();


	normal = getNormal(v6,v2,v1);
	
	glBegin(GL_QUADS);			
		glNormal3f(normal[0],normal[1],normal[2]);
        glVertex3f(0,0,1);
        glVertex3f(1,0,1);
        glVertex3f(1,0,0);
        glVertex3f(0,0,0);
	glEnd();

	vec4 v7(0,1,0,1);
	normal = getNormal(v1,v7,v5);
	
	glBegin(GL_QUADS);			
		glNormal3f(normal[0],normal[1],normal[2]);
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
        glVertex3f(0,1,1);
        glVertex3f(0,0,1);
	glEnd();

	normal = getNormal(v4,v3,v2);
	
	glBegin(GL_QUADS);			
		glNormal3f(normal[0],normal[1],normal[2]);
		glVertex3f(1,1,1);
        glVertex3f(1,1,0);
        glVertex3f(1,0,0);
        glVertex3f(1,0,1);
	glEnd();

	glPopMatrix();

	
	//Divisions between cabinets
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glPushMatrix();
		glTranslated(0.0, .5, 0.0);
		glBegin(GL_LINES);
			glVertex3f(0,0,-0.01);
			glVertex3f(1,0,-0.01);
		glEnd();
		glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glPushMatrix();
		glTranslated(0.0, 1, 0.0);
		glBegin(GL_LINES);
			glVertex3f(0,0,-0.01);
			glVertex3f(1,0,-0.01);
		glEnd();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glPushMatrix();
		glTranslated(0.0, 1.5, 0.0);
		glBegin(GL_LINES);
			glVertex3f(0,0,-0.01);
			glVertex3f(1,0,-0.01);
		glEnd();
	glPopMatrix();

	//Handles to open cabinets
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glPushMatrix();
		glTranslated(0.375, .2, 0.0);
		glBegin(GL_QUADS);			
        glVertex3f(0,0,-0.01);
        glVertex3f(0,.1,-0.01);
        glVertex3f(.25,.1,-0.01);
        glVertex3f(.25,0,-0.01);
	glEnd();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glPushMatrix();
		glTranslated(0.375, 0.7, 0.0);
		glBegin(GL_QUADS);			
        glVertex3f(0,0,-0.01);
        glVertex3f(0,.1,-0.01);
        glVertex3f(.25,.1,-0.01);
        glVertex3f(.25,0,-0.01);
	glEnd();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glPushMatrix();
		glTranslated(0.375, 1.2, 0.0);
		glBegin(GL_QUADS);			
        glVertex3f(0,0,-0.01);
        glVertex3f(0,.1,-0.01);
        glVertex3f(.25,.1,-0.01);
        glVertex3f(.25,0,-0.01);
	glEnd();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glPushMatrix();
		glTranslated(0.375, 1.7, 0.0);
		glBegin(GL_QUADS);			
        glVertex3f(0,0,-0.01);
        glVertex3f(0,.1,-0.01);
        glVertex3f(.25,.1,-0.01);
        glVertex3f(.25,0,-0.01);
	glEnd();
	glPopMatrix();

}
#endif