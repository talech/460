/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/
/*************
* inputButton.h
*************
* inputButton Class:
* This class creates an Fl_Widget with a button and 1,2, or 3 inputs.
* There are 3 constructors; 
* the number of inputs created depends on the number of labels inputed.
*************/

#ifndef INPUTBUTTON_H
#define INPUTBUTTON_H

#include <FL/Fl.h>
#include <FL/Fl_Widget.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Float_Input.h>
#include <iostream>
#include <string>
#include <sstream>

class inputButton : public Fl_Widget{
private:
	Fl_Button* button;
	Fl_Float_Input* input1;
	Fl_Float_Input* input2;
	Fl_Float_Input* input3;
	static const int inputW = 40;
	static const int inputH = 25;
	static const int buttonW = 95;
	static const int space = 30;
	void draw(){}
	int num;

public:
	inputButton(int x, int y, int w, int h, char* label, char *in1) : Fl_Widget(x,y,w,h){
		button = new Fl_Button(x,y,buttonW,inputH,label);
		button->box(FL_PLASTIC_UP_BOX);
		button->color(FL_BLUE);
		
		num = 1;

		input1 = new Fl_Float_Input(x+10, y-90, inputW, inputH, in1);
	}

	inputButton(int x, int y, int w, int h, char* label, char *in1, char* in2) : Fl_Widget(x,y,w,h){
		button = new Fl_Button(x,y,buttonW,inputH,label);
		button->box(FL_PLASTIC_UP_BOX);
		button->color(FL_BLUE);
		
		num = 2;

		input1 = new Fl_Float_Input(x+10, y-90, inputW, inputH, in1);
		input2 = new Fl_Float_Input(x+10, y-60, inputW, inputH, in2);
	}

	inputButton(int x, int y, int w, int h, char* label, char *in1, char* in2, char* in3) : Fl_Widget(x,y,w,h){
		button = new Fl_Button(x,y,buttonW,inputH,label);
		button->box(FL_PLASTIC_UP_BOX);
		button->color(FL_BLUE);
		
		num = 3;

		input1 = new Fl_Float_Input(x+10, y-90, inputW, inputH, in1);
		input2 = new Fl_Float_Input(x+10, y-60, inputW, inputH, in2);
		input3 = new Fl_Float_Input(x+10, y-30, inputW, inputH, in3);
	}

	void activate(){
		button->activate();
	}

	void deactivate(){
		button->deactivate();
	}

	void hide(){
		button->hide();
		input1->hide();
		if(num>1) input2->hide();
		if(num == 3) input3->hide();
	}

	void show(){
		button->show();
		input1->show();
		if(num >1) input2->show();
		if(num == 3) input3->show();
	}

	float getValue(int i){
		switch(i){
			case 1:
				return atof(input1->value());
				break;
			case 2:
				return atof(input2->value());
				break;
			case 3:
				return atof(input3->value());
				break;
			default:
				return 0;
		}
	}

	void value(int i,float v){
		std::stringstream str;
		switch(i){
			case 1:
				input1->value(str.str().c_str());
				break;
			case 2:
				input2->value(str.str().c_str());
				break;
			case 3:
				input3->value(str.str().c_str());
				break;
		}
	}

	Fl_Button* getButton(){ return button; }

	
};

#endif