#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "define.h"

#define LIGHT 1
#define SFERA 44
#define BUCA 62

class Frame : public Fl_Gl_Window {
private:
	void draw();
	void init();
	int handle_mouse(int event, int button, int x, int y);
	int handle_key(int event, int key);
public:
	double ruotaX, ruotaY, ruotaZ, zoom;
	double moveUp, moveSide, scale;
	bool choiceS = false, choiceP = false;
	int inputVal = -1;
	int handle(int);
	Frame(int x, int y, int w, int h, const char* l = 0) : Fl_Gl_Window(x, y, w, h, l) {}
};


