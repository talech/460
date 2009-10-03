/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#include "controller.h"
#include <iostream>

using namespace std;

Controller::Controller(){
	root = new ObjectNode("Light",12,4);
	root->setRoot();
	selected = root;
	root->setSelected();
	root->transforms->setTransX(-5);
	root->transforms->setTransY(10);
	root->transforms->setTransZ(10);
	root->transforms->setScaleX(.5);
	root->transforms->setScaleY(.5);
	root->transforms->setScaleZ(.5);

	addNode("Root Node",0,0);
	

	//root->tex_2d = tex_2d;
	//glBindTexture( GL_TEXTURE_2D, tex_2d );


	
	PrintGraph();
}

void
Controller::removeNode(){
	if(selected->isRoot()||selected->getObject() == 0){
		cout<<"** You can't delete root node **\n";
	}
	else{
		selected->deleteAllChildren();
		ObjectNode* parent = selected->getParent();
		parent->deleteChild(selected);
		selected = parent;
		selected->setSelected();
	}
	PrintGraph();
}

void 
Controller::addNode(string n, int t, int s){
	ObjectNode* newNode = new ObjectNode(n,t,s);
	selected->addChild(newNode);
	PrintGraph();
}

void
Controller::NextNodeHelp(){
	if(!selected->isRoot()){
		ObjectNode* next = selected->getParent()->nextChild(selected);
		if(next != selected->getParent()){
			selected = next;
		}
		else{
			selected = selected->getParent();
			this->NextNodeHelp();
		}
	}
}

void
Controller::NextNode(){
	selected->unSelect();
	if(selected->numChildren() > 0){
		selected = selected->firstChild();
	}
	else{
		NextNodeHelp();
	}
	selected->setSelected();
	this->PrintGraph();
}

void
Controller::PrintHelp(ObjectNode* node){
	if(!selected->isRoot()){
		ObjectNode* next = selected->getParent()->nextChild(selected);
		if(next != selected->getParent()){
			cout<<" }";
			selected = next;
			if(node == selected)
				cout<<"=>**"<<selected->nodeName()<<"**{ ";
			else
				cout<<"=>"<<selected->nodeName()<<"{ ";
		}
		else{
			cout<<"}";
			selected = selected->getParent();
			this->PrintHelp(node);
		}
	}
}

void
Controller::PrintGraph(){
	ObjectNode* temp = selected;

	cout<<"\n";	
	if(temp == root)
		cout<<">> **"<<root->nodeName()<<"** ";
	else
		cout<<">> "<<root->nodeName()<<" ";
	selected = root;
	
	do{
		if(selected->numChildren() > 0){
			selected = selected->firstChild();

			if(temp == selected)
				cout<<"=>**"<<selected->nodeName()<<"**{ ";
			else
				cout<<"=>"<<selected->nodeName()<<" { ";
		}
		else{
			PrintHelp(temp);
			
		}
	}
	while(selected != root);

	cout<<"<<\n";
	selected = temp;
	
	
}

void
Controller::draw(){
	root->drawObject(counter);
}

void
Controller::translate(float x, float y, float z){
	if(!selected->isRoot()){
		selected->transforms->setTransX(x);
		selected->transforms->setTransY(y);
		selected->transforms->setTransZ(z);
	}
}

void
Controller::scale(float x, float y, float z){
	if(!selected->isRoot()){
		if(x!=0)
			selected->transforms->setScaleX(x);
		if(y!=0)
			selected->transforms->setScaleY(y);
		if(z!=0)
			selected->transforms->setScaleZ(z);
	}
}

void
Controller::rotate(float x, float y, float z){
	if(!selected->isRoot()){
		selected->transforms->setAngleX(x);
		selected->transforms->setAngleY(y);
		selected->transforms->setAngleZ(z);
	}
}

void
Controller::color(float r, float g, float b){
	selected->transforms->setColor(r,g,b);
}

void
Controller::clone(){
	ObjectNode* newNode = new ObjectNode(selected->nodeName(),selected->getObject(),selected->getShape());
	selected->getParent()->addChild(newNode);
	newNode->transforms->setColor(selected->transforms->getR(),selected->transforms->getG(),selected->transforms->getB());
	newNode->transforms->setAngleX(selected->transforms->getAngleX());
	newNode->transforms->setAngleY(selected->transforms->getAngleY());
	newNode->transforms->setAngleZ(selected->transforms->getAngleZ());
	newNode->transforms->setScaleX(selected->transforms->getScaleX());
	newNode->transforms->setScaleY(selected->transforms->getScaleY());
	newNode->transforms->setScaleZ(selected->transforms->getScaleZ());
	newNode->transforms->setTransX(selected->transforms->getTransX()+2);
	newNode->transforms->setTransY(selected->transforms->getTransY());
	newNode->transforms->setTransZ(0);

	if(selected->numChildren() > 0)
		selected->cloneChildren(newNode);
}


bool
Controller::addMesh(const std::string &filename){
	Mesh* file_m = ReadFile(filename);
	if(file_m->numFaces() >0){
		ObjectNode* newNode = new ObjectNode("Mesh",10,3);
		selected->addChild(newNode);
		newNode->addMesh(file_m);
		PrintGraph();
		return true;
	}
	
	return false;
}

void 
Controller::render(){
	Tracer* trace = new Tracer(root);
	trace->setDimensions(500,500);
	trace->InitRender();
	trace->Render();
}

