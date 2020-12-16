#pragma once

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

void moveEverything(int index, int rotateX, int rotateY, int rotateZ) {
    //funziona per il pesce, per il banco no perche' devo calcolare il punto medio e seguire, appunto, il banco
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 60, s.getP()[index].getPos()[0], s.getP()[index].getPos()[1], s.getP()[index].getPos()[2], 0, 1, 0);
    glTranslatef(s.getP()[index].getPos()[0], s.getP()[index].getPos()[1], s.getP()[index].getPos()[2]);
    glRotatef(rotateX, 1, 0, 0);
    rx = rotateX;
    glRotatef(rotateY, 0, 1, 0);
    ry = rotateY;
    glRotatef(rotateZ, 0, 0, 1);
    rz = rotateZ;
    glTranslatef(-s.getP()[index].getPos()[0], -s.getP()[index].getPos()[1], -s.getP()[index].getPos()[2]);
}

void moveEverything(float px, float py, float pz, int rotateX, int rotateY, int rotateZ) {
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 60, px, py, pz, 0, 1, 0);
    glTranslatef(px, py, pz);
    glRotatef(rotateX, 1, 0, 0);
    rx = rotateX;
    glRotatef(rotateY, 0, 1, 0);
    ry = rotateY;
    glRotatef(rotateZ, 0, 0, 1);
    rz = rotateZ;
    glTranslatef(-px, -py, -pz);
}

void setCamera(int follow, bool isSchool, bool isFish, int rotateX, int rotateY, int rotateZ) {
    if (follow != -1) {
        if (isSchool) {
            if (follow <= s.getSchool().back().first) {
                //qua devo calcolare le coordinate 
                float center[3] = { 0, 0, 0 };
                s.computeAVGDir(follow, center);
                moveEverything(center[0], center[1], center[2], rotateX, rotateY, rotateZ);
            }
        }
        if (isFish) {
            if (follow < s.getP().size())
                moveEverything(follow, rotateX, rotateY, rotateZ);
        }
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
    s.Merge();
    s.Split();
    s.SetAccelerazioni();
    DrawSchool();
}
// ********************************************************************************************************
void initOcean() {
    s = School();
}


void draw_scene(int follow, bool isSchool, bool isFish, int rotateX, int rotateY, int rotateZ) {
    setCamera(follow, isSchool, isFish, rotateX, rotateY, rotateZ);
    DrawOcean();
    glColor3f(0.1, 1.0, 0.1);		// redish
    
}
