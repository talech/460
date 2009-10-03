#include "rayTracer.h"

Tracer::Tracer(ObjectNode *r){
	root = r;
}

void 
Tracer::setDimensions(int w, int h){
	width = w;
	height = h;
}

void 
Tracer::InitRender(){
	// screen plane in world space coordinates
	WX1 = -0.5, WX2 = 0.5, WY1 = 0.5, WY2 = SY = -0.5;
	DX = (WX2 - WX1)/width;
	DY = -(WY2 - WY1)/height; //we start with Y negative to write bmp 
}

void
Tracer::Render(){
	
	/*myfile.open ("example#3.txt");*/
	double mat[16];


	root->getMatrix(mat,0);
	
	/*myfile<<"MAT\n";	
	for(int i=0; i<16; i++){
		myfile<<mat[i]<<" ";}
	myfile << "\nStart.\n";
	*/
	char *file_out_name = "test#10.bmp";
	vec3 origin(0,0,0);
	for(int i=0; i<TRACEDEPTH; i++)
		smallestT[i] = -1;
	

	# define VERBOSE false

	  unsigned char *barray;
	  bool error;
	  unsigned char *garray;

	  unsigned char *indexb;
	  unsigned char *indexg;
	  unsigned char *indexr;
	  
	  int numbytes;
	  unsigned char *rarray;

	
	//  Allocate the memory.

	  numbytes = (width) * abs ( height ) * sizeof ( unsigned char );  

	  rarray = new unsigned char[numbytes];
	  garray = new unsigned char[numbytes];
	  barray = new unsigned char[numbytes];
	//
	//  Set the data.
	//  Note that BMP files go from "bottom" up, so we'll reverse the
	//  sense of "J" here to get what we want.
	//
	  indexr = rarray;
	  indexg = garray;
	  indexb = barray;


	

	for(int y=0; y<height; y++){
		
		SX = WX1;
		for(int x=0; x<width; x++){
			/*std::cout<<"SX: "<<SX<<"  ";
			std::cout<<"SY: "<<SY<<std::endl;*/
			vec3 color(0,0,0);
			vec3 dir = vec3(SX,SY,-1) - origin;
			/*std::cout<<"dir\n";	
			for(int i=0; i<3; i++){
				std::cout<<dir[i]<<" ";
			}
			std::cout<<"\n";*/
			color[0] = 0;
			color[1] = 0;
			color[2] = 0;
			
			RayTrace(origin, dir, color,root,0);

			if(smallestT[0] == -1){
				color[0] = 0;
				color[1] = 0;
				color[2] = 0;
				/*myfile<<" X: "<<x<<"  ";
				myfile<<"Y: "<<y<<"";
				myfile<<" SX: "<<SX<<"  ";
				myfile<<"SY: "<<SY<<"\n";*/
			}
		/*	else{ myfile<<" X: "<<x<<"  ";
				  myfile<<"Y: "<<y<<"";
				  myfile<<" SX: "<<SX<<"  ";
				  myfile<<"SY: "<<SY<<"\n";}*/
			*indexr = 255*color[0];
			*indexg = 255*color[1];
			*indexb = 255*color[2];
			SX+=DX;
			for(int i=0; i<TRACEDEPTH; i++)
				smallestT[i] = -1;

			indexr = indexr + 1;
			indexg = indexg + 1;
			indexb = indexb + 1;
			/*std::cout<<"\n";*/
		}
		//myfile<<"\n---------------\n";
		SY+=DY;
	}
	std::cout<<"DONE\n";
	//myfile << "End.\n";
	//myfile.close();


	//
	//  Write the data to a file.
	//
	  error = bmp_24_write ( file_out_name, width, height, rarray, garray, barray );

	  if ( error ){
		cout << "\n";
		cout << "BMP_24_WRITE_TEST - Fatal error!\n";
		cout << "  The test failed.\n";
		//return error;
	  }
	//
	//  Free the memory.
	//
	  /*delete [] rarray;
	  delete [] garray;
	  delete [] barray;*/

	  if ( VERBOSE )
	  {
		cout << "\n";
		cout << "BMP_24_WRITE_TEST:\n";
		cout << "  The test was successful.\n";
	  }

	  error = false;
	  //return error;
	# undef VERBOSE
}

void
Tracer::RayTrace(vec3 &origin, vec3 &dir, vec3 &color,ObjectNode* obj,int t_depth){
	
	if (t_depth < TRACEDEPTH){
		if(obj->numChildren() == 0){
			IntersectTest(origin,dir,color,obj,t_depth);
		}
		else{
			for(int j=0; j<obj->numChildren();j++){
				RayTrace(origin,dir,color,obj->getChild(j),t_depth);
			}
			IntersectTest(origin,dir,color,obj,t_depth);
		}
	}
	
}

bool
Tracer::RayTraceShadow(vec3 &origin, vec3 &dir,ObjectNode* obj){
	bool intersect = false;
	if(obj->numChildren() == 0){
		intersect = IntersectTestShadow(origin,dir,obj);
	}
	else{
		for(int j=0; j<obj->numChildren();j++){
			intersect = RayTraceShadow(origin,dir,obj->getChild(j));
			if(intersect) return true;
		}
		intersect = IntersectTestShadow(origin,dir,obj);
	}	
	return intersect;
}

void
Tracer::IntersectTest(vec3 &origin, vec3 &dir, vec3 &color,ObjectNode* obj,int t_depth){
	double mat[16];
	double o[3] = {origin[0],origin[1],origin[2]};
	double d[3] = {dir[0],dir[1],dir[2]};
	double t = -1;
	vec3 normal(0,0,0);
	vec3 point(0,0,0);

	obj->getMatrix(mat,0);
	
	/*std::cout<<"MAT\n";	
	for(int i=0; i<16; i++){
		std::cout<<mat[i]<<" ";
	}
	std::cout<<"\n";*/
	if(obj->getShape() == 2){
		//Sphere
		if(obj->getObject() == 5){
			t = Test_RaySphereIntersect(o,d,mat,normal,point);
		}
		//Cube
		else if(obj->getObject() == 6){
			t = Test_RayCubeIntersect(o,d,mat,normal,point);
		}
	}
	else{
		//Root = floor
		if(obj->getObject() == 0){
			double p1[3] = {5,0,5};
			double p2[3] = {5,0,-5};
			double p3[3] = {-5,0,-5};
			double p4[3] = {-5,0,5};
			double t1 = Test_RayPlaneIntersect(o,d,p1,p2,p3,p4,mat,normal,point);
			
			t = t1;
			/*if(t1>=0){
				color[0] = .35;
				color[1] = .18;
				color[2] = .07;
			}

			double p5[3] = {5,5,5};
			double p6[3] = {5,5,-5};
			double t2 = Test_RayPlaneIntersect(o,d,p1,p5,p6,p2,mat,normal,point);
			if(t2>=0 && t2<t) t = t2; 

			double p7[3] = {-5,5,-5};
			double t3 = Test_RayPlaneIntersect(o,d,p2,p6,p7,p3,mat,normal,point);
			if(t3>=0 && t3<t) t = t3;

			double p8[3] = {-5,5,5};
			double t4 = Test_RayPlaneIntersect(o,d,p3,p3,p8,p4,mat,normal,point);
			if(t4>=0 && t4<t) t = t4;

			if(t != t1){
				color[0] = obj->transforms->getR();
				color[1] = obj->transforms->getG();
				color[2] = obj->transforms->getB();
			}*/
		}
		//Meshes
		//Find bounding box, given by the max and min x, y and z
		//test for each of the planes until find one that intersects
		//no need to find the closest only if there is intersection or not
		//if there is at least one intersection then test for every 
		//polygon in the mesh, if no intersection t = -1
		else if(obj->getObject() == 10){
			vec3 min, max;
			obj->myMesh->findBoundingBox(max,min);
			double p1[3] = {max[0],min[1],max[2]};	double p2[3] = {max[0],max[1],max[2]};
			double p3[3] = {min[0],min[1],max[2]};	double p4[3] = {min[0],max[1],max[2]};
			double p5[3] = {max[0],min[1],min[2]};	double p6[3] = {max[0],max[1],min[2]};
			double p7[3] = {min[0],min[1],min[2]};	double p8[3] = {min[0],max[1],min[2]};
			double t1 = Test_RayPlaneIntersect(o,d,p1,p2,p4,p3,mat,normal,point);
			if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
			else{
				t1 = Test_RayPlaneIntersect(o,d,p5,p6,p2,p1,mat,normal,point);
				if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
				else{
					t1 = Test_RayPlaneIntersect(o,d,p7,p8,p6,p5,mat,normal,point);
					if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
					else{
						t1 = Test_RayPlaneIntersect(o,d,p3,p4,p8,p7,mat,normal,point);
						if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
						else{
							t1 = Test_RayPlaneIntersect(o,d,p2,p6,p8,p4,mat,normal,point);
							if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
							else{
								t1 = Test_RayPlaneIntersect(o,d,p3,p7,p5,p1,mat,normal,point);
								if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
								else{
									t = -1;
								}
							}
						}
					}
				}
			}
		}
		//Light
		else if(obj->getObject() == 12){
			t = Test_RaySphereIntersect(o,d,mat,normal,point);
		}
		
	}
	
	if(t>=0){
		//myfile<<"** T: "<<t;
		if(smallestT[t_depth] < 0)
			smallestT[t_depth] = t;
		if(t <= smallestT[t_depth]){
			smallestT[t_depth] = t;
			if(obj->getObject() == 5||obj->getObject() == 6
				||obj->getObject() == 0||obj->getObject() == 10){
				getColor(dir,color,normal,point,obj,t_depth);
			}
			else if(obj->getObject() == 12){
				color[0] = 1;
				color[1] = 1;
				color[2] = 1;
			}
			else{
				color[0] = obj->transforms->getR();
				color[1] = obj->transforms->getG();
				color[2] = obj->transforms->getB();
			}
		}
	}

	else{
	}
		
}

bool
Tracer::IntersectTestShadow(vec3 &origin, vec3 &dir,ObjectNode* obj){
	double mat[16];
	double o[3] = {origin[0],origin[1],origin[2]};
	double d[3] = {dir[0],dir[1],dir[2]};
	double t = -1;
	vec3 normal(0,0,0);
	vec3 point(0,0,0);

	obj->getMatrix(mat,0);
	
	if(obj->getShape() == 2){
		if(obj->getObject() == 5){
			t = Test_RaySphereIntersect(o,d,mat,normal,point);
		}
		else if(obj->getObject() == 6){
			t = Test_RayCubeIntersect(o,d,mat,normal,point);
		}
	}
	else{
		if(obj->getObject() == 0){
			double p1[3] = {5,0,5};
			double p2[3] = {5,0,-5};
			double p3[3] = {-5,0,-5};
			double p4[3] = {-5,0,5};
			double t1 = Test_RayPlaneIntersect(o,d,p1,p2,p3,p4,mat,normal,point);
			t = t1;
			/*if(t1>=0){
				color[0] = .35;
				color[1] = .18;
				color[2] = .07;
			}

			double p5[3] = {5,5,5};
			double p6[3] = {5,5,-5};
			double t2 = Test_RayPlaneIntersect(o,d,p1,p5,p6,p2,mat,normal,point);
			if(t2>=0 && t2<t) t = t2; 

			double p7[3] = {-5,5,-5};
			double t3 = Test_RayPlaneIntersect(o,d,p2,p6,p7,p3,mat,normal,point);
			if(t3>=0 && t3<t) t = t3;

			double p8[3] = {-5,5,5};
			double t4 = Test_RayPlaneIntersect(o,d,p3,p3,p8,p4,mat,normal,point);
			if(t4>=0 && t4<t) t = t4;

			if(t != t1){
				color[0] = obj->transforms->getR();
				color[1] = obj->transforms->getG();
				color[2] = obj->transforms->getB();
			}*/
		}
		else if(obj->getObject() == 10){
			vec3 min, max;
			obj->myMesh->findBoundingBox(max,min);
			double p1[3] = {max[0],min[1],max[2]};	double p2[3] = {max[0],max[1],max[2]};
			double p3[3] = {min[0],min[1],max[2]};	double p4[3] = {min[0],max[1],max[2]};
			double p5[3] = {max[0],min[1],min[2]};	double p6[3] = {max[0],max[1],min[2]};
			double p7[3] = {min[0],min[1],min[2]};	double p8[3] = {min[0],max[1],min[2]};
			double t1 = Test_RayPlaneIntersect(o,d,p1,p2,p4,p3,mat,normal,point);
			if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
			else{
				t1 = Test_RayPlaneIntersect(o,d,p5,p6,p2,p1,mat,normal,point);
				if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
				else{
					t1 = Test_RayPlaneIntersect(o,d,p7,p8,p6,p5,mat,normal,point);
					if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
					else{
						t1 = Test_RayPlaneIntersect(o,d,p3,p4,p8,p7,mat,normal,point);
						if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
						else{
							t1 = Test_RayPlaneIntersect(o,d,p2,p6,p8,p4,mat,normal,point);
							if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
							else{
								t1 = Test_RayPlaneIntersect(o,d,p3,p7,p5,p1,mat,normal,point);
								if(t1>=0) t = obj->myMesh->Test_RayMeshIntersect(o,d,mat,normal,point);
								else{
									return false;
								}
							}
						}
					}
				}
			}
		}
		else if(obj->getObject() == 12){
			
			t = Test_RaySphereIntersect(o,d,mat,normal,point);
			if(t>=0) return false;

		}
	}
	
	if(t>=0)
		return true;

	else
		return false;
		
}

void
Tracer::getColor(vec3 &dir, vec3& color, vec3& normal,vec3& point,ObjectNode* obj,int t_depth){
	double mLight[16];
	root->getMatrix(mLight,0);
	Matrix mL(mLight);
	vec4 L0(0,0,0,1);
	L0 = mL.multiply(L0);
	vec3 L0_3(L0[0],L0[1],L0[2]);
	double mat[16];
	obj->getMatrix(mat,0);
	Matrix m(mat);
	float shade = 1;
	if(m.InvertMatrix()){
		L0 = m.multiplyInverse(L0);
		vec3 L(L0[0],L0[1],L0[2]);
		L = L - point;
		L.normalize();
		
		/*std::cout<<"Normal x : "<<"= "<<normal[0]<<std::endl;
		std::cout<<"Normal y : "<<"= "<<normal[1]<<std::endl;
		std::cout<<"Normal z : "<<"= "<<normal[2]<<"\n"<<std::endl;*/
		float d = L*normal;
		if(obj->getObject() == 10 && !obj->myMesh->isConvex()){
			if(d<0){
				d = fabs(d);
				d = 1-d;
			}
		}
		

		//calculations to determine shades
		vec4 pi(point[0],point[1],point[2],1);
		pi = m.multiply(pi);
		vec3 p0(pi[0],pi[1],pi[2]);
		vec3 light = L0_3 - p0;
		float tdist = light.length();
		light = light * (1.0/tdist);

		bool intersect = RayTraceShadow(p0+(light*EPSILON),light,root);
		if(intersect) shade = 0;
		
		// calculation to add diffuse component to ray color
		float diff = d * obj->transforms->getDiffuse()*shade;
		
		//calculations to add specular highlights
		vec4 r0(0,0,0,1);
		vec4 v0(dir[0],dir[1],dir[2],0);
		vec4 r1;
		r1 = r0 + v0;
		r0 = m.multiplyInverse(r0);
		r1 = m.multiplyInverse(r1);
		//recalculate v0
		v0 = r1 - r0;

		vec3 w_Dir(v0[0],v0[1],v0[2]);
		vec3 lR = L - (2.0 * d * normal);
		float dot = w_Dir*L;
		float spec = powf(dot,20)*obj->transforms->getSpecular()*shade;

		// add diffuse component to ray color
		if(obj->transforms->getDiffuse()>0 && d>0){
			color[0] = diff*obj->transforms->getR();
			color[1] = diff*obj->transforms->getG();
			color[2] = diff*obj->transforms->getB();
		}
		//add specular highlights
		if(obj->transforms->getSpecular()>0 && dot>0){
			color[0] += spec*obj->transforms->getR();
			color[1] += spec*obj->transforms->getG();
			color[2] += spec*obj->transforms->getB();
		}
		else if(d<0){
			color[0] = 0;
			color[1] = 0;
			color[2] = 0;
		}
		

		// calculate reflection
		float refl = obj->transforms->getReflection();
		if (refl > 0){
			vec4 N(normal[0],normal[1],normal[2],0);
			vec4 P(point[0],point[1],point[2],1);
			P = m.multiply(P);
			vec3 w_P(P[0],P[1],P[2]);
			if(m.removeTrans()){
				N = m.multiplyInverseTranspose(N);
				vec3 w_N(N[0],N[1],N[2]);
				dir.normalize();
				w_N.normalize();
				vec3 R = dir - ((2.0*(dir*w_N))* w_N);
				
				/*myfile<<"\n---------------------\nTRACE DEPTH: "<<t_depth<<endl;
				myfile<<"Object: "<<obj->getObject()<<endl;
				
				myfile<<"P: x = "<<point[0]<<" y = "<<point[1]<<" z = "<<point[2]<<endl;
				myfile<<"N: x = "<<normal[0]<<" y = "<<normal[1]<<" z = "<<normal[2]<<endl;

				myfile<<"\nR: x = "<<R[0]<<" y = "<<R[1]<<" z = "<<R[2]<<endl;*/
				if (t_depth < TRACEDEPTH) {
					vec3 rcol( 0, 0, 0 );
					float dist;
					vec3 orig = w_P + (R * EPSILON);

					/*myfile<<"w_N: x = "<<w_N[0]<<" y = "<<w_N[1]<<" z = "<<w_N[2]<<endl;
					myfile<<"orig: x = "<<orig[0]<<" y = "<<orig[1]<<" z = "<<orig[2]<<endl;*/
					
					
					RayTrace(orig,R,rcol,root,t_depth+1);					
					color[0] += refl * rcol[0] * obj->transforms->getR();
					color[1] += refl * rcol[1] * obj->transforms->getG();
					color[2] += refl * rcol[2] * obj->transforms->getB();
					//cout<<"RColor: r = "<<rcol[0]<<" g = "<<rcol[1]<<" b = "<<rcol[2]<<endl;
					//cout<<"Color: r = "<<color[0]<<" g = "<<color[1]<<" b = "<<color[2]<<endl;
					
				}
			}
		}


	}

}
