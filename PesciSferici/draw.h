#pragma once
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include "Pesce.h"
#include "Shoal.h"

bool init = false;
Shoal* s = new Shoal();

void normale9f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
void draw_scene(void);
/*void draw_palla(void);
void draw_tetra(void);
void draw_cube(void);
*/