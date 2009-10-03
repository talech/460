/*****************************
Tamara Levy
CIS 460
October 23, 2008
SceneGraph - Room Editor
******************************/
/*****************************
parser.h
Reads .obj, .extrude, .surfrev files,
parses them and sets them in their corresponding format
to create a mesh
*******************************/

#ifndef PARSER_H
#define PARSER_H



#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "algebra3.h"
#include "Extrude.h"
#include "Surfrev.h"
#include "Mesh.h"
using namespace std;

//ParseOBJ Inspired by http://www.cs.kuleuven.ac.be/~ares/libobj/index.html
//Took some code snipets but simplified it for the class requierments
static Mesh* ParseOBJ(const std::string& filename){
	Mesh* m = new Mesh();
	string line;
	char c;
	
	ifstream ifs(filename.c_str());
	
	if(ifs.is_open()){
		cout <<"READ\n";
		while (ifs.good()){
			getline(ifs, line);
			//cout << line<<endl;
			istringstream stringstream(line);
			stringstream.unsetf(ios_base::skipws);

			stringstream >> std::ws;
			c = stringstream.peek();
			//cout<<c<<endl;
			if(c == '#'){}
			else{
				/*cout << line<<endl;*/
				std::string keyword;
				stringstream >> keyword;
				if(keyword == "v"){
					float x, y, z;
					char wspace_x, wspace_y, wspace_z;
					stringstream >> wspace_x >> ws >> x >> wspace_y >> ws >> y >> wspace_z >> ws >> z >> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x) || !isspace(wspace_y) || !isspace(wspace_z)) {
						cout << "Corrupted file\n";
						return m;
					}
					//cout<<"x = "<<x<<" y = "<<y<<" z = "<<z<<endl;
					vec3 v(x,y,z);
					m->addVertex(v);
				}
				else if(keyword == "vn"){
					float x, y, z;
					char wspace_x, wspace_y, wspace_z;
					stringstream >> wspace_x >> ws >> x >> wspace_y >> ws >> y >> wspace_z >> ws >> z >> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x) || !isspace(wspace_y) || !isspace(wspace_z)) {
						cout << "Corrupted file\n";
						return m;
					}
					//cout<<"x = "<<x<<" y = "<<y<<" z = "<<z<<endl;
					vec3 vn(x,y,z);
					m->addNormal(vn);
				}
				else if(keyword == "f"){
					string str("//");
					size_t found;
					int face, normal;
					string face_char, normal_char;
					
					vec2 face_vec;
					vector<vec2> face_array;
					
					while(stringstream) {
						string f;
						char wspace;
						stringstream >> wspace >>ws >> f;
						if (!stringstream)
							break;
						else if(!isspace(wspace)){
							cout << "Corrupted file\n";
							return m;
						}
						else{
							/*cout<<"f = "<< f <<endl;*/						
							found = f.find(str);
							if(found!=string::npos){
								face_char = f.substr(0,found);
								normal_char = f.substr(found+2);
								face = atoi(face_char.c_str());
								normal = atoi(normal_char.c_str());		
								face_vec[0] = (double)face-1;//subtract 1 for array index
								face_vec[1] = (double)normal-1;//subtract 1 for array index
								face_array.push_back(face_vec);
								//cout<<" "<<face<<"//"<<normal;
							}
							else{
								cout << "Corrupted file\n";
								return m;
							}
						}
					}
					cout<<"\n";
					m->addFace(face_array);
					
				}
			}
		}

		ifs.close();
	}
	else{
		cout << "Error opening file\n";
		return m;
	}

	return m;
}
static Mesh* ParseEXTRUDE(const std::string& filename){
	Mesh* m = new Mesh();
	string line;
	char c;
	float distance, points;
	vector<vec3> extr_v;
	
	ifstream ifs(filename.c_str());
	
	if(ifs.is_open()){
		cout <<"READ\n";

		getline(ifs, line);
		istringstream stringstream(line);
		stringstream.unsetf(ios_base::skipws);

		stringstream >> std::ws>>distance;

		getline(ifs, line);
		istringstream stringstream2(line);
		stringstream2.unsetf(ios_base::skipws);
		stringstream2 >> std::ws>>points;

		/*cout <<"DISTANCE: "<<distance<<endl;
		cout<<"POINTS: "<<points<<endl;*/

		while (ifs.good()){
			getline(ifs, line);
			/*cout << line<<endl;*/
			istringstream stringstream3(line);
			stringstream3.unsetf(ios_base::skipws);

			stringstream3 >> std::ws;

			float x, y, z;
			y=0;
			char wspace_x, wspace_z;
			stringstream3 >> x >> wspace_z >> ws >> z >> ws;
			if (!stringstream3)
				break;
			if (!stringstream3.eof()  || !isspace(wspace_z)) {
				cout << "Corrupted file\n";
				return m;
			}
			/*cout<<"x = "<<x<<" y = "<<y<<" z = "<<z<<endl;*/
			vec3 v(x,y,z);
			extr_v.push_back(v);

			//cout<<"\n";
			
		}

		Extrude* extrude = new Extrude(extr_v,distance,points);
		m = extrude->createMesh();
		ifs.close();
	}
	else{
		cout << "Error opening file\n";
		return m;
	}

	return m;
}
static Mesh* ParseSURFREV(const std::string& filename){
	Mesh* m = new Mesh();
	string line;
	char c;
	float slices, points;
	vector<vec3> surf_v;
	
	ifstream ifs(filename.c_str());
	
	if(ifs.is_open()){
		cout <<"READ\n";

		getline(ifs, line);
		istringstream stringstream(line);
		stringstream.unsetf(ios_base::skipws);

		stringstream >> std::ws>>slices;

		getline(ifs, line);
		istringstream stringstream2(line);
		stringstream2.unsetf(ios_base::skipws);
		stringstream2 >> std::ws>>points;

		/*cout <<"SLICES: "<<slices<<endl;
		cout<<"POINTS: "<<points<<endl;*/

		while (ifs.good()){
			getline(ifs, line);
			/*cout << line<<endl;*/
			istringstream stringstream3(line);
			stringstream3.unsetf(ios_base::skipws);

			stringstream3 >> std::ws;

			float x, y, z;
			z=0;
			char wspace_x, wspace_y;
			stringstream3 >> x >> wspace_y >> ws >> y >> ws;
			if (!stringstream3)
				break;
			if (!stringstream3.eof()  || !isspace(wspace_y)) {
				cout << "Corrupted file\n";
				return m;
			}
			/*cout<<"x = "<<x<<" y = "<<y<<" z = "<<z<<endl;*/
			vec3 v(x,y,z);
			surf_v.push_back(v);

			//cout<<"\n";
			
		}

		Surfrev* surf = new Surfrev(surf_v,slices,points);
		m = surf->createMesh();
		ifs.close();
	}
	else{
		cout << "Error opening file\n";
		return m;
	}

	return m;
}


static Mesh* ReadFile(const std::string& filename){
	size_t dot;
	string strO(".obj");
	string strE(".extrude");
	string strS(".surfrev");
	Mesh* m;

	dot = filename.find(strO);
	if(dot!=string::npos)
		m = ParseOBJ(filename);
	else{
		dot = filename.find(strE);
		if(dot!=string::npos)
			m = ParseEXTRUDE(filename);
		else{
			dot = filename.find(strS);
			if(dot!=string::npos)
				m = ParseSURFREV(filename);
			else{
				cout <<"Type of file not valid\n";
				m = new Mesh();
			}
		}
	}
	

	return m;
}






#endif