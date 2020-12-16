#include "form.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Radio_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Input.H>
#include <FL/FL_ask.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Menu_Item.H>
#include <string>
#include "Frame.h"
#include <stdexcept>

void exit_callback(Fl_Widget*);
void ruotaX_callback(Fl_Widget*);
void ruotaY_callback(Fl_Widget*);
void ruotaZ_callback(Fl_Widget*);
void zoom_callback(Fl_Widget*);

Fl_Window* form;
Frame* scene;
Fl_Button* button, *sendVal;
Fl_Value_Slider* ruotaX, * ruotaY, * ruotaZ, * zoom;
Fl_Group* radios;
Fl_Round_Button* choiceS, *choiceP;
Fl_Input* inputBox;


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

void choiceS_callback(Fl_Widget*) {
    scene->choiceP = false;
    scene->choiceS = true;
}
void choiceP_callback(Fl_Widget*) {
    scene->choiceS = false;
    scene->choiceP = true;
}
void button_callback(Fl_Widget*) {
}

void sendVal_callback(Fl_Widget*) {
    if (scene->choiceS || scene->choiceP) {
        ruotaX->show();
        ruotaY->show();
        ruotaZ->show();
        try {
            scene->inputVal = std::stoi(inputBox->value());;
        }
        catch (std::invalid_argument& const) {
            fl_alert("il valore inserito non e' un intero");
        }
        catch (std::out_of_range& const) {
            fl_alert("il valore inserito eccede il limite degli interi");
        }
    }else fl_alert("devi decidere se seguire un banco o uno specifico pesce");
}


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

    ruotaX = new Fl_Value_Slider(w_est - 210, 20 + 1 * 50, 210, 20, "Ruota X");
    ruotaY = new Fl_Value_Slider(w_est - 210, 20 + 2 * 50, 210, 20, "Ruota Y");
    ruotaZ = new Fl_Value_Slider(w_est - 210, 20 + 3 * 50, 210, 20, "Ruota Z");
    choiceS = new Fl_Round_Button(w_est - 210, 20 + 4 * 50, 20, 20, "Segui banco");
    choiceP = new Fl_Round_Button(w_est - 210, 10 + 5 * 50, 20, 20, "Segui pesce");
    inputBox = new Fl_Input(w_est - 150, 10 + 6 * 50, 40, 20, "numero");
    sendVal = new Fl_Button(SCREEN_W + 130 , 10 + 6 * 50, 50, 20, "invia");


    button = new Fl_Button(w_est - 205, 10+17*50, 200, 80, "Richiesta valori banco \n e pesci");
    /*
    zoom = new Fl_Value_Slider(w_est - 230, 20 + 3 * 50, 210, 20, "Zoom");
    linee = new Fl_Multiline_Output(w_est - 230, 20 + 4 * 50, 210, 70, "");

    button = new Fl_Button(w_est - 230, h_est - 130, 210, 110, "Exit");*/
    ruotaX->type(FL_HOR_NICE_SLIDER); ruotaX->bounds(-1, 1); ruotaX->value(scene->ruotaX = 0);
    ruotaY->type(FL_HOR_NICE_SLIDER); ruotaY->bounds(-1, 1); ruotaY->value(scene->ruotaY = 0);
    ruotaZ->type(FL_HOR_NICE_SLIDER); ruotaZ->bounds(-1, 1); ruotaZ->value(scene->ruotaZ = 0);
    ruotaX->hide();
    ruotaY->hide();
    ruotaZ->hide();
    choiceS->type(FL_RADIO_BUTTON);
    choiceP->type(FL_RADIO_BUTTON);
    /*
    zoom->type(FL_HOR_NICE_SLIDER); zoom->bounds(0.1, 10); zoom->value(scene->zoom = 1.0);*/
    
    ruotaX->callback(ruotaX_callback);
    ruotaY->callback(ruotaY_callback);
    ruotaZ->callback(ruotaZ_callback);
    choiceS->callback(choiceS_callback);
    choiceP->callback(choiceP_callback);
    sendVal->callback(sendVal_callback);
    inputBox->callback(sendVal_callback);

    button->callback(button_callback);
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


