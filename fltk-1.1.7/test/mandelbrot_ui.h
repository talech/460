// generated by Fast Light User Interface Designer (fluid) version 1.0107

#ifndef mandelbrot_ui_h
#define mandelbrot_ui_h
#include <FL/Fl.H>
#include "mandelbrot.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Box.H>

class Drawing_Window {
public:
  void make_window();
  Fl_Double_Window *window;
  Drawing_Area *d;
  Fl_Input *x_input;
private:
  void cb_x_input_i(Fl_Input*, void*);
  static void cb_x_input(Fl_Input*, void*);
public:
  Fl_Input *y_input;
private:
  void cb_y_input_i(Fl_Input*, void*);
  static void cb_y_input(Fl_Input*, void*);
public:
  Fl_Input *w_input;
private:
  void cb_w_input_i(Fl_Input*, void*);
  static void cb_w_input(Fl_Input*, void*);
  void cb_brightness_i(Fl_Slider*, void*);
  static void cb_brightness(Fl_Slider*, void*);
  void cb_iterations_i(Fl_Slider*, void*);
  static void cb_iterations(Fl_Slider*, void*);
public:
  void update_label();
};
#endif
