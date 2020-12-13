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


float dist(float* pos1, float* pos2);
float modul3(float* Anyvect);
void FindDir(float* Anyvect, float* arr);
float ProdottoScalare3(float* AnyVet1, float* AnyVet2);