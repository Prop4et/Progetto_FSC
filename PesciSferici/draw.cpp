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

/*extern float pos[10][3];
extern float vel[10][3];
extern Pesce p[10];
extern School s[10];
extern vector<School> pozza;*/
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
void DrawOcean(vector<School>& Oceano)
{
    Merge(Oceano);
    SetAccelerazioni(Oceano);
    for (int i = 0; i < Oceano.size(); i++) {
        Oceano[i].DrawSchool();
    }
}
// ********************************************************************************************************
void initOcean() {
    //prova per potenziale repulsivo+attrattivo.
    float x, y, z, vx, vy, vz;
    x = y = z = vx = vy = vz= 0;
    for (int i = 0; i < FISHNUMBER; i++) {
        pos[i][0] = x;
        pos[i][1] = y;
        pos[i][2] = z;
        x += 2;
        y += 2;
        srand(time(NULL));
        vx = rand() % 10;
        vy = rand() % 10;
        vel[i][0] = vx;
        vel[i][1] = vy;
        vel[i][2] = 0;
        p[i] = Pesce(pos[i], vel[i]);
    }
   
    for (int i = 0; i < SCHOOLNUMBER; i++) {
        s[i] = School(&p[i]);
        pozza.push_back(s[i]);
    }
}

void initOcean2(int rangeSpawn) {
    bool too_close=false;
    for (int i = 0; i < FISHNUMBER; i++) 
    {
        srand(time(NULL));
        pos[i][0] = ((rand() % rangeSpawn * 200 + 1)-rangeSpawn*100)/100;
        pos[i][1] = ((rand() % rangeSpawn * 200 + 1) - rangeSpawn * 100) / 100;
        pos[i][2] = 0;
        for (int g = 0; g < i; g++)
        {
            while (dist(pos[g], pos[i]) <3)
            {
                pos[i][0] = ((rand() % rangeSpawn * 200 + 1) - rangeSpawn * 100) / 100;
                pos[i][1] = ((rand() % rangeSpawn * 200 + 1) - rangeSpawn * 100) / 100;
            }
        }
       
  
        vel[i][0] = 1;
        vel[i][1] = 1;
        vel[i][2] = 0;
        p[i] = Pesce(pos[i], vel[i]);
    }

    for (int i = 0; i < SCHOOLNUMBER; i++) {
        s[i] = School(&p[i]);
        pozza.push_back(s[i]);
    }
}



void draw_scene(void) {
    DrawOcean(pozza);


    // ********************************************************************************************************
    /*void draw_scene(void) {

        draw_pesce();
    */
    //glColor3f(0.1, 1.0, 0.1);		// redish
    //glFrontFace(GL_CW); 
    //glutSolidTeapot(0.5);			// draw the teapot
    //glutSolidTorus(1,2,30,30);			            // draw the torus
    //glutSolidCylinder(1,2,30,20);			            // draw the cylinder

}
