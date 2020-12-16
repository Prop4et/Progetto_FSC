#define _CRT_SECURE_NO_WARNINGS
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <Windows.h>
#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/Enumerations.H>

#include "Frame.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>


#define LIGHT

extern void initOcean();
extern void draw_scene(int schoolToWatch, bool isSchool, bool isFish, int rotateX, int rotateY, int rotateZ);
extern void stampa(const char* messaggio);
char* foo;
int flag = 0;

void Frame::init(void) {
    moveUp = 0;
    moveSide = 0;
    scale = 1;
    gl_font(FL_HELVETICA_BOLD, 16);
    GLUquadricObj* palla;
    palla = gluNewQuadric();
    gluQuadricDrawStyle(palla, GLU_FILL);
    gluQuadricNormals(palla, GLU_FLAT);
    glNewList(SFERA, GL_COMPILE);
    glColor3f(1.0f, .0f, .0f);
    gluSphere(palla, 0.5, 30, 30);
    glEndList();

    //per disegnare le buche (giusto per vedere se sono nelle posizioni giuste)
    GLUquadricObj* buca;
    buca = gluNewQuadric();
    gluQuadricDrawStyle(buca, GLU_FILL);
    gluQuadricNormals(buca, GLU_FLAT);

    glNewList(BUCA, GL_COMPILE);
    gluSphere(buca, 0.1, 30, 30);
    glEndList();
    initOcean();
}
//-----------------------------------------------------------------------------------------------


void Frame::draw() {
    if (!valid()) {
#if defined(LIGHT)

        GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
        GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
        GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glShadeModel(GL_SMOOTH);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glClearColor(0.0, 0.0, 0.0, 1.0);

#endif // LIGHT            
        glClearColor(0.0, 0.0, .5, .6);                        // Turn the background color blue
        glViewport(0, 0, w(), h());                            // Make our viewport the whole window
        glMatrixMode(GL_PROJECTION);                           // Select The Projection Matrix
        glLoadIdentity();                                      // Reset The Projection Matrix
        gluPerspective(45.0f, w() / h(), 1, 200.0f);
        glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
        glLoadIdentity();                                      // Reset The Modelview Matrix
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer
        glLoadIdentity();                                      // Reset The View
        gluLookAt(0.0, 0.0, 60, 0, 0, 0, 0, 1, 0);        // Position - View  - Up Vector
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        init();
        valid(1);
    }

    //glClear(GL_DEPTH_BUFFER_BIT); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_scene(inputVal, choiceS, choiceP, ruotaX, ruotaY, ruotaZ);       
}

//-----------------------------------------------------------------------------------------------
int Frame::handle(int event) {

    switch (event) {
    case FL_PUSH:
        return handle_mouse(event, Fl::event_button(), Fl::event_x(), Fl::event_y());
    case FL_RELEASE:
    case FL_DRAG:
        return handle_mouse(event, Fl::event_button(), Fl::event_x(), Fl::event_y());
    case FL_MOVE:
        //return handle_mouse(event, Fl::event_button(), Fl::event_x(), Fl::event_y());
        return 1;
    case FL_FOCUS:
        return 1;
    case FL_UNFOCUS:
        return 1;
    default:
        return Fl_Window::handle(event);
    case FL_KEYBOARD:  return handle_key(event, Fl::event_key());
    };
}

int Frame::handle_mouse(int event, int button, int x, int y) {
    foo = new char[100];
    int ret = 0;
    switch (button) {
    case 1: // LMB
        ret = 1;
        // Based on the action, print the action and
        // coordinates where it occurred.
       
    case 3:
        ret = 1;
        // Based on the action, print the action and
        // coordinates where it occurred.
        if (event == FL_PUSH) {
            //inizializzo le posizioni in cui clicko
        }
        else if (event == FL_DRAG) {

        }
        else if (event == FL_RELEASE) {

        }
    }
    return ret;
}

int Frame::handle_key(int event, int key) {
    switch (key) {
    case 's':  //label("letter c was depressed");
        moveUp--;
        glLoadIdentity();
        gluLookAt(0.0+scale, 0.0+scale, 60+scale, 0 + moveSide, 0 + moveUp, 0, 0, 1, 0);
        glScalef(scale, scale, scale);
        return 1;
    case 'w':  //label("letter c was depressed");
        moveUp++;
        glLoadIdentity();
        gluLookAt(0.0+scale, 0.0+scale, 60+scale, 0 + moveSide, 0 + moveUp, 0, 0, 1, 0);
        glScalef(scale, scale, scale);
        return 1;
    case 'd':  //label("letter c was depressed");
        moveSide++;
        glLoadIdentity();
        gluLookAt(0.0 + scale, 0.0 +scale , 60+scale, 0 + moveSide, 0 + moveUp, 0, 0, 1, 0);
        glScalef(scale, scale, scale);
        return 1;
    case 'a':  //label("letter c was depressed");
        moveSide--;
        glLoadIdentity();
        gluLookAt(0.0 + scale, 0.0 +scale, 60+scale, 0 + moveSide, 0 + moveUp, 0, 0, 1, 0);
        glScalef(scale, scale, scale);
        return 1;
    case 'x':
        scale+=0.1;
        glLoadIdentity();
        gluLookAt(0.0 +scale, 0.0+scale, 60+scale, 0 + moveSide, 0 + moveUp, 0, 0, 1, 0);
        glScalef(scale, scale, scale);
        return 1;
    case 'z':
        scale-=0.1;
        glLoadIdentity();
        gluLookAt(0.0+scale, 0.0+scale, 60+scale, 0 + moveSide, 0 + moveUp, 0, 0, 1, 0);
        glScalef(scale, scale, scale);
        return 1;
    default:  //label("Nothing to do!");
        damage(1);
        printf("nothing to do\n");
        return 1;
    }
}