/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#include "GUI.h"
#include <iostream>


// openGL3D main entry point
int main (int argc, char * const argv[]) {
	GUI g = GUI();
	Fl::run();

    return 1;
}

//
//
///********************************************************************/
///* This is some starter code for P1.  You can modify this file, except
//in areas where that is not recommended.  In its current state, this
//program will display a chair.*/
//
//
//#include <windows.h>
//#include <gl\gl.h>
//#include <gl\glu.h>
////#include "glut.h"
//#include <GL/glut.h>
//#include "chair.h"
//#include "cabinet.h"
//
//void init(void);
//void display(void);
//void keypressed(unsigned char, int, int);
//
//int main (int argc, char **argv)
//{
//	/****************************************************************/
//	unsigned char key;
//	int x,y;
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(600,600);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("Hello World");
//	init();
//	glutDisplayFunc(display);
//	glutKeyboardFunc(keypressed);
//
//	glutMainLoop();
//	return 0;
//	/***************************************************************/
//}
//
//void init(void)
//{
//	/********************************************************/
//	//You shouldn't need to change any of the code in this block
//	float l0_dif[] = {1.0f, 1.0f, 1.0f, 1.0f};
//	float l0_amb[] = {0.2f, 0.2f, 0.2f, 0.2f};
//	float l0_pos[] = {0.5f, 0.6f, 0.624f, 0.0f};
//	
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_NORMALIZE);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
//	/*******************************************************/
//
//	
//
//}
//
//void display(void)
//{
//	
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(40.0, 1.0, 0.5, 30.0);
//		
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	//gluLookAt(10.0, 10.0, 8.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
//	gluLookAt(0.0, 7.0, 10.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
//	
//	drawChair();
//	drawCabinet();
//	glutSwapBuffers();
//}
//
//void keypressed(unsigned char key, int x, int y)
////put code to handle key presses in here
//{
//}






//#include <iostream>
//#include <stdio.h>
//#include <GL/glut.h>
//#include <string>
//#include "controller.h"
//
//// all variables initialized to 1.0, meaning 
//// the triangle will initially be white
//float red=1.0; 
//float blue=1.0; 
//float green=1.0;
//float angle = 90;
//Controller* c;
//
//void processNormalKeys(unsigned char key, int x, int y) {
//	char str [80];
//	
//	if (key == 27) 
//		exit(0);
//
//	else if (key=='a') {
//		printf ("Enter the node name: ");
//		scanf ("%s",str); 
//		string str2(str);
//		c->addNode(str2);
//		c->PrintGraph();
//		
//	}
//	else if (key=='d') {
//		std::cout<<"Delete Selected Node\n";
//		c->removeNode();
//	}
//
//}
//
//void processSpecialKeys(int key, int x, int y) {
//
//	switch(key) {
//		case GLUT_KEY_UP :
//			//std::cout<<"Prev Node\n";
//			break;
//		case GLUT_KEY_DOWN :
//			c->NextNode();
//			break;
//
//	}
//}
//
//void renderScene(void) {
//	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
//	glColor3f(red,green,blue);
//
//	glBegin(GL_TRIANGLES);
//		glVertex3f(-0.5,-0.5,0.0);
//		glVertex3f(0.5,0.0,0.0);
//		glVertex3f(0.0,0.5,0.0);
//	glEnd();
//	
//
//	glutSwapBuffers();
//
//	
//}
//
//int main (int argc, char **argv) {
//	std::cout<<"Hello\n";
//	c = new Controller();
//	c->PrintGraph();
//	
//	glutInit(&argc, argv);
//	
//	// This is where we say that we want a double buffer
//	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
//	
//	glutInitWindowPosition(100,100);
//	glutInitWindowSize(320,320);
//	glutCreateWindow("Scene Graph");
//	glutDisplayFunc(renderScene);
//	glutIdleFunc(renderScene);
//	
//	
//	// here are the new entries
//	glutKeyboardFunc(processNormalKeys);
//	glutSpecialFunc(processSpecialKeys);	
//
//	// enable depth testing
//	glEnable(GL_DEPTH_TEST);
//	glutMainLoop();
//
//	std::cout<<"Goodbye\n";
//	return 0;
//}