/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#ifndef GLWINDOW_H
#define GLWINDOW_H
/*
 * glWindow.h
 *
 * Basic wrapper class for Fl_Gl_Window
 * Modification of glDrawer.h and PointDrawer.h applied to FLTK
 */

#include <FL/Fl_Gl_Window.h>
#include <FL/gl.h>
#include <FL/Fl.h>
#include <windows.h>

class glWindow : public Fl_Gl_Window{
private:
	void init(){
		glLoadIdentity();
		glViewport(0,0,w(),h());
		glOrtho(-10, 10, -10, 10, -1, 1);
		clearBackground();
	}

	void draw(){
		if (!valid()){ 
			valid(1);
			init();
		}
	}
	
	void resize(int x,int y,int w,int h){
		Fl_Gl_Window::resize(x,y,w,h);
		glLoadIdentity();
		glViewport(0,0,w,h);
		glOrtho(-10,10,-10,10,-1,1);
	}
		
	int handle(int e){
		return Fl_Gl_Window::handle(e);
	}

public:
	glWindow(int x, int y, int w, int h) : Fl_Gl_Window(x,y,w,h){}
	
	
	friend void clearBackground(){
		glClearColor(0.0,0.0,0.0,0.0);      //Sets the bg color
		glClear(GL_COLOR_BUFFER_BIT);		//Clears the screen.
	}
};

#endif