#pragma once
#ifdef PIGRECO

#else
#define PIGRECO 3.141592f

#endif
#include <stdlib.h>     
#include <time.h>
#include <vector>
#include <math.h>
#include "School.h"



void Merge(vector<School>& Oceano);
float dist(float* pos1, float* pos2);
float modul3(float* Anyvect);
void FindDir(float* Anyvect, float* arr);
float ProdottoScalare3(float* AnyVet1, float* AnyVet2);

void ProdottoVettoriale(float* v, float* w, float* result); //result=v x w
void ProdottoVettoriale(float* v, float* w); //v=v x w
void Rotazione(float* v, float* omega); //omega asse di rotazione, R matrice di rotazione

