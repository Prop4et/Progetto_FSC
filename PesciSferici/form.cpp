#include "form.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Multiline_Output.H>

#include "Frame.h"

void exit_callback(Fl_Widget*);
void ruotaX_callback(Fl_Widget*);
void ruotaY_callback(Fl_Widget*);
void ruotaZ_callback(Fl_Widget*);
void zoom_callback(Fl_Widget*);

Fl_Window* form;
Frame* scene;
Fl_Button* button;
Fl_Value_Slider* ruotaX, * ruotaY, * ruotaZ, * zoom;

void exit_callback(Fl_Widget*);
void ruotaX_callback(Fl_Widget*);
void ruotaY_callback(Fl_Widget*);
void ruotaZ_callback(Fl_Widget*);
void zoom_callback(Fl_Widget*);

Fl_Multiline_Output* linee;

//-------------------------------------------------------
void exit_callback(Fl_Widget*) { form->hide(); }
/*
void ruotaSfera_cb(Fl_Widget*) { scene->theta; }
void vSfera_cb(Fl_Widget*) { scene->v; }*/

void ruotaX_callback(Fl_Widget*) { scene->ruotaX = 180 * ruotaX->value(); }
void ruotaY_callback(Fl_Widget*) { scene->ruotaY = 180 * ruotaY->value(); }
void ruotaZ_callback(Fl_Widget*) { scene->ruotaZ = 180 * ruotaZ->value(); }
void zoom_callback(Fl_Widget*) { scene->zoom = zoom->value(); }




void stampa(const char* messaggio) {
    const int N = 50;
    static char linea2[N] = { 0 }, linea3[N] = { 0 }, linea4[N] = { 0 };
    char linea[4 * N] = { 0 };

    strcpy_s(linea, linea2); strcpy_s(linea2, linea3); strcpy_s(linea3, linea4); strcpy_s(linea4, messaggio);
    strcat_s(linea, linea2); strcat_s(linea, linea3); strcat_s(linea, linea4);
}
//-------------------------------------------------------------------------------------------------

void CreateMyWindow(void) {
    int w_est, h_est;

    w_est = 10 + SCREEN_W + 200 + 10;   h_est = 10 + SCREEN_H + 10;

    form = new Fl_Window(w_est, h_est, "Pesci");
    new Fl_Box(FL_DOWN_FRAME, 10, 10, SCREEN_W , SCREEN_H , "");
    scene = new Frame(10, 10, SCREEN_W, SCREEN_H, 0);
    //scene->tooltip(" OpenGl windows ");
    //scene->MyTip->enter_area(scene, 0,0,SCREEN_WIDTH,SCREEN_HEIGHT, " ecco il centro ");

    ruotaX = new Fl_Value_Slider(w_est - 210, 20 + 0 * 50, 210, 20, "Ruota X");
    ruotaY = new Fl_Value_Slider(w_est - 210, 20 + 1 * 50, 210, 20, "Ruota Y");
    ruotaZ = new Fl_Value_Slider(w_est - 210, 20 + 2 * 50, 210, 20, "Ruota Z");
    /*
    zoom = new Fl_Value_Slider(w_est - 230, 20 + 3 * 50, 210, 20, "Zoom");
    linee = new Fl_Multiline_Output(w_est - 230, 20 + 4 * 50, 210, 70, "");

    button = new Fl_Button(w_est - 230, h_est - 130, 210, 110, "Exit");*/
    ruotaX->type(FL_HOR_NICE_SLIDER); ruotaX->bounds(-1, 1); ruotaX->value(scene->ruotaX = 0);
    ruotaY->type(FL_HOR_NICE_SLIDER); ruotaY->bounds(-1, 1); ruotaY->value(scene->ruotaY = 0);
    ruotaZ->type(FL_HOR_NICE_SLIDER); ruotaZ->bounds(-1, 1); ruotaZ->value(scene->ruotaZ = 0);
    /*
    zoom->type(FL_HOR_NICE_SLIDER); zoom->bounds(0.1, 10); zoom->value(scene->zoom = 1.0);*/
    ruotaX->callback(ruotaX_callback);
    ruotaY->callback(ruotaY_callback);
    ruotaZ->callback(ruotaZ_callback);
    /*
    zoom->callback(zoom_callback);


    button->callback(exit_callback);
    button->tooltip(" Ciao ");
    //ruotaX->tooltip(" Rotazione antioraria con asse x ");
    */

    form->end();
    form->show();
    scene->show();


}
//-------------------------------------------------------------------------------------------------


