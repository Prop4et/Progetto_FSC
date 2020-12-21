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
        omega[k] += omegapunto[k] * dt;
        if (v > 5) acc[k] += -pow(vel[k], 3) / (abs(vel[k]) + 0.0000001); //attrito viscoso
        pos[k] += vel[k] * dt;
        vel[k] += acc[k] * dt;
    }

    //movimenti e grafica delle buche che vanno spostati
    for (int i = 0; i < 8; i++)
    {
        holes[i].AggiornaBuca(pos, vel);
        glColor3f(holes[i].getCol()[0], holes[i].getCol()[1], holes[i].getCol()[2]);
        glPushMatrix();
        glTranslated(holes[i].getPos()[0], holes[i].getPos()[1], holes[i].getPos()[2]);
        glCallList(BUCA);
        glPopMatrix();
    }
    Rotazione(vel, omega);
}


float Pesce::computeTheta() {
    return atan2f(vel[1], vel[0]) * (180 / M_PI);
}

void Pesce::Rotazione(float* v, float* omega)
{
    float result[3];
    //costruiamo la matrice di rotazione
    float R[3][3];
    int sgn = -1;
    float theta = modul3(omega);
    float u[3];
    if (modul3(omega) < 0.00001)
    {
        theta = 1;
    }
    for (int y = 0; y < 3; y++) u[y] = omega[y] / theta;
    theta *= dt;
    for (int i = 0; i < 3; i++) //riga i-esima
        for (int j = 0; j < 3; j++) //colonna j-esima
        {
            if (i == j)
                R[i][j] = cos(theta) + u[j] * u[j] * (1 - cos(theta));
            else
            {
                R[i][j] = u[i] * u[j] * (1 - cos(theta)) + sgn * u[3 - i - j] * sin(theta);
                if (j != 2) sgn *= -1;
            }
        }
    //matrice costruita ora ruotiamo il vettore
    for (int i = 0; i < 3; i++)
        result[i] = ProdottoScalare3(R[i], v);
    for (int i = 0; i < 3; i++)
        v[i] = result[i];
}
/*
void Pesce::computePol()
{
    for (int i = 0; i < 3; i++)
        omega[i] += omegapunto[i] * dt;
    Rotazione(vel, omega);
}*/