#include "GUI.h"
#include <iostream>

//Adds a new Item to TreeView and calls the add method in 
//Controller which will add the proper node depending
//on the selection.
void 
GUI::addCB2(){
	int v = add->value();
	std::cout<<v<<std::endl;
	if(v == 1){
		control->addNode("Chair",1,1);
	}
	else if(v == 2){
		control->addNode("Desk",2,1);
	}
	else if(v == 3){
		control->addNode("Lamp",3,1);
	}
	else if(v == 4){
		control->addNode("Cabinet",4,1);
	}
	else if(v == 5){
		control->addNode("Monitor",11,1);
	}
	else if(v == 8){
		control->addNode("Sphere",5,2);
	}
	else if(v == 9){
		control->addNode("Cube",6,2);
	}
	else if(v == 10){
		control->addNode("Cylinder",7,2);
	}
	else if(v == 11){
		control->addNode("Half Sphere",8,2);
	}
	else if(v == 12){
		control->addNode("Disk",9,2);
	}
	
	view->redraw();
}

void 
GUI::transfCB2(){
	int v = transfMenu->value();
	rotate->value(1,control->selected->transforms->getAngleX());
	rotate->value(2,control->selected->transforms->getAngleY());
	rotate->value(3,control->selected->transforms->getAngleZ());

	translate->value(1,control->selected->transforms->getTransX());
	translate->value(2,control->selected->transforms->getTransY());
	translate->value(3,control->selected->transforms->getTransZ());

	scales->value(1,control->selected->transforms->getScaleX());
	scales->value(2,control->selected->transforms->getScaleY());
	scales->value(3,control->selected->transforms->getScaleZ());

	color->rgb(control->selected->transforms->getR(),
			   control->selected->transforms->getG(),
			   control->selected->transforms->getB());


	if(v==0){
		color->show();
		translate->hide();
		tag2->hide();
		scales->hide();
		tag3->hide();
		rotate->hide();
		rotate2->hide();
	}
	else if(v == 1){
		color->hide();
		translate->show();
		tag2->show();
		scales->hide();
		tag3->hide();
		rotate->hide();
		rotate2->hide();

	}
	else if(v==2){
		color->hide();
		translate->hide();
		tag2->hide();
		scales->show();
		tag3->show();
		rotate->hide();
		rotate2->hide();
	}
	else if(v==3){
		color->hide();
		translate->hide();
		tag2->hide();
		scales->hide();
		tag3->hide();
		if(control->shape() == SHAPE)
			rotate2->show();
		else
			rotate->show();
	}

}

void
GUI::cb2Translate(){
	float x = translate->getValue(1);
	float y = translate->getValue(2);
	float z = translate->getValue(3);
	if(control->shape() == ROOT)
		control->translate(0,0,0);
	else
		control->translate(x,y,z);
	view->redraw();	
}


void
GUI::cb2Rotate(){
	float x = rotate->getValue(1);
	float y = rotate->getValue(2);
	float z = rotate->getValue(3);
	if(control->shape() == ROOT)
		control->rotate(0,0,0);
	else 
		control->rotate(x,y,z);
	view->redraw();	
}

void
GUI::cb2Rotate2(){
	float x = rotate2->getValue(1);
	float y = rotate2->getValue(2);
	float z = rotate2->getValue(3);
	if(control->shape() == ROOT)
		control->rotate(0,0,0);
	else 
		control->rotate(x,y,z);
	view->redraw();	
}

void
GUI::cb2Scale(){
	float x = scales->getValue(1);
	float y = scales->getValue(2);
	float z = scales->getValue(3);
	if(control->shape() == ROOT)
		control->scale(1,1,1);
	else 
		control->scale(x,y,z);
	view->redraw();	
}

void
GUI::cb2Color(){
	float r = color->r();
	float g = color->g();
	float b = color->b();
	control->color(r,g,b);
	view->redraw();
}

void
GUI::cb2Diffuse(){
	float d = diffuse->value();
	control->setDiffuse(d);
	control->setSpecular(1-d);
	
}

void
GUI::cb2Specular(){
	float s = specular->value();
	control->setSpecular(s);
	control->setDiffuse(1-s);
}

void
GUI::cb2Reflection(){
	float r = reflection->value();
	control->setReflection(r);
}

void
GUI::select(){
	Fl::add_timeout(0, selectCB, this);
}

void 
GUI::selectCB2(){
	if(control->counter == 1) control->counter = 2;
	else control->counter = 1;
	view->redraw();
	//update values
	diffuse->value(control->selected->transforms->getDiffuse());
	reflection->value(control->selected->transforms->getReflection());
	specular->value(control->selected->transforms->getSpecular());
	
	

	
	Fl::repeat_timeout(1.0/2.0, selectCB, this); 
}

void
GUI::removeCB2(){
	if(control->rootSelected()){
		char msg[] = "Sorry, you can't delete the Root.";
		fl_alert(msg);
	}
	else
		control->removeNode();
	view->redraw();
}

void
GUI::cloneCB2(){
	if(control->rootSelected()){
		char msg[] = "Sorry, you can't clone the Root.";
		fl_alert(msg);
	}
	else
		control->clone();
	view->redraw();

}

void
GUI::importCB2(){
	string filename;
	Fl_File_Chooser chooser(".","Valid Files (*.{surfrev,extrude,obj})",Fl_File_Chooser::SINGLE, "Open file?");
	chooser.show();
	while(chooser.shown()){ Fl::wait(); }

	if ( chooser.value() != NULL ){
		filename = chooser.value();
		bool load = control->addMesh(filename);
		if(!load){
			char msg[] = "Sorry. Invalid file.";
			fl_alert(msg);
		}
	}
	view->redraw();

}

void 
GUI::renderCB2(){
	control->render();
}

GUI::GUI(){
	
	window = new Fl_Window(100,50,880,700, "My Super Cool Room Editor");
	window->begin();
		control = new Controller();	
		view = new View(control);
		
		add = new Fl_Menu_Button(20, 10, 80, 30, "&Add");
		Fl_Menu_Item items[] = {
			{"&Objects",0,0,0,FL_SUBMENU},
				{"chair"},
				{"desk"},
				{"lamp"},
				{"cabinet"},
				{"monitor"},
				{0},
			{"&Shapes",0,0,0,FL_SUBMENU},
				{"sphere"},
				{"cube"},
				{"cylinder"},
				{"half sphere"},
				{"disk"},
				{0},
			{0}
		};
		add->menu(items);
		add->box(FL_PLASTIC_UP_BOX);
		add->color(FL_GREEN);
		add->callback((Fl_Callback*)addCB, this);

		remove = new Fl_Button(290, 10, 80, 30, "&Remove");
		remove->box(FL_PLASTIC_UP_BOX);
		remove->color(FL_RED);
		remove->callback((Fl_Callback*)removeCB, this);

		clone = new Fl_Button(200, 10, 80, 30, "&Clone");
		clone->box(FL_PLASTIC_UP_BOX);
		clone->color(FL_DARK_MAGENTA);
		clone->callback((Fl_Callback*)cloneCB, this);

		import = new Fl_Button(110, 10, 80, 30, "Import");
		import->box(FL_PLASTIC_UP_BOX);
		import->color(FL_GREEN);
		import->callback((Fl_Callback*)importCB, this);

		render = new Fl_Button(790, 10, 80, 30, "Render");
		render->box(FL_PLASTIC_UP_BOX);
		render->color(FL_YELLOW);
		render->callback((Fl_Callback*)renderCB, this);

		transfMenu = new Fl_Menu_Button(20, 60, 80, 30, "&Edit");
		Fl_Menu_Item items_edit[] = {
			{"Color"},
			{"Translate"},
			{"Scale"},
			{"Rotate"},
			{0}
		};
		transfMenu->menu(items_edit);
		transfMenu->box(FL_PLASTIC_UP_BOX);
		transfMenu->color(FL_BLUE);
		transfMenu->callback((Fl_Callback*)transfCB, this);
		

		//use show and hide to change transf menu
		rotate = new inputButton(20, 190, 1, 1, "Rotate", "X", "Y", "Z");
		rotate->getButton()->callback((Fl_Callback*)cbRotate, this);

		rotate2 = new inputButton(20, 190, 1, 1, "Rotate", "X", "Y", "Z");
		rotate2->getButton()->callback((Fl_Callback*)cbRotate2, this);
		
		translate = new inputButton(20, 190, 1, 1, "Translate", "X", "Y", "Z");
		tag2 = new Fl_Box(120,100,20,15,"Values: [-5 to 5]");
		translate->getButton()->callback((Fl_Callback*)cbTranslate, this);
		

		scales = new inputButton(20, 190, 1, 1, "Scale", "X", "Y", "Z");
		tag3 = new Fl_Box(120,100,20,15,"Values: [0 to 10]");
		scales->getButton()->callback((Fl_Callback*)cbScale, this);
		tag3->hide();


		color = new Fl_Color_Chooser(20,100,210,95,"");
		color->callback((Fl_Callback*)cbColor, this);
		
		color->hide();
		scales->hide();
		rotate->hide();
		rotate2->hide();

		tagMaterial = new Fl_Box(100,240,20,15,"Material Values\nfor Rendering");
		diffuse = new Fl_Value_Slider(20,280,200,25,"Diffuse");
		diffuse->type(FL_HOR_NICE_SLIDER);
		diffuse->box(FL_PLASTIC_UP_BOX);
		diffuse->bounds(0,1);
		diffuse->color(FL_DARK_YELLOW);
		diffuse->callback((Fl_Callback*)cbDiffuse, this);
		diffuse->value(1);

		specular = new Fl_Value_Slider(20,330,200,25,"Specular");
		specular->type(FL_HOR_NICE_SLIDER);
		specular->box(FL_PLASTIC_UP_BOX);
		specular->bounds(0,1);
		specular->color(FL_DARK_RED);
		specular->callback((Fl_Callback*)cbSpecular, this);

		reflection = new Fl_Value_Slider(20,380,200,25,"Reflection");
		reflection->type(FL_HOR_NICE_SLIDER);
		reflection->box(FL_PLASTIC_UP_BOX);
		reflection->bounds(0,1);
		reflection->color(FL_DARK_BLUE);
		reflection->callback((Fl_Callback*)cbReflection, this);
		


		Fl::focus(view);

	window->end();
	window->show();  // this actually opens the window
	select();

}