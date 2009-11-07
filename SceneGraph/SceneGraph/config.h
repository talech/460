#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "algebra3.h"

using namespace std;

//global variables for raytracer status
//int RTSIZE = 0;
//int RTSTEP = 0;
//bool RTDONE = false;

class Config{
public:
	Config(){}
	char* file;
	vec2 resolution;
	vec3 eyePos;
	vec3 vDir;
	vec3 uVec;
	float fovy;
	vec3 lPos;
	vec3 lCol;
	vec3 aCol;
	vector<float> mat1;
	vector<float> mat2;
	vector<float> mat3;
	bool complete;
};

static Config* Open_Config(const std::string& filename){
	Config* tracerConfig = new Config();
	tracerConfig->complete = false;
	string line;
	char c;
	
	ifstream ifs(filename.c_str());
	
	if(ifs.is_open()){
		cout <<"READ\n";
		while (ifs.good()){
			getline(ifs, line);
			istringstream stringstream(line);
			stringstream.unsetf(ios_base::skipws);

			stringstream >> std::ws;
			c = stringstream.peek();
			if(c == '#'){}
			else{
				std::string keyword;
				stringstream >> keyword;
				if(keyword == "FILE"){
					//we know File should be followed by a string
					string name;
					char wspace_x;
					stringstream >> wspace_x >> ws >> name >> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					char* cName = new char[name.size() + 1];
					copy(name.begin(), name.end(), cName);
					cName[name.size()] = '\0';
					tracerConfig->file = cName;
				}
				else if(keyword == "RESO"){
					//RESO should be followed by x and y coords
					float x, y;
					char wspace_x, wspace_y;
					stringstream >> wspace_x >> ws >> x >> wspace_y >> ws >> y >> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x) || !isspace(wspace_y)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					vec2 rs(x,y);
					tracerConfig->resolution = rs;
				}
				else if(keyword == "EYEP"){
					//EYEP should be followed by x, y and z coords
					float x, y, z;
					char wspace_x, wspace_y, wspace_z;
					stringstream >> wspace_x >> ws >> x >> wspace_y >> ws >> y >> wspace_z >> ws >> z>> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x) || !isspace(wspace_y) || !isspace(wspace_z)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					vec3 ep(x,y,z);
					tracerConfig->eyePos = ep;
				}
				else if(keyword == "VDIR"){
					//VDIR should be followed by x, y and z coords
					float x, y, z;
					char wspace_x, wspace_y, wspace_z;
					stringstream >> wspace_x >> ws >> x >> wspace_y >> ws >> y >> wspace_z >> ws >> z>> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x) || !isspace(wspace_y) || !isspace(wspace_z)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					vec3 vd(x,y,z);
					tracerConfig->vDir = vd;
				}
				else if(keyword == "UVEC"){
					//UVEC should be followed by x, y and z coords
					float x, y, z;
					char wspace_x, wspace_y, wspace_z;
					stringstream >> wspace_x >> ws >> x >> wspace_y >> ws >> y >> wspace_z >> ws >> z>> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x) || !isspace(wspace_y) || !isspace(wspace_z)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					vec3 uv(x,y,z);
					tracerConfig->uVec = uv;
				}
				else if(keyword == "FOVY"){
					//FOVY should be followed by y degrees
					float y;
					char wspace_y;
					stringstream >> wspace_y >> ws >> y >> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_y)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					tracerConfig->fovy = y;
				}
				else if(keyword == "LPOS"){
					//LPOS should be followed by x, y and z coords
					float x, y, z;
					char wspace_x, wspace_y, wspace_z;
					stringstream >> wspace_x >> ws >> x >> wspace_y >> ws >> y >> wspace_z >> ws >> z>> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x) || !isspace(wspace_y) || !isspace(wspace_z)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					vec3 lp(x,y,z);
					tracerConfig->lPos = lp;
				}
				else if(keyword == "LCOL"){
					//LCOL should be followed by x, y and z coords
					float x, y, z;
					char wspace_x, wspace_y, wspace_z;
					stringstream >> wspace_x >> ws >> x >> wspace_y >> ws >> y >> wspace_z >> ws >> z>> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x) || !isspace(wspace_y) || !isspace(wspace_z)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					vec3 lc(x,y,z);
					tracerConfig->lCol = lc;
				}
				else if(keyword == "ACOL"){
					//ACOL should be followed by x, y and z coords
					float x, y, z;
					char wspace_x, wspace_y, wspace_z;
					stringstream >> wspace_x >> ws >> x >> wspace_y >> ws >> y >> wspace_z >> ws >> z>> ws;
					if (!stringstream || !stringstream.eof() || !isspace(wspace_x) || !isspace(wspace_y) || !isspace(wspace_z)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					vec3 ac(x,y,z);
					tracerConfig->aCol = ac;
				}
				else if(keyword == "MAT1"){
					//MAT1 should be followed by 8 values
					vector<float> m1;
					m1.resize(8);
					char wspace_0, wspace_1, wspace_2, wspace_3, wspace_4, wspace_5, wspace_6, wspace_7;
					stringstream >> wspace_0 >> ws >> m1[0] >> wspace_1 >> ws >> m1[1] 
					>> wspace_2 >> ws >> m1[2]>> wspace_3 >> ws >> m1[3]>> wspace_4 >> ws >> m1[4]
					>> wspace_5 >> ws >> m1[5]>> wspace_6 >> ws >> m1[6]>> wspace_7 >> ws >> m1[7]>> ws; 
					if (!stringstream || !stringstream.eof() || !isspace(wspace_0) || !isspace(wspace_1) || !isspace(wspace_2) ||
						!isspace(wspace_3) || !isspace(wspace_4) || !isspace(wspace_5) || !isspace(wspace_6)|| !isspace(wspace_7)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					tracerConfig->mat1 = m1;
				}
				else if(keyword == "MAT2"){
					//MAT2 should be followed by 8 values
					vector<float> m2;
					m2.resize(8);
					char wspace_0, wspace_1, wspace_2, wspace_3, wspace_4, wspace_5, wspace_6, wspace_7;
					stringstream >> wspace_0 >> ws >> m2[0] >> wspace_1 >> ws >> m2[1] 
					>> wspace_2 >> ws >> m2[2]>> wspace_3 >> ws >> m2[3]>> wspace_4 >> ws >> m2[4]
					>> wspace_5 >> ws >> m2[5]>> wspace_6 >> ws >> m2[6]>> wspace_7 >> ws >> m2[7]>> ws; 
					if (!stringstream || !stringstream.eof() || !isspace(wspace_0) || !isspace(wspace_1) || !isspace(wspace_2) ||
						!isspace(wspace_3) || !isspace(wspace_4) || !isspace(wspace_5) || !isspace(wspace_6)|| !isspace(wspace_7)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					tracerConfig->mat2 = m2;
				}
				else if(keyword == "MAT3"){
					//MAT3 should be followed by 8 values
					vector<float> m3;
					m3.resize(8);
					char wspace_0, wspace_1, wspace_2, wspace_3, wspace_4, wspace_5, wspace_6, wspace_7;
					stringstream >> wspace_0 >> ws >> m3[0] >> wspace_1 >> ws >> m3[1] 
					>> wspace_2 >> ws >> m3[2]>> wspace_3 >> ws >> m3[3]>> wspace_4 >> ws >> m3[4]
					>> wspace_5 >> ws >> m3[5]>> wspace_6 >> ws >> m3[6]>> wspace_7 >> ws >> m3[7]>> ws; 
					if (!stringstream || !stringstream.eof() || !isspace(wspace_0) || !isspace(wspace_1) || !isspace(wspace_2) ||
						!isspace(wspace_3) || !isspace(wspace_4) || !isspace(wspace_5) || !isspace(wspace_6)|| !isspace(wspace_7)) {
						cout << "Corrupted file\n";
						return tracerConfig;
					}
					tracerConfig->mat3 = m3;
				}
			}
		}
		ifs.close();
		tracerConfig->complete = true;
	}
	else{
		cout << "Error opening file\n";
		return tracerConfig;
	}
	return tracerConfig;
}

#endif