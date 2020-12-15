#include "Pesce.h"
#include <iostream>




Pesce::Pesce() {
    float arr[3] = { 0.0, 0.0, 0.0 };
    setPos(arr);
    setVel(arr);
    setAcc(arr);
    setTheta(0.0);
    for (int i = 0; i < 8; i++) holes[i] = Hole(pos, vel, i + 1);
}

Pesce::Pesce(float* p, float* v, float* a) {
    //assuming everything has the same size, as it should be
    setPos(p);
    setVel(v);
    setAcc(a);
    for (int i = 0; i < 8; i++) holes[i] = Hole(pos, vel, i + 1);
}

Pesce::Pesce(float* p, float* v) {
    //assuming everything has the same size, as it should be
    setPos(p);
    setVel(v);
    float a[3] = { 0,0,0 };
    setAcc(a);
    for (int i = 0; i < 8; i++) holes[i] = Hole(pos, vel, i + 1);
}

void Pesce::setPos(float* p) {
    for (int i = 0; i < DIMARR; i++)
        pos[i] = p[i];
}

void Pesce::setVel(float* v) {
    for (int i = 0; i < DIMARR; i++)
        vel[i] = v[i];
}

void Pesce::setAcc(float* a) {
    for (int i = 0; i < DIMARR; i++)
        acc[i] = a[i];
}


void Pesce::setTheta(float t) {
    theta = t;
}

void Pesce::Nuota() {
    float v = askModule(vel);
    //incremento della posizione e della velocità del pesce
    for (int k = 0; k < DIMARR; ++k)
    {
        
        pos[k] += vel[k] * dt;
        vel[k] += acc[k] * dt;
        //if (vel[k]>0.001) acc[k] += -dt*vel[k]/abs(vel[k]); //attrito viscoso
        if (vel[k]>0.001) acc[k] += -dt*pow(vel[k], 3) / (abs(vel[k]) + 0.0000001); //attrito 
        //if (vel[k] > 0.001) acc[k] += -dt * pow(vel[k], 5) / (abs(vel[k]) + 0.0000001); //attrito viscoso
       // else  acc[k] += -vel[k] * dt;
    }

    //movimenti e grafica delle buche
    for (int i = 0; i < 8; i++)
    {
        holes[i].AggiornaBuca(pos, vel);
        glColor3f(holes[i].getCol()[0], holes[i].getCol()[1], holes[i].getCol()[2]);
        glPushMatrix();
        glTranslated(holes[i].getPos()[0], holes[i].getPos()[1], holes[i].getPos()[2]);
        glCallList(BUCA);
        glPopMatrix();
    }
}

void Pesce::NuotainCerchio(float& t, int i) {
    //i=0->ruta su piano xz i=1->ruota su piano xy, altri valori->bohhh
    acc[0] = -10 * cos(t);
    acc[1] = -10 * sin(t) * i;
    acc[2] = 10 * sin(t) * (i - 1);
    Nuota();
    t += dt;

}


float Pesce::computeTheta() {
    return atan2f(vel[1], vel[0]) * (180 / M_PI);
}