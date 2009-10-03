/*
 * View.cpp
 *
 */

#include "View.h"
#include <iostream>

void View::init3D(){
	float l0_dif[] = {1.0f, 1.0f, 1.0f, 1.0f};
	float l0_amb[] = {0.2f, 0.2f, 0.2f, 0.2f};
	float l0_pos[] = {-5.0f, 10.0f, 10.0f, 0.0f};
	
	glViewport(0, 0, w(), h());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w()/(float)h(), .05, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
	glEnable(GL_TEXTURE_2D);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

	
	glShadeModel(GL_SMOOTH);

	
	control->loadTexture("parquet.bmp", 0);
	//cout<<"View1: "<<glGetError()<<endl;
	control->loadTexture("snoopy.bmp", 1);
	//cout<<"View2: "<<glGetError()<<endl;
	glGetError();

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//GLfloat smoky[] = {.5,.5,.5,1.0};
	//GLfloat somewhere[] = {-1,-1,-1,0};
	//GLfloat lightSpecular[] = {1,1,1,1};
	//glLightfv(GL_LIGHT0, GL_AMBIENT, smoky);
	//glLightfv(GL_LIGHT0, GL_POSITION, somewhere);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	


	
}

void View::updateCamera(){
	/*cout<<"View3: "<<glGetError()<<endl;*/
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(myCamera.eye[0],myCamera.eye[1],myCamera.eye[2], 
			myCamera.center[0],	myCamera.center[1],myCamera.center[2], 
			myCamera.up[0],myCamera.up[1],myCamera.up[2]);
	
	
}


int View::handle(int e){

	int ret = Fl_Gl_Window::handle(e);

	if(e == FL_KEYUP)
	{
		switch(Fl::event_key())
		{
			//case 'w':
				//myCamera.rotateUpDown(5);
				//redraw();
				//break;
			//case 's':
				//myCamera.rotateUpDown(-5);
				//break;
			case 'd':
				myCamera.rotateRightLeft(-2.5);
				break;
			case 'a':
				myCamera.rotateRightLeft(2.5);
				break;
			case 's':
				myCamera.zoom(1);
				break;
			case 'w':
				myCamera.zoom(-1);
				break;
			case 'n':
				control->NextNode();
				break;
		}
	}
	
	if(e == FL_PUSH)
	{
		if(Fl::event_button()==1)//leftclick
		{
			lOffX = Fl::event_x();
			lOffY = Fl::event_y();
			leftButton = true;
		}
		else if(Fl::event_button()==3)//rightclick
		{
			rOffX = Fl::event_x();
			rOffY = Fl::event_y();
			leftButton = false;
		}
		return 1;
	}
	else if(e==FL_RELEASE){
		return 1;
	}
	else if(e==FL_DRAG)
	{
		if(leftButton)//rotate
		{
			myCamera.rotateUpDown((Fl::event_y()-lOffY));
			myCamera.rotateRightLeft(-(Fl::event_x()-lOffX));
			lOffX = Fl::event_x();
			lOffY = Fl::event_y();
			redraw();
		}
		else//zoom
		{
			myCamera.zoom((Fl::event_y()-rOffY)/10);
			rOffY = Fl::event_y();
			redraw();
		}
		return 1;
	}

	redraw();
	return (ret);
}

void View::resize(int x,int y,int w,int h){
	Fl_Gl_Window::resize(x,y,w,h);
	glLoadIdentity();
	glViewport(x,y,w,h);
	glFrustum(-1,1,-1,1,1,100);
	redraw();
}

void View::passEvent(int e){
	handle(e);
}
