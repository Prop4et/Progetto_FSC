#pragma once
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include "School.h"
#include "define.h"
#include "Frame.h"

void initOcean();
void normale9f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
void draw_scene(int schoolToWatch, int fishToWatch, int rotateX, int rotateY, int rotateZ);
void DrawOcean();
void setCamera(int schoolToWatch, int fishToWatch, int rotateX, int rotateY, int rotateZ);
School s;

//prova per potenziale repulsivo+attrattivo.






