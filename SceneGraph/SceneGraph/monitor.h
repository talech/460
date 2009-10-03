#ifndef MONITOR_H
#define MONITOR_H

static void drawMonitor(float r, float g, float b){
	GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat blue[] = {0.6, 0.6, 1.0, 1.0};
	GLfloat color[] = {r, g, b, 1.0};
	
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	
	/*vec4 v1(5,0,5,1);
	vec4 v2(5,0,-5,1);
	vec4 v3(-5,0,-5,1);
	vec4 normal = getNormal(v1,v2,v3);
	normal = normal * (-1);
	glNormal3f(normal[0],normal[1],normal[2]);*/
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glBindTexture(GL_TEXTURE_2D, texture);
	
	

	glBegin(GL_QUADS);
        glTexCoord2f(1,0); glVertex3f(-0.35,.8,0.07);
        glTexCoord2f(0,0); glVertex3f(.35,.8,0.07);
        glTexCoord2f(0,1); glVertex3f(.35,1.2,0.07);
        glTexCoord2f(1,1); glVertex3f(-0.35,1.2,0.07);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	glPushMatrix();
	glTranslated(0,1,0);
	glScaled(1.7,1.2,.25);
	glutSolidCube(0.5f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,.7,0);
	glScaled(.25,.25,.25);
	glPushMatrix();
		glTranslated(0,-0.78,0);
		glRotated(90,1,0,0);
		int list1 = makeDisk();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		drawShape(list1);
	glPopMatrix();
	
	glPushMatrix();
		
		glRotated(90,1,0,0);
		glScaled(0.2, 0.2, .2);
		int list2 = makeCylinder();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		drawShape(list2);
	glPopMatrix();
	glPopMatrix();
	

	glPopMatrix();

}

#endif