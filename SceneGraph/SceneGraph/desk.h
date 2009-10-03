/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#ifndef DESK_H
#define DESK_H

static	void drawDeskLeg(){
		glPushMatrix();
		glTranslated(0.0, 0.4, 0.0);
		glScaled(0.2, 0.8, 0.2);
		glutSolidCube(1.0f);
		glPopMatrix();
}

static void drawDesk(){	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScaled(2, 1.5, 4);


		glPushMatrix();
		glTranslated(0.4, 0.0, 0.4);
		drawDeskLeg();
		glPopMatrix();
		
		glPushMatrix();
		glTranslated(-0.4, 0.0, 0.4);
		drawDeskLeg();
		glPopMatrix();
		
		glPushMatrix();
		glTranslated(-0.4, 0.0, -0.4);
		drawDeskLeg();
		glPopMatrix();
		
		glPushMatrix();
		glTranslated(0.4, 0.0, -0.4);
		drawDeskLeg();
		glPopMatrix();
		
		// draw seat
		glPushMatrix();
		glTranslated(0.0, 0.9, 0.0);
		glScaled(1.0, 0.2, 1.0);
		glutSolidCube(1.0f);
		glPopMatrix();

	glPopMatrix();
		
}

#endif