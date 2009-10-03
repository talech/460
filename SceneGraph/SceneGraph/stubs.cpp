#include <math.h>
#include "algebra3.h"
#include "Matrix.h"
#include "tests.h"
#include <vector>


using namespace std;

static bool SameSide(vec3 p1,vec3 p2, vec3 a,vec3 b){
	vec3 cp1 = (b-a)^(p1-a);
	vec3 cp2 = (b-a)^(p2-a);
	if ((cp1*cp2)>= 0) return true;
	else return false;
}

vec3 getNormal(vec3 vert1, vec3 vert2, vec3 vert3){
	vec3 a = vert1-vert2;
	vec3 b = vert3-vert2;
	vec3 res = a^b;
	res.normalize();
	/*vec4 result = vec4(res[0], res[1], res[2], 1);*/
	
	return res;
}

double Test_RaySphereIntersect( const double P0[3], const double V0[3], const double matrix[16],vec3& normOut, vec3& inPoint){
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in tests.h.
	vec4 p0(P0[0],P0[1],P0[2],1);
	vec4 v0(V0[0],V0[1],V0[2],0);
	vec4 p1;
	Matrix m(matrix);
	v0 = v0.normalize();
	float t = -1;
	if(m.InvertMatrix()){
		/*std::cout<<"DETERMINANT: "<<m.getDet()<<std::endl;
		for(int i=0; i<16; i++){
			std::cout<<m.getInverse(i)<<std::endl;
		}*/
		
		
		p1 = p0 + v0;
		p1[3] = 1;
		p0 = m.multiplyInverse(p0);
		p1 = m.multiplyInverse(p1);
		//cout<<"\n"<<"VECTOR P0\n";
		
		//for(int i=0; i<4; i++){
		//	//std::cout<<p0[i]<<" ";
		//}
		//std::cout<<"\n";
		//std::cout<<"VECTOR P1\n";
		
		//for(int i=0; i<4; i++){
		////	std::cout<<p1[i]<<" ";
		//}
		//std::cout<<"\n";
		//Perspective Division
		p0[0] = p0[0]/p0[3];
		p0[1] = p0[1]/p0[3];
		p0[2] = p0[2]/p0[3];
		p1[0] = p1[0]/p1[3];
		p1[1] = p1[1]/p1[3];
		p1[2] = p1[2]/p1[3];
		//recalculate v0
		v0 = p1 - p0;
		//std::cout<<"VECTOR V0\n";
		
		//for(int i=0; i<4; i++){
		////	std::cout<<v0[i]<<" ";
		//}
		//std::cout<<"\n";
		p0[3] = 0;
		
		//test for intersection
		//A ray with a known point of origin o=p0, and direction vector d=v0.
		//a sphere with a known centre at a point c and a known radius r 

		//Compute A, B and C coefficients
		float a = v0*v0;
		float b = 2*(v0*p0);
		float c = (p0*p0) - (.5*.5); // p0*p0 - r^2 (unit sphere so r = 1)

		/*std::cout<<"a = "<<a<<std::endl;
		std::cout<<"b = "<<b<<std::endl;
		std::cout<<"c = "<<c<<std::endl;*/
		//Find discriminant
	    float disc = (b * b) - (4 * a * c);
		/*std::cout<<"disc = "<<disc<<std::endl;*/

		// if discriminant is negative there are no real roots, so return 
	    // -1 as ray misses sphere
		if (disc < 0)
			return -1;
		float distSqrt = sqrt(disc);
		/*std::cout<<"distSqrt = "<<distSqrt<<std::endl;*/
		float q;
		//By quadratic formula we have
		if (b < 0)
			//dist = (-b - distSqrt)
			q = (-b - distSqrt)/2.0;
		else
			q = (-b + distSqrt)/2.0;

		/*std::cout<<"q = "<<q<<std::endl;*/
		// compute t0 and t1
		float t0 = q / a;
		float t1 = c / q;

	/*	std::cout<<"t0 = "<<t0<<std::endl;
		std::cout<<"t1 = "<<t1<<std::endl;*/

		// make sure t0 is smaller than t1
		if (t0 > t1){
			// if t0 is bigger than t1 swap them around
			float temp = t0;
			t0 = t1;
			t1 = temp;
		}

		// if t1 is less than zero, the object is in the ray's negative direction
		// and consequently the ray misses the sphere
		if (t1 < 0)
			return -1;

		// if t0 is less than zero, the intersection point is at t1
		if (t0 < 0)
		{
			t = t1;
			//std::cout<<"T = "<<t<<"\n"<<std::endl;
			vec3 rayStart = vec3(p0[0],p0[1],p0[2]);
			vec3 rayDirection = vec3(v0[0],v0[1],v0[2]);
			inPoint = rayStart + (rayDirection*t);
			normOut = inPoint;
			normOut.normalize();

			return t;
		}
		// else the intersection point is at t0
		else
		{
			t = t0;
			//std::cout<<"T = "<<t<<"\n"<<std::endl;
			vec3 rayStart = vec3(p0[0],p0[1],p0[2]);
			vec3 rayDirection = vec3(v0[0],v0[1],v0[2]);
			inPoint = rayStart + (rayDirection*t);
			normOut = inPoint;
			normOut.normalize();

			return t;
		}

	}
	else
		return -1;
}

double Test_RayPolyIntersect( const double P0[3], const double V0[3], const double p1[3], const double p2[3], const double p3[3], const double matrix[16],vec3& normOut,vec3& inPoint ){
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in tests.h.

	vec4 r0(P0[0],P0[1],P0[2],1);
	vec4 v0(V0[0],V0[1],V0[2],0);
	vec4 r1;
	vec3 rayStart;
	vec3 rayDirection;
	Matrix m(matrix);
	v0 = v0.normalize();
	float t = -1;
	if(m.InvertMatrix()){
		/*std::cout<<"DETERMINANT: "<<m.getDet()<<std::endl;
		for(int i=0; i<16; i++){
			std::cout<<m.getInverse(i)<<std::endl;
		}*/
		
		r1 = r0 + v0;
		r1[3] = 1;
		r0 = m.multiplyInverse(r0);
		r1 = m.multiplyInverse(r1);
		//std::cout<<"\n"<<"VECTOR r0\n";
		
		for(int i=0; i<4; i++){
			//std::cout<<r0[i]<<" ";
		}
		/*std::cout<<"\n";
		std::cout<<"VECTOR r1\n";
		
		for(int i=0; i<4; i++){
			std::cout<<r1[i]<<" ";
		}
		std::cout<<"\n";
		*///Perspective Division
		r0[0] = r0[0]/r0[3];
		r0[1] = r0[1]/r0[3];
		r0[2] = r0[2]/r0[3];
		r1[0] = r1[0]/r1[3];
		r1[1] = r1[1]/r1[3];
		r1[2] = r1[2]/r1[3];
		//recalculate v0
		v0 = r1 - r0;
		/*std::cout<<"VECTOR V0\n";
		
		for(int i=0; i<4; i++){
			std::cout<<v0[i]<<" ";
		}
		std::cout<<"\n";*/
		r0[3] = 0;

		rayStart = vec3(r0[0],r0[1],r0[2]);
		rayDirection = vec3(v0[0],v0[1],v0[2]);
		

		//test for intersection
		vec3 normal;
		normal = getNormal(vec3(p1[0],p1[1],p1[2]),vec3(p2[0],p2[1],p2[2]),vec3(p3[0],p3[1],p3[2]));
		normal = normOut;
		/*std::cout<<"NORMAL: ";
		for(int i=0; i<3; i++){
			std::cout<<normal[i]<<" ";
		}
		std::cout<<"\n";*/
			
		//test for ray plane intersection
		//t = (normal dot (PointOnPLANE - Raystart)) / (normal dot Raydirection)
		// If normal dot Raydirection = 0 then these two vectors are perpendicular 
		//(ray runs parallel to plane) and there will be no collision. Let t = -1
		if((normal * rayDirection)==0){
			t=-1;
		}
		else{
			t = (normal*(vec3(p1[0],p1[1],p1[2]) - rayStart))/(normal * rayDirection);
			
		}
	}
	//if intersection with plane, check if in triangle limits
	//this is done by comparing edges, ie, the point has to lie
	//to the same side of two edges and the opposite side of the 
	//other edge
	vec3 intersect = rayStart + (rayDirection*t); 
	inPoint = intersect;
	/*std::cout<<"Intersect: ";
	for(int i=0; i<3; i++){
		std::cout<<intersect[i]<<" ";
	}
	std::cout<<"\n";*/
	
	if(!(SameSide(intersect,vec3(p1[0],p1[1],p1[2]),vec3(p2[0],p2[1],p2[2]),vec3(p3[0],p3[1],p3[2]))&&
		SameSide(intersect,vec3(p2[0],p2[1],p2[2]),vec3(p1[0],p1[1],p1[2]),vec3(p3[0],p3[1],p3[2]))&&
		SameSide(intersect,vec3(p3[0],p3[1],p3[2]),vec3(p1[0],p1[1],p1[2]),vec3(p2[0],p2[1],p2[2])))) t=-1;

	//std::cout<<"T = "<<t<<"\n"<<std::endl;
	
	return t;
}

double Test_RayCubeIntersect( const double P0[3], const double V0[3], const double matrix[16], 
							 vec3& normOut, vec3& inPoint )
{
	// TODO fill this in so it calls your own ray-casting function.
	// See the documentation of this function in tests.h.

	vec4 p0(P0[0],P0[1],P0[2],1);
	vec4 v0(V0[0],V0[1],V0[2],0);
	vec4 p1;
	vec3 rayStart;
	vec3 rayDirection;
	Matrix m(matrix);
	v0 = v0.normalize();
	float ts[6];
	vec3 normals[6];
	float t = -1;
	bool tPos = false;
	if(m.InvertMatrix()){
		/*std::cout<<"DETERMINANT: "<<m.getDet()<<std::endl;
		for(int i=0; i<16; i++){
			std::cout<<m.getInverse(i)<<" ";
		}
		std::cout<<"\n";*/
		p1 = p0 + v0;
		p1[3] = 1;


		/*std::cout<<"\n"<<"POINT P0 before\n";
		
		for(int i=0; i<4; i++){
			std::cout<<p0[i]<<" ";
		}
		std::cout<<"\n";

		std::cout<<"\n"<<"POINT P1 before\n";
		
		for(int i=0; i<4; i++){
			std::cout<<p1[i]<<" ";
		}
		std::cout<<"\n";

		std::cout<<"VECTOR V0 before\n";
		
		for(int i=0; i<4; i++){
			std::cout<<v0[i]<<" ";
		}
		std::cout<<"\n";*/

		p0 = m.multiplyInverse(p0);
		p1 = m.multiplyInverse(p1);
		/*std::cout<<"\n"<<"POINT P0\n";
		
		for(int i=0; i<4; i++){
			std::cout<<p0[i]<<" ";
		}
		std::cout<<"\n";
		std::cout<<"POINT P1\n";
		
		for(int i=0; i<4; i++){
			std::cout<<p1[i]<<" ";
		}
		std::cout<<"\n";*/
		//Perspective Division
		p0[0] = p0[0]/p0[3];
		p0[1] = p0[1]/p0[3];
		p0[2] = p0[2]/p0[3];
		p1[0] = p1[0]/p1[3];
		p1[1] = p1[1]/p1[3];
		p1[2] = p1[2]/p1[3];
		//recalculate v0
		v0 = p1 - p0;
		/*std::cout<<"VECTOR V0\n";
		
		for(int i=0; i<4; i++){
			std::cout<<v0[i]<<" ";
		}
		std::cout<<"\n";*/
		p0[3] = 0;

		rayStart = vec3(p0[0],p0[1],p0[2]);
		rayDirection = vec3(v0[0],v0[1],v0[2]);
		
		//test for intersection
		//vertices of unit cube
		vector<vec3> vertices;
		vertices.push_back(vec3(0.5,-0.5,0.5));
		vertices.push_back(vec3(0.5,0.5,0.5));
		vertices.push_back(vec3(-0.5,-0.5,0.5));
		vertices.push_back(vec3(-0.5,0.5,0.5));
		vertices.push_back(vec3(-0.5,-0.5,-0.5));
		vertices.push_back(vec3(-0.5,0.5,-0.5));
		vertices.push_back(vec3(0.5,-0.5,-0.5));
		vertices.push_back(vec3(0.5,0.5,-0.5));
		
		for(int f=0; f<11; f++){
			vec3 normal;
			if(f==6)		normal = getNormal(vertices[f],vertices[f+1],vertices[1]);
			else if(f==8)	normal = getNormal(vertices[6],vertices[0],vertices[2]);
			else if(f==10)	normal = getNormal(vertices[1],vertices[7],vertices[5]);
			else			normal = getNormal(vertices[f],vertices[f+1],vertices[f+3]);
			/*
			std::cout<<"NORMAL: ";
			for(int i=0; i<3; i++){
				std::cout<<normal[i]<<" ";
			}
			std::cout<<"\n";*/
			
			//test for ray plane intersection
			//t = (normal dot (PointOnPLANE - Raystart)) / (normal dot Raydirection)
			// If normal dot Raydirection = 0 then these two vectors are perpendicular 
			//(ray runs parallel to plane) and there will be no collision. Let t = -1
			if((normal * rayDirection)==0){
				if(f==8){
					ts[4] = -1;
					normals[4] = normal;
				}
				else if(f==10){
					ts[5] =  -1;
					normals[5] = normal;
				}
				else{
					ts[f/2]= -1;
					normals[f/2] = normal;
				}
			}
			else{
				if(f==8){
					ts[4] = (normal*(vertices[6] - rayStart))/(normal * rayDirection);
					normals[4] = normal;
				}
				else if(f==10){
					ts[5] = (normal*(vertices[1] - rayStart))/(normal * rayDirection);
					normals[5] = normal;
				}
				else{
					ts[f/2] = (normal*(vertices[f] - rayStart))/(normal * rayDirection);
					normals[f/2] = normal;
				}
			}

			f++;
		}
	}
	//if intersection with plane, check if in square limits
	//then take the smalles positive t if no intersections take largest 
	//negative t
	for(int i=0; i<6; i++){
		float tempT;
		vec3 intersect = rayStart + (rayDirection*ts[i]); 
		float x = fabs(intersect[0]);
		float y = fabs(intersect[1]);
		float z = fabs(intersect[2]);
		float e = 0.501;
		
		//std::cout<<"x: "<<x<<" y: "<<y<<" z: "<<z<<" ts["<<i<<"]: "<<ts[i]<<std::endl;
		
		if(ts[i] >= 0){			
			if((x < e)&&(y < e)&&(z < e)){
				tempT = ts[i];
				if(!tPos){
					t = tempT;
					tPos = true;
					normOut = normals[i];
					inPoint = intersect;
				}
				else{
					if(tempT<t){
						t = tempT;
						normOut = normals[i];
						inPoint = intersect;
					}
				}

			}
		}
		else{
			if(!tPos){
				if(fabs(ts[i])<fabs(t)){
					t = ts[i];
					normOut = normals[i];
					inPoint = intersect;
				}
			}
		}
	}
	
	//std::cout<<"T = "<<t<<"\n"<<std::endl;
	//std::cout<<t<<" ";
	normOut = (-1)*normOut;
	return t;
}

double Test_RayPlaneIntersect(
	const double P0[3], const double V0[3], 
	const double p1[3], const double p2[3], const double p3[3],const double p4[3],
	const double matrix[16],vec3& normOut, vec3& inPoint){

	vec4 r0(P0[0],P0[1],P0[2],1);
	vec4 v0(V0[0],V0[1],V0[2],0);
	vec4 r1;
	vec3 rayStart;
	vec3 rayDirection;
	Matrix m(matrix);
	v0 = v0.normalize();
	vec3 normal;
	float t = -1;
	if(m.InvertMatrix()){
		/*std::cout<<"DETERMINANT: "<<m.getDet()<<std::endl;
		for(int i=0; i<16; i++){
			std::cout<<m.getInverse(i)<<" ";
		}
		std::cout<<"\n";*/
		r1 = r0 + v0;
		r1[3] = 1;


		/*std::cout<<"\n"<<"POINT P0 before\n";
		
		for(int i=0; i<4; i++){
			std::cout<<r0[i]<<" ";
		}
		std::cout<<"\n";

		std::cout<<"\n"<<"POINT P1 before\n";
		
		for(int i=0; i<4; i++){
			std::cout<<r1[i]<<" ";
		}
		std::cout<<"\n";

		std::cout<<"VECTOR V0 before\n";
		
		for(int i=0; i<4; i++){
			std::cout<<v0[i]<<" ";
		}
		std::cout<<"\n";*/

		r0 = m.multiplyInverse(r0);
		r1 = m.multiplyInverse(r1);
		/*std::cout<<"\n"<<"POINT P0\n";
		
		for(int i=0; i<4; i++){
			std::cout<<r0[i]<<" ";
		}
		std::cout<<"\n";
		std::cout<<"POINT P1\n";
		
		for(int i=0; i<4; i++){
			std::cout<<r1[i]<<" ";
		}
		std::cout<<"\n";*/
		//Perspective Division
		r0[0] = r0[0]/r0[3];
		r0[1] = r0[1]/r0[3];
		r0[2] = r0[2]/r0[3];
		r1[0] = r1[0]/r1[3];
		r1[1] = r1[1]/r1[3];
		r1[2] = r1[2]/r1[3];
		//recalculate v0
		v0 = r1 - r0;
		/*std::cout<<"VECTOR V0\n";
		
		for(int i=0; i<4; i++){
			std::cout<<v0[i]<<" ";
		}
		std::cout<<"\n";*/
		r0[3] = 0;

		rayStart = vec3(r0[0],r0[1],r0[2]);
		rayDirection = vec3(v0[0],v0[1],v0[2]);
		
		//test for intersection
		
		normal = getNormal(vec3(p1[0],p1[1],p1[2]),vec3(p2[0],p2[1],p2[2]),vec3(p3[0],p3[1],p3[2]));
			
		/*std::cout<<"NORMAL: ";
		for(int i=0; i<3; i++){
			std::cout<<normal[i]<<" ";
		}
		std::cout<<"\n";*/
			
		//test for ray plane intersection
		//t = (normal dot (PointOnPLANE - Raystart)) / (normal dot Raydirection)
		// If normal dot Raydirection = 0 then these two vectors are perpendicular 
		//(ray runs parallel to plane) and there will be no collision. Let t = -1
		if((normal * rayDirection)==0){
			t=-1;
		}
		else{
			t = (normal*(vec3(p1[0],p1[1],p1[2]) - rayStart))/(normal * rayDirection);
			// dist = (normal * rayDirection)
			
		}
	}
	//if intersection with plane, check if in square limits
	//this is done by comparing edges, ie, the point has to lie
	//to the same side of two edges and the opposite side of the 
	//other edge
	vec3 intersect = rayStart + (rayDirection*t); 
	inPoint = intersect;
	normOut = (-1)*normal;
	
	
	/*std::cout<<"Intersect: ";
	for(int i=0; i<3; i++){
		std::cout<<intersect[i]<<" ";
	}
	std::cout<<"\n";*/
	
	if(!(SameSide(intersect,vec3(p1[0],p1[1],p1[2]),vec3(p2[0],p2[1],p2[2]),vec3(p3[0],p3[1],p3[2]))&&
		SameSide(intersect,vec3(p2[0],p2[1],p2[2]),vec3(p1[0],p1[1],p1[2]),vec3(p3[0],p3[1],p3[2]))&&
		SameSide(intersect,vec3(p3[0],p3[1],p3[2]),vec3(p1[0],p1[1],p1[2]),vec3(p2[0],p2[1],p2[2])))){
			
			if(!(SameSide(intersect,vec3(p1[0],p1[1],p1[2]),vec3(p3[0],p3[1],p3[2]),vec3(p4[0],p4[1],p4[2]))&&
				SameSide(intersect,vec3(p3[0],p3[1],p3[2]),vec3(p1[0],p1[1],p1[2]),vec3(p4[0],p4[1],p4[2]))&&
				SameSide(intersect,vec3(p4[0],p4[1],p4[2]),vec3(p1[0],p1[1],p1[2]),vec3(p3[0],p3[1],p3[2])))){
					t=-1;
			}
	}

	//std::cout<<"T = "<<t<<"\n"<<std::endl;
	return t;
}


