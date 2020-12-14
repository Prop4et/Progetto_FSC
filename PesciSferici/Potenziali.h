#pragma once
#include <math.h>
#include <iostream>
#include "define.h"
#include "Pesce.h"

int WeightTot(vector<pair<int, int>> school);
int Weight(vector<pair<int, int>> school, int indexS);
bool seenSchools(vector<pair<int, int>> s, vector<Pesce> p, vector<int>& ps, int pesce);
void AttractiveForcesSchool(float* PosSchool, float* VelSchool, float* PosFish, float RSchool, float* arr, int len);
void AttractiveForcesSchool(vector<pair<int, int>> s, vector<Pesce> p, int indexPerceivedSchools, int indexP, float* arr);
void RepulsiveForcesFish(Pesce PesceGen, Pesce PesceSub, float* arr);
void RepulsiveForcesFish(float* PosFish1, float* PosFish2, float* arr);
void AttractiveForcesHole(float* PosFish, float* PosHole, float* arr);
