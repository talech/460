
/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#ifndef OBJECTS_H
#define OBJECTS_H

#include <iostream>
#include "chair.h"
#include "cabinet.h"
#include "lamp.h"
#include "desk.h"
#include "shapes.h"
#include "monitor.h"

static void drawPlane(GLuint texture){
	GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat blue[] = {0.6, 0.6, 1.0, 1.0};
	GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
	
	glMatrixMode(GL_MODELVIEW);
			
	
	/*glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);*/

	glPushMatrix();
	
	vec4 v1(5,0,5,1);
	vec4 v2(5,0,-5,1);
	vec4 v3(-5,0,-5,1);
	vec4 normal = getNormal(v1,v2,v3);
	normal = normal * (-1);
	glNormal3f(normal[0],normal[1],normal[2]);
	/*glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture);*/
	
	
	//std::cout<<glGetIntegerv(GL_TEXTURE_2D_BINDING,texture)<<std::endl;

	glBegin(GL_QUADS);
        /*glTexCoord2f(1,0);*/ glVertex3f(5,0,5);
		/*glTexCoord2f(1,1);*/ glVertex3f(5,0,-5);
        /*glTexCoord2f(0,1);*/ glVertex3f(-5,0,-5);
        /*glTexCoord2f(0,0);*/ glVertex3f(-5,0,5);
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	
	/*glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	vec4 v1w3(5,0,5,1);
	vec4 v2w3(5,5,5,1);
	vec4 v3w3(5,5,-5,1);
	vec4 normalw3 = getNormal(v1w3,v2w3,v3w3);
	normalw3 = normalw3 * (-1);
	glNormal3f(normalw3[0],normalw3[1],normalw3[2]);
	glBegin(GL_QUADS);
        glVertex3f(5,0,5);
        glVertex3f(5,5,5);
        glVertex3f(5,5,-5);
        glVertex3f(5,0,-5);
	glEnd();*/
	
	
	
	/*vec4 v1w(5,0,-5,1);
	vec4 v2w(5,5,-5,1);
	vec4 v3w(-5,5,-5,1);
	vec4 normalw = getNormal(v1w,v2w,v3w);
	normalw = normalw * (-1);
	glNormal3f(normalw[0],normalw[1],normalw[2]);
	glBegin(GL_QUADS);
        glVertex3f(5,0,-5);
        glVertex3f(5,5,-5);
        glVertex3f(-5,5,-5);
        glVertex3f(-5,0,-5);
	glEnd();*/

	/*vec4 v1w2(-5,0,-5,1);
	vec4 v2w2(-5,5,-5,1);
	vec4 v3w2(-5,5,5,1);
	vec4 normalw2 = getNormal(v1w2,v2w2,v3w2);
	normalw2 = normalw2 * (-1);
	glNormal3f(normalw2[0],normalw2[1],normalw2[2]);
	glBegin(GL_QUADS);
        glVertex3f(-5,0,-5);
        glVertex3f(-5,5,-5);
        glVertex3f(-5,5,5);
        glVertex3f(-5,0,5);
	glEnd();*/

	glPopMatrix();

}

#endif