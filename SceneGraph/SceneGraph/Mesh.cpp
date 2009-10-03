/*****************************
Tamara Levy
CIS 460
October 23, 2008
SceneGraph - Room Editor
******************************/


#include "Mesh.h"
#include <iostream>

Mesh::Mesh(){
	convex = true;
}

Mesh::Mesh(bool conv){
	convex = conv;
}

void
Mesh::addVertex(vec3 v){
	vertices.push_back(v);
}

void
Mesh::addNormal(vec3 vn){
	normals.push_back(vn);
	/*std::cout<<"Mesh: \nNormal x = "<<normals[normals.size()-1][0]<<std::endl;
	std::cout<<"Normal y = "<<normals[normals.size()-1][1]<<std::endl;
	std::cout<<"Normal z = "<<normals[normals.size()-1][2]<<"\n"<<std::endl;*/
}

void
Mesh::addFace(vector<vec2> f){
	faces.push_back(f);
	/*for(int i=0; i<f.size(); i++){
		std::cout<<"Face : vert: "<<f[i][0]<<" norm: "<<f[i][1]<<std::endl;
	}*/
	
}

//iterates faces to draw the corresponding mesh
void
Mesh::drawMesh(){
	
	GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_NORMALIZE);
	
			
	// draw mesh
	
	//std::cout<<"Faces = "<<faces.size()<<std::endl;
	for(int i=0; i<faces.size();i++){
		//std::cout<<"******\nFace i = "<<i<<std::endl;
		
		int index = faces[i][0][1];
		//vec3 c(0,0,0);
		
		glBegin(GL_POLYGON);
		/*std::cout<<"Normal x : "<<i<<"= "<<normals[index][0]<<std::endl;
		std::cout<<"Normal y : "<<i<<"= "<<normals[index][1]<<std::endl;
		std::cout<<"Normal z : "<<i<<"= "<<normals[index][2]<<"\n"<<std::endl;*/
		glNormal3f(normals[index][0],normals[index][1],normals[index][2]);
		//std::cout<<"Faces intern = "<<faces[1].size()<<std::endl;
		for(int j = 0; j<faces[i].size();j++){
			/*std::cout<<"Face j = "<<j<<std::endl;
			std::cout<<"Vector x : "<<i<<"= "<<vertices[faces[i][j][0]][0]<<std::endl;
			std::cout<<"Vector y : "<<i<<"= "<<vertices[faces[i][j][0]][1]<<std::endl;
			std::cout<<"Vector z : "<<i<<"= "<<vertices[faces[i][j][0]][2]<<"\n"<<std::endl;*/
			
			glVertex3f(vertices[faces[i][j][0]][0],vertices[faces[i][j][0]][1],vertices[faces[i][j][0]][2]);
			/*c[0] = c[0] + vertices[faces[i][j][0]][0];
			c[1] = c[1] + vertices[faces[i][j][0]][1];
			c[2] = c[2] + vertices[faces[i][j][0]][2];*/
		}
		glEnd();

		/*c[0] = c[0]/faces[i].size();
		c[1] = c[1]/faces[i].size();
		c[2] = c[2]/faces[i].size();*/
		//draw normals to debug
		/*glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
		glBegin(GL_LINES);
			glVertex3f(c[0],c[1],c[2]);
			glVertex3f(c[0]+normals[index][0],c[1]+normals[index][1],c[2]+normals[index][2]);
		glEnd();*/
	}

}

void
Mesh::findBoundingBox(vec3& max, vec3& min){
	max[0] = vertices[0][0];
	max[1] = vertices[0][1];
	max[2] = vertices[0][2];

	min[0] = vertices[0][0];
	min[1] = vertices[0][1];
	min[2] = vertices[0][2];

	for(int i = 0; i<3; i++){
		for(int j = 1; j<vertices.size(); j++){
			if(vertices[j][i] < min[i])		min[i] = vertices[j][i];
			if(vertices[j][i] > max[i])		max[i] = vertices[j][i];
		}
	}
}

float
Mesh::Test_RayMeshIntersect(const double P0[], const double V0[], 
			const double matrix[], vec3 &normOut, vec3 &inPoint){

	float t = -1;
	int smallIndex = faces[0][0][1];
	//double ps[4][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
	vector<vec3> ps;
	

	vec3 point;
	vec3 norm;

	for(int i=0; i<faces.size();i++){
		int index = faces[i][0][1];
		std::cout<<"\n\n------------------------\nINDEX i = "<<i<<std::endl;
		ps.clear();
		for(int j = 0; j<faces[i].size();j++){
			//std::cout<<faces[i].size()<<std::endl;
			std::cout<<"\nVertex j = "<<j<<std::endl;
			std::cout<<"Vector x : "<<i<<"= "<<vertices[faces[i][j][0]][0]<<std::endl;
			std::cout<<"Vector y : "<<i<<"= "<<vertices[faces[i][j][0]][1]<<std::endl;
			std::cout<<"Vector z : "<<i<<"= "<<vertices[faces[i][j][0]][2]<<"\n"<<std::endl;
			
			vec3 p(vertices[faces[i][j][0]][0],vertices[faces[i][j][0]][1],vertices[faces[i][j][0]][2]);
			ps.push_back(p);

		}
		
		float ti = -1;
		norm = normals[index];
		if(faces[i].size() == 3){
			double p1[3] = {ps[0][0],ps[0][1],ps[0][2]};
			double p2[3] = {ps[1][0],ps[1][1],ps[1][2]};
			double p3[3] = {ps[2][0],ps[2][1],ps[2][2]};
			/*cout<<"PS 0 : x = "<<p1[0]<<" y = "<<p1[1]<<" z = "<<p1[2]<<endl;
			cout<<"PS 1 : x = "<<p2[0]<<" y = "<<p2[1]<<" z = "<<p2[2]<<endl;
			cout<<"PS 2 : x = "<<p3[0]<<" y = "<<p3[1]<<" z = "<<p3[2]<<endl;*/
			
			ti = Test_RayPolyIntersect(P0,V0,p1,p2,p3,matrix,norm,point);
			
			
			//cout<<"ti: "<<ti<<endl;

		}
		else if(faces[i].size() == 4){
			double p1[3] = {ps[0][0],ps[0][1],ps[0][2]};
			double p2[3] = {ps[1][0],ps[1][1],ps[1][2]};
			double p3[3] = {ps[2][0],ps[2][1],ps[2][2]};
			double p4[3] = {ps[3][0],ps[3][1],ps[3][2]};
			/*cout<<"PS 0 : x = "<<p1[0]<<" y = "<<p1[1]<<" z = "<<p1[2]<<endl;
			cout<<"PS 1 : x = "<<p2[0]<<" y = "<<p2[1]<<" z = "<<p2[2]<<endl;
			cout<<"PS 2 : x = "<<p3[0]<<" y = "<<p3[1]<<" z = "<<p3[2]<<endl;
			cout<<"PS 3 : x = "<<p4[0]<<" y = "<<p4[1]<<" z = "<<p4[2]<<endl;*/
			ti = Test_RayPlaneIntersect(P0,V0,p1,p2,p3,p4,matrix,norm,point);
			//cout<<"ti: "<<ti<<endl;
		}
		else if(faces[i].size() > 4){
			double p1[3], p2[3], p3[3];
				p1[0] = ps[0][0];	p1[1] = ps[0][1];	p1[2] = ps[0][2];
				for(int n = 1; n<(ps.size()-1) && ti<0; n++){
					p2[0] = ps[n][0];	p2[1] = ps[n][1];	p2[2] = ps[n][2];
					p3[0] = ps[n+1][0];	p3[1] = ps[n+1][1];	p3[2] = ps[n+1][2];
						/*cout<<"\nPS 0 : x = "<<p1[0]<<" y = "<<p1[1]<<" z = "<<p1[2]<<endl;
						cout<<"PS 1 : x = "<<p2[0]<<" y = "<<p2[1]<<" z = "<<p2[2]<<endl;
						cout<<"PS 2 : x = "<<p3[0]<<" y = "<<p3[1]<<" z = "<<p3[2]<<endl;*/
					ti = Test_RayPolyIntersect(P0,V0,p1,p2,p3,matrix,norm,point);	
				}
				
		}

		if(ti >= 0 && (t<0 || ti<t)){
			t = ti;
			smallIndex = index;
			inPoint = point;
		}
	}
	
	normOut = normals[smallIndex];
	
	/*std::cout<<"Normal x : "<<"= "<<normOut[0]<<std::endl;
	std::cout<<"Normal y : "<<"= "<<normOut[1]<<std::endl;
	std::cout<<"Normal z : "<<"= "<<normOut[2]<<"\n"<<std::endl;*/
	return t;
}