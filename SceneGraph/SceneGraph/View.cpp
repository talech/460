/*
 * View.cpp
 *
 */

#include "View.h"
#include <iostream>
#include <cstring>
#include <stdio.h>

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

	if(e == FL_KEYUP){
		bool done = false;
		switch(Fl::event_key()){
			case FL_Shift_L:
				done = true;
				break;
			case FL_Shift_R:
				break;
		}
		std::cout<<Fl::event_text()<<std::endl;

		//decrease 'X'
		if(!done && strcmp(Fl::event_text(),"x") == 0)
			control->translate(-1,0,0);
		//decrease 'Y'
		else if(!done && strcmp(Fl::event_text(),"y") == 0)
			control->translate(0,-1,0);
		//decrease 'Z'
		else if(!done && strcmp(Fl::event_text(),"z") == 0)
			control->translate(0,0,-1);
		//decrease 'X'
		else if(!done && strcmp(Fl::event_text(),"j") == 0)
			control->scale(-.2,0,0);
		//decrease 'Y'
		else if(!done && strcmp(Fl::event_text(),"k") == 0)
			control->scale(0,-.2,0);
		//decrease 'Z'
		else if(!done && strcmp(Fl::event_text(),"l") == 0)
			control->scale(0,0,-.2);

		//decrease 'X'
		else if(!done && strcmp(Fl::event_text(),"u") == 0)
			control->rotate(-30,0,0);
		//decrease 'Y'
		else if(!done && strcmp(Fl::event_text(),"i") == 0)
			control->rotate(0,-30,0);
		//decrease 'Z'
		else if(!done && strcmp(Fl::event_text(),"o") == 0)
			control->rotate(0,0,-30);







		else{
			switch(Fl::event_key()){
				/*case 'd':
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
					break;*/
				case 'q':
					control->NextNode();
					break;
				//select first child
				case 's':
					control->s_firstChild();
					break;
				//select parent
				case 'w':
					control->s_parent();
					break;
				//select parent
				case 'a':
					control->s_prevSib();
					break;
				//select parent
				case 'd':
					control->s_nextSib();
					break;
				//create empty node
				case 'c':
					control->addNode("Node",13,1);
					break;
				//erase selected node
				case 'e':
					control->removeNode();
					break;
				//change to sphere
				case 'b':
					control->changeNodeType("Sphere",5,2);
					break;
				//change to cube
				case 'g':
					control->changeNodeType("Cube",6,2);
					break;
				//change to empty node
				case 'n':
					control->changeNodeType("Node",13,1);
					break;
				//increase x
				case 'x':
					control->translate(1,0,0);
					break;
				//increase y
				case 'y':
					control->translate(0,1,0);
					break;
				//increase 'z'
				case 'z':
					control->translate(0,0,1);
					break;
				//scale 'x'
				case 'j':
					control->scale(.2,0,0);
					break;
				//scale 'y'
				case 'k':
					control->scale(0,.2,0);
					break;
				//scale 'z'
				case 'l':
					control->scale(0,0,.2);
					break;
				//rotate 'x'
				case 'u':
					control->rotate(30,0,0);
					break;
				//rotate 'y'
				case 'i':
					control->rotate(0,30,0);
					break;
				//rotate 'z'
				case 'o':
					control->rotate(0,0,30);
					break;
			}	
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
