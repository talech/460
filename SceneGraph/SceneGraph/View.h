/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/
 /* View.h
 *
 * Subclass of glWindow that draws in 3D
 * and implementing the new Camera class
 *
   Overrides a few of the glWindow functions such as init() and draw()

   The mesh is rotated with:
	a-left
	s-down
	d-right
	w-up
   Zoom in is with 'i' and zoom out is with 'o'

   The scene is also rotated with mouse drag with the left mouse button.
   Zoom in and out is with mouse drag with the right mouse button.
 *
 */

#ifndef VIEW_H
#define VIEW_H

#include "glWindow.h"
#include "camera.h"
#include "Controller.h"
#include <Fl/Gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#include "objects.h"



class View : public glWindow{
private:	

	camera myCamera;
	Controller* control;
	float lOffX, lOffY, rOffX, rOffY;
	bool leftButton;
	

	void init(){ init3D(); }
	void init3D();
	void draw(){ 
		if(!valid()){
			valid(1);
			init3D();
		}

		updateCamera();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		control->draw();
	}
	void updateCamera();
	void drawCube();
	

	void resize(int x,int y,int w,int h);
	int handle(int e);
	int drawSphere();
	void drawEdit();

public:
	
	
	View(Controller* c) : glWindow(240,60,630,630){
		myCamera = camera();
		control = c;
	}

	void passEvent(int e);

};

#endif