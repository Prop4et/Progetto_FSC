#pragma once
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include "Ocean.h"
#include "define.h"
#include "Frame.h"

void initOcean();
void normale9f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
void draw_scene(int follow, bool isSchool, bool isFish, int rotateX, int rotateY, int rotateZ);
void DrawOcean();
//void setCamera(int follow, bool isSchool, bool isFish, int rotateX, int rotateY, int rotateZ);
int rx = 0, ry = 0, rz = 0;

//prova per potenziale repulsivo+attrattivo.






