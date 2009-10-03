/*****************************
Tamara Levy
CIS 460
October 9, 2008
SceneGraph - Room Editor
******************************/

#ifndef GUI_H
#define GUI_H

#include <FL/Fl_Window.h>
#include <FL/Fl_Counter.h>
#include <FL/Fl_Button.h>
#include <FL/Fl_Menu_Button.h>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Input.h>
#include <FL/fl_ask.h>
#include <FL/fl_draw.H>
#include <string>

#include "View.h"
#include "Controller.h"
#include "inputButton.h"
#include "algebra3.h"



class GUI{
private:
	Fl_Window* window;
	
	Fl_Menu_Button* add;
	Fl_Button* remove;
	Fl_Button* clone;
	Fl_Button* render;
	Fl_Button* import;
	Fl_File_Chooser* choose_import;

	
	Fl_Menu_Button* transfMenu;
	Fl_Color_Chooser* color;
	inputButton* rotate;
	inputButton* translate;
	inputButton* rotate2;
	inputButton* scales;
	Fl_Value_Slider* diffuse;
	Fl_Value_Slider* specular;
	Fl_Value_Slider* reflection;
	Fl_Box* tagMaterial;

	Fl_Box* tag3;
	Fl_Box* tag2;
	Controller* control;

	
	static void addCB(Fl_Button* button, void* gui){
		((GUI*)gui)->addCB2();
	}

	void addCB2();

	static void transfCB(Fl_Button* button, void* gui){
		((GUI*)gui)->transfCB2();
	}

	void transfCB2();

	static void cbRotate(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->cb2Rotate();}
	
	void cb2Rotate();

	static void cbRotate2(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->cb2Rotate2();}
	
	void cb2Rotate2();

	static void cbTranslate(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->cb2Translate();}
	
	void cb2Translate();

	static void cbScale(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->cb2Scale();}
	
	void cb2Scale();

	static void cbColor(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->cb2Color();}
	
	void cb2Color();

	static void cbSpecular(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->cb2Specular();}
	
	void cb2Specular();

	static void cbDiffuse(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->cb2Diffuse();}
	
	void cb2Diffuse();

	static void cbReflection(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->cb2Reflection();}
	
	void cb2Reflection();
	
	void select();

	static void selectCB(void* gui)
	{  ((GUI*)gui)->selectCB2();}
	
	void selectCB2();

	static void removeCB(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->removeCB2();}
	
	void removeCB2();

	static void cloneCB(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->cloneCB2();}
	
	void cloneCB2();

	static void importCB(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->importCB2();}
	
	void importCB2();

	static void renderCB(Fl_Widget* w, void* gui)
	{  ((GUI*)gui)->renderCB2();}
	
	void renderCB2();


public:
	View* view;
	GUI();
	
};

#endif