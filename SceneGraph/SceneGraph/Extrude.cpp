/*****************************
Tamara Levy
CIS 460
October 24, 2008
SceneGraph - Room Editor
******************************/

#include "Extrude.h"
#include <iostream>

Extrude::Extrude(std::vector<vec3> p, float d, int s){
	polygon = p;
	distance = d;
	sides = s;
}

//compares adjacent edges to check for convexity
//since it is guaranteed that polygon will be in the xz plane
//the cross product of the edges will be (0,y,0), so
//we only care for y
bool
Extrude::isConvex(){
	bool convex = true;
	float w1 = 0;
	float w2 = 0;
	if(polygon.size()<3) return convex;
	for(int i = 0; i< polygon.size()-1; i++){
		vec3 p0, p1, p2, p3;
		//case that compares the last edge and the edge before
		if(i == polygon.size() - 3){
			p0 = polygon[i]; //get first edge endpoint from polygon
			p1 = polygon[i+1]; //get second edge endpoint from polygon
			p2 = polygon[i+2]; //get third edge endpoint from polygon
			p3 = polygon[0]; //get fourth edge endpoint from polygon
		}
		//case that compares the last edge and the first edge
		else if(i == polygon.size() - 2){
			p0 = polygon[i]; //get first edge endpoint from polygon
			p1 = polygon[i+1]; //get second edge endpoint from polygon
			p2 = polygon[0]; //get third edge endpoint from polygon
			p3 = polygon[1]; //get fourth edge endpoint from polygon
		}
		//case that compares any two edges in the polygon
		else{
			p0 = polygon[i]; //get first edge endpoint from polygon
			p1 = polygon[i+1]; //get second edge endpoint from polygon
			p2 = polygon[i+2]; //get third edge endpoint from polygon
			p3 = polygon[i+3]; //get fourth edge endpoint from polygon
		}
		
		// y of crossproduct(p1-p0, p2-p1)
		w1 = (((p1[0]-p0[0])*(p2[2]-p1[2]))-((p2[0]-p1[0])*(p1[2]-p0[2])));
		// y of crossproduct(p2-p1, p2,p3)
		w2 = (((p2[0]-p1[0])*(p3[2]-p2[2]))-((p3[0]-p2[0])*(p2[2]-p1[2])));
		if(!((w1 > 0 && w2 > 0) || (w1 < 0 && w2 < 0) || w1 == 0 || w2 == 0)){
			convex = false;
			break;
		}
	}
	return convex;
}


vec4
Extrude::getNormal(vec4 vert1, vec4 vert2, vec4 vert3){
	vec4 a = vec4((vert2-vert1)[0], (vert2-vert1)[1], (vert2-vert1)[2],1);
	vec4 b = vec4((vert3-vert1)[0], (vert3-vert1)[1], (vert3-vert1)[2],1);
	vec4 res = a^b;
	res = res/res.length();
	res = res * (-1);
	return res;
}

//creates a Mesh with the appropriate values and returns its pointer
//calculates the extrusion, and if it is convex polygon will be capped

Mesh*
Extrude::createMesh(){
	cout<<isConvex()<<" - True = "<<true<<endl;
	
	Mesh* m = new Mesh(isConvex()); //empty mesh
	vector<vec3> polygon_top(polygon);	//a copy of polygon
	
	
	//inserts polygon to mesh
	//so for polygon the index is k
	for(int j = 0; j< sides; j++){
		m->addVertex(polygon[j]);
	}
	//add y coordinate to polygon_top and inserts it to mesh
	//so for top polygon the index is k+sides
	for(int i = 0; i<sides; i++){
		polygon_top[i][1] = distance;
		m->addVertex(polygon_top[i]);
	}
	for(int k = 0; k<sides; k++){
		if(k<(sides-1)){
			//finds normal for face that is going to be inserted to the mesh
			vec4 vert1(polygon[k][0],polygon[k][1],polygon[k][2],1);
			vec4 vert2(polygon[k+1][0],polygon[k+1][1],polygon[k+1][2],1);
			vec4 vert3(polygon_top[k+1][0],polygon_top[k+1][1],polygon_top[k+1][2],1);
			vec4 n = getNormal(vert1,vert2,vert3);
			vec3 normal(n[0],n[1],n[2]);

			
			/*std::cout<<"--------\nNormal x = "<<normal[0]<<std::endl;
			std::cout<<"Normal y = "<<normal[1]<<std::endl;
			std::cout<<"Normal z = "<<normal[2]<<std::endl;*/
			m->addNormal(normal);
			//creates the faces, normal index is = k, always have 4 vertices for a face
			vec2 f1((double)k,(double)k);
			vec2 f2((double)k+1,(double)k);
			vec2 f3((double)sides+k+1,(double)k);
			vec2 f4((double)sides+k,(double)k);
			std::vector<vec2> face;
			face.push_back(f1);
			face.push_back(f2);
			face.push_back(f3);
			face.push_back(f4);
			m->addFace(face);
		}

		//case: need to do last one too
		if(k == (sides-1)){
			vec4 vert1L(polygon[k][0],polygon[k][1],polygon[k][2],1);
			vec4 vert2L(polygon[0][0],polygon[0][1],polygon[0][2],1);
			vec4 vert3L(polygon_top[0][0],polygon_top[0][1],polygon_top[0][2],1);
			vec4 nL = getNormal(vert1L,vert2L,vert3L);
			vec3 normalL(nL[0],nL[1],nL[2]);
			m->addNormal(normalL);
			//creates the faces, normal index is = k, always have 4 vertices for a face
			vec2 f1L((double)k,(double)k);
			vec2 f2L((double)0,(double)k);
			vec2 f3L((double)sides,(double)k);
			vec2 f4L((double)sides+k,(double)k);
			std::vector<vec2> faceL;
			faceL.push_back(f1L);
			faceL.push_back(f2L);
			faceL.push_back(f3L);
			faceL.push_back(f4L);
			m->addFace(faceL);
		}

	}

	//check if convex to cap or not
	if(isConvex()){
		std::vector<vec2> cap;
		std::vector<vec2> cap_top;
		//add the two normals at side and side+1
		vec4 vert1(polygon[0][0],polygon[0][1],polygon[0][2],1);
		vec4 vert2(polygon[1][0],polygon[1][1],polygon[1][2],1);
		vec4 vert3(polygon[2][0],polygon[2][1],polygon[2][2],1);
		vec4 n = getNormal(vert1,vert2,vert3);
		n = n*(-1);
		vec3 normal(n[0],n[1],n[2]);
		m->addNormal(normal);
		vec4 vert1_top(polygon_top[0][0],polygon_top[0][1],polygon_top[0][2],1);
		vec4 vert2_top(polygon_top[1][0],polygon_top[1][1],polygon_top[1][2],1);
		vec4 vert3_top(polygon_top[2][0],polygon_top[2][1],polygon_top[2][2],1);
		vec4 n_top = getNormal(vert1_top,vert2_top,vert3_top);
		vec3 normal_top(n_top[0],n_top[1],n_top[2]);
		m->addNormal(normal_top);
		//adds the faces, vertices for bottom cap = polygon(i)
		//for top cap = polygon_top(i+side)
		for(int i = 0; i<sides; i++){
			vec2 f((double)i,(double)sides);
			cap.push_back(f);
			vec2 f_top((double)i+sides,(double)sides+1);
			cap_top.push_back(f_top);
		}
		m->addFace(cap);
		m->addFace(cap_top);
	}
	
	return m;

}