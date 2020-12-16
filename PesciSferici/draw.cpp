﻿#pragma once

#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <GL/glut.h>	  
#include <math.h>
#include <thread>

#include "draw.h"
#include "Frame.h"



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
    if(x!=0)
        glColor3f(1, 0, 0);
    if(y!=0)
        glColor3f(0, 1, 0);
    if(z!=0)
        glColor3f(0, 0, 1);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0); glVertex3f(x, y, z);
    glEnd();
}

void setCamera(int schoolToWatch, int fishToWatch, int rotateX, int rotateY, int rotateZ) {
    //se non ho nessun parametro passato dall'input seguo il primo banco che si crea
    if (schoolToWatch == -1) {
        glLoadIdentity();
        gluLookAt(0.0, 0.0, 60, s.getP()[s.getSchool()[0].second].getPos()[0], s.getP()[s.getSchool()[0].second].getPos()[1], s.getP()[s.getSchool()[0].second].getPos()[2], 0, 1, 0);
        glTranslatef(s.getP()[s.getSchool()[0].second].getPos()[0], s.getP()[s.getSchool()[0].second].getPos()[1], s.getP()[s.getSchool()[0].second].getPos()[2]);
        glRotatef(rotateX, 1, 0, 0);
        rx = rotateX;
        glRotatef(rotateY, 0, 1, 0);
        ry = rotateY;
        glRotatef(rotateZ, 0, 0, 1);
        rz = rotateZ;
        glTranslatef(-s.getP()[s.getSchool()[0].second].getPos()[0], -s.getP()[s.getSchool()[0].second].getPos()[1], -s.getP()[s.getSchool()[0].second].getPos()[2]);
       
    }
}

/*
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
*/
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
    s.Split();
    s.Merge();
    s.SetAccelerazioni();
    DrawSchool();
}
// ********************************************************************************************************
void initOcean() {
    s = School();
}


void draw_scene(int schoolToWatch, int fishToWatch, int rotateX, int rotateY, int rotateZ) {
    setCamera(schoolToWatch, fishToWatch, rotateX, rotateY, rotateZ);
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
