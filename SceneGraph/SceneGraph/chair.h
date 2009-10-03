/**
 * Utility class for making a chair.
 * 
 * You don't have to put code for drawing an object in a separate class, 
 * as I've done here. Breaking this out into a separate class simply 
 * shows which code should not be changed as part of the assignment.
 */

static	void drawChairLeg()
	{
		glPushMatrix();
		glTranslated(0.0, 0.4, 0.0);
		glScaled(0.2, 0.8, 0.2);
		glutSolidCube(1.0f);
		glPopMatrix();
	}

static void drawChair()
	{
		//GLfloat light_blue[] = {0.6, 0.7, 1.0, 1.0};
		// the chair should be a nice light blue color
		//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, light_blue);
		
		glMatrixMode(GL_MODELVIEW);
		
		glPushMatrix();
		glTranslated(0.4, 0.0, 0.4);
		drawChairLeg();
		glPopMatrix();
		
		glPushMatrix();
		glTranslated(-0.4, 0.0, 0.4);
		drawChairLeg();
		glPopMatrix();
		
		glPushMatrix();
		glTranslated(-0.4, 0.0, -0.4);
		drawChairLeg();
		glPopMatrix();
		
		glPushMatrix();
		glTranslated(0.4, 0.0, -0.4);
		drawChairLeg();
		glPopMatrix();
		
		// draw seat
		glPushMatrix();
		glTranslated(0.0, 0.9, 0.0);
		glScaled(1.0, 0.2, 1.0);
		glutSolidCube(1.0f);
		glPopMatrix();
		
		// draw backrest
		glPushMatrix();
		glTranslated(-0.4, 1.5, 0.0);
		glScaled(0.2, 1.0, 1.0);
		glutSolidCube(1.0f);
		glPopMatrix();		
	}


