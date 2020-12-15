#pragma once

#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include <thread>

#include "draw.h"
#include "Frame.h"
#include "utilities.h"
#include "Potenziali.h"


//-------------------------------------------------------------------------------------------------
void normale9f(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
    float xx1, yy1, zz1, xx2, yy2, zz2, nx, ny, nz, nn;
    xx1 = x2 - x1; yy1 = y2 - y1; zz1 = z2 - z1;
    xx2 = x3 - x1; yy2 = y3 - y1; zz2 = z3 - z1;
    nx = yy1 * zz2 - yy2 * zz1; ny = zz1 * xx2 - zz2 * xx1; nz = xx1 * yy2 - xx2 * yy1;
    nn = sqrt(nx * nx + ny * ny + nz * nz);
    nx /= nn; ny /= nn; nz /= nn;
    glNormal3f(nx, ny, nz);
}


void draw_direction(float x, float y, float z) {
    glColor3f(1, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0); glVertex3f(x, y, z);
    glEnd();
}


void rotateAxis(int *prevX, int *clickX, int *prevY, int *clickY, int x, int y) {
    if (*prevX > *clickX)
        glRotatef(-1, 0, 1, 0);
    if (*prevX < *clickX)
        glRotatef(1, 0, 1, 0);
    *prevX = *clickX;
    *clickX = x;

    if (*prevY > *clickY)
        glRotatef(-1, 1, 0, 0);
    if (*prevY < *clickY)
        glRotatef(1, 1, 0, 0);
    *prevY = *clickY;
    *clickY = y;
}

void DrawSchool()
{   
    s.Nuota();
    vector<Pesce> p = s.getP();
    for (int i = 0; i < p.size(); i++)
    {
        glPushMatrix();
        glTranslated(p[i].getPos()[0], p[i].getPos()[1], p[i].getPos()[2]);
        glCallList(SFERA);
        glPopMatrix();
    }

}

void DrawOcean()
{
    draw_direction(0, 0, 30);
    draw_direction(0, 30, 0);
    draw_direction(30, 0, 0);
    s.Split();
    s.Merge();
    s.SetAccelerazioni();
    DrawSchool();
}
// ********************************************************************************************************
void initOcean() {
    s = School();
}


void draw_scene(void) {
    DrawOcean();

    // ********************************************************************************************************
    /*void draw_scene(void) {

        draw_pesce();
    */
    glColor3f(0.1, 1.0, 0.1);		// redish
    //glFrontFace(GL_CW); 
    //glutSolidTeapot(0.5);			// draw the teapot
    //glutSolidTorus(1,2,30,30);			            // draw the torus
    //glutSolidCylinder(1,2,30,20);			            // draw the cylinder

}
