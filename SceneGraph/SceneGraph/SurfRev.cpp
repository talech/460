/*****************************
Tamara Levy
CIS 460
October 24, 2008
SceneGraph - Room Editor
Comment for GIT
******************************/

#include <iostream>
#include "SurfRev.h"

Surfrev::Surfrev(std::vector<vec3> p, int s, int p0){
	polyline = p;
	slices = s;
	points = p0;
}

vec4
Surfrev::getNormal(vec4 vert1, vec4 vert2, vec4 vert3){
	vec3 a = vec3((vert1-vert2)[0], (vert1-vert2)[1], (vert1-vert2)[2]);
	vec3 b = vec3((vert3-vert2)[0], (vert3-vert2)[1], (vert3-vert2)[2]);
	vec3 res = a^b;
	res = res/res.length();
	vec4 result = vec4(res[0], res[1], res[2], 1);
	
	return result;
}

//creates a Mesh with the appropriate values and returns its pointer
//calculates the rotation
Mesh*
Surfrev::createMesh(){
	Mesh* m = new Mesh(); //empty mesh
	float degrees = 360/slices;
	float angle = 0;
	vec3 Y(0,1,0);
	//inserts all points doing the rotation around the y-axis
	for(int i=0; i<slices; i++){
		for(int j=0; j<points; j++){
			vec3 v = rotation3D(Y,angle)*polyline[j];
			cout<<"i = "<<i<<" X = "<<v[0]<<" Y = "<<v[1] <<" Z = "<< v[2]<<endl;
			m->addVertex(v);
		}
		angle += degrees;
	}
	for(int i=0; i<(slices*points)-1;i++){			
		//finds normal for face that is going to be inserted to the mesh
		if(i<((slices*points)-(points+1))){
			int mod = (1+i)%points;
			if(mod != 0){
				/*cout<<"--------\nPoint: "<<i<<endl;
				cout<<"i+1: "<<i+1<<endl;
				cout<<"i+1+points: "<<i+1+points<<endl;
				cout<<"i+points: "<<i+points<<"\n"<<endl;
				cout<<(mod)<<" = Mod\n\n";*/
			}

			vec4 vert1(m->getVertex(i)[0],m->getVertex(i)[1],m->getVertex(i)[2],1);
			vec4 vert2(m->getVertex(i+1)[0],m->getVertex(i+1)[1],m->getVertex(i+1)[2],1);
			vec4 vert3(m->getVertex(i+points+1)[0],m->getVertex(i+points+1)[1],m->getVertex(i+points+1)[2],1);
			//check for final point that has  x = 0: triangle not square
			if(((i+2)%points) == 0 && m->getVertex(i+1)[0] == 0){
				vert3[0] = m->getVertex(i+points)[0];
				vert3[1] = m->getVertex(i+points)[1];
				vert3[2] = m->getVertex(i+points)[2];
			}
			
			
			vec4 n = getNormal(vert1,vert2,vert3);
			vec3 normal(n[0],n[1],n[2]);
		
			if(mod != 0){
				/*std::cout<<"Normal x = "<<normal[0]<<std::endl;
				std::cout<<"Normal y = "<<normal[1]<<std::endl;
				std::cout<<"Normal z = "<<normal[2]<<std::endl;*/
			}
			m->addNormal(normal);
			////creates the faces, normal index is = i, always have 4 vertices for a face if x != 0
			

			vec2 f1((double)i,(double)i);
			vec2 f2((double)i+1,(double)i);
			vec2 f3((double)points+i+1,(double)i);
			vec2 f4((double)points+i,(double)i);
			std::vector<vec2> face;


			if(((i+2)%points) == 0 && m->getVertex(i+1)[0] == 0){
				face.push_back(f4);
				face.push_back(f2);
				face.push_back(f1);
			}

			else{
				face.push_back(f2);
				face.push_back(f1);
				face.push_back(f4);
				face.push_back(f3);

			}
			
			
			if(mod != 0){
				//cout<<"add face: "<<i<<endl;
				m->addFace(face);
			}
		}
		//case: do last face
		else{
			int mod = (1+i)%points;
			int k = (points*slices);
			/*cout<<"Else Point: "<<i<<endl;
			cout<<"i+1: "<<i+1<<endl;
			cout<<"i+1+points: "<<i+1+points-k<<endl;
			cout<<"i+points: "<<i+points-k<<"\n"<<endl;
			cout<<(mod)<<" = Mod\n\n";*/
					
			vec4 vert1L(m->getVertex(i)[0],m->getVertex(i)[1],m->getVertex(i)[2],1);
			vec4 vert2L(m->getVertex(i+1)[0],m->getVertex(i+1)[1],m->getVertex(i+1)[2],1);
			vec4 vert3L(m->getVertex(i+points+1-k)[0],m->getVertex(i+points+1-k)[1],m->getVertex(i+points+1-k)[2],1);
			if(((i+2)%points) == 0 && m->getVertex(i+1)[0] == 0){
				vert3L[0] = m->getVertex(i+points-k)[0];
				vert3L[1] = m->getVertex(i+points-k)[1];
				vert3L[2] = m->getVertex(i+points-k)[2];
			}
			vec4 nL = getNormal(vert1L,vert2L,vert3L);
			vec3 normalL(nL[0],nL[1],nL[2]);
				
			/*std::cout<<"--------\nNormal x = "<<normal[0]<<std::endl;
			std::cout<<"Normal y = "<<normal[1]<<std::endl;
			std::cout<<"Normal z = "<<normal[2]<<std::endl;*/
			m->addNormal(normalL);
			//creates the faces, normal index is = i, always have 4 vertices for a face
			vec2 f1L((double)i,(double)i);
			vec2 f2L((double)i+1,(double)i);
			vec2 f3L((double)points+i+1-k,(double)i);
			vec2 f4L((double)points+i-k,(double)i);
			std::vector<vec2> faceL;
			faceL.push_back(f2L);
			faceL.push_back(f1L);
			faceL.push_back(f4L);
			faceL.push_back(f3L);
			
			
			if(mod != 0){
				//cout<<"add face: "<<i<<endl;
				m->addFace(faceL);
			}
		}
	}
		//check if there is an opening at the top or bottom to cap or not
	if(polyline[0][0] != 0){	//cap the bottom
		/*cout<<"X1 = "<<m->getVertex(0)[0]<<"  Y1 = "<<m->getVertex(0)[1]<<"  Z1 = "<<m->getVertex(points-1)[2]<<endl;
		cout<<"X2 = "<<m->getVertex((points))[0]<<"  Y2 = "<<m->getVertex((points))[1]<<"  Z2 = "<<m->getVertex((points))[2]<<endl;
		cout<<"X3 = "<<m->getVertex((points*2))[0]<<"  Y3 = "<<m->getVertex((points*2))[1]<<"  Z3 = "<<m->getVertex((points*2))[2]<<"\n"<<endl;*/

		vec4 vert1(m->getVertex(0)[0],m->getVertex(0)[1],m->getVertex(0)[2],1);
		vec4 vert2(m->getVertex(points)[0],m->getVertex(points)[1],m->getVertex(points)[2],1);
		vec4 vert3(m->getVertex(points*2)[0],m->getVertex(points*2)[1],m->getVertex(points*2)[2],1);
		vec4 n = getNormal(vert1,vert2,vert3);
		vec3 normal(n[0],n[1],n[2]);

		m->addNormal(normal);
		std::vector<vec2> face;
		for(int k=0; k<slices; k++){
			vec2 f((double)points*k,(double)m->lastNorm());
			face.push_back(f);
		}
		m->addFace(face);
	}
	
	if(polyline[points-1][0] != 0){	//cap the top
		/*cout<<"Top\nX1 = "<<m->getVertex(points-1)[0]<<"  Y1 = "<<m->getVertex(points-1)[1]<<"  Z1 = "<<m->getVertex(points-1)[2]<<endl;
		cout<<"X2 = "<<m->getVertex((points*2)-1)[0]<<"  Y2 = "<<m->getVertex((points*2)-1)[1]<<"  Z2 = "<<m->getVertex((points*2)-1)[2]<<endl;
		cout<<"X3 = "<<m->getVertex((points*3)-1)[0]<<"  Y3 = "<<m->getVertex((points*3)-1)[1]<<"  Z3 = "<<m->getVertex((points*3)-1)[2]<<"\n"<<endl;*/

		vec4 vert1(m->getVertex(points-1)[0],m->getVertex(points-1)[1],m->getVertex(points-1)[2],1);
		vec4 vert2(m->getVertex((points*2)-1)[0],m->getVertex((points*2)-1)[1],m->getVertex((points*2)-1)[2],1);
		vec4 vert3(m->getVertex((points*3)-1)[0],m->getVertex((points*3)-1)[1],m->getVertex((points*3)-1)[2],1);
		vec4 n = getNormal(vert1,vert2,vert3);
		n = n * (-1);
		vec3 normal(n[0],n[1],n[2]);

		m->addNormal(normal);
		std::vector<vec2> face;
		for(int k=1; k<slices+1; k++){
			vec2 f((double)(points*k)-1,(double)m->lastNorm());
			face.push_back(f);
		}
		m->addFace(face);
	}
	

	return m;

}