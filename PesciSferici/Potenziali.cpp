#include "Potenziali.h"
#include "utilities.h"
#include <iostream>
#include <math.h>
using namespace std;

float asimmetry = 0.2f; //fattore di asimettria banco

//##########################
//Funzioni e attributi generali








//##########################################
//Interazione repulsiva pesce-pesce

float RepulsiveForceFishX(float* PosFish1, float* PosFish2)  //pesce 1 crea il potenziale, pesce 2 le subisce
{
	float r = dist(PosFish1, PosFish2);
	return ((3.f) * (PosFish2[0] - PosFish1[0])) / (r * (pow(abs(r - LUNGHEZZA_PESCE / 2.f - Spazio_Vitale), 4)));
}



float RepulsiveForceFishY(float* PosFish1, float* PosFish2) //pesce 1 crea il potenziale, pesce 2 le subisce
{
	float r = dist(PosFish1, PosFish2);
	return ((3.f) * (PosFish2[1] - PosFish1[1])) / (r * (pow(abs(r - LUNGHEZZA_PESCE / 2.f - Spazio_Vitale), 4)));
}


float RepulsiveForceFishZ(float* PosFish1, float* PosFish2) //pesce 1 crea il potenziale, pesce 2 le subisce
{
	float r = dist(PosFish1, PosFish2);
	return ((3.f) * (PosFish2[2] - PosFish1[2])) / (r * (pow(abs(r - LUNGHEZZA_PESCE / 2.f - Spazio_Vitale), 4)));
}


void RepulsiveForcesFish(float* PosFish1, float* PosFish2, float *arr) //calcolo delle forze repulsive generate da un pesce FUNZIONA
																//pesce 1 crea il potenziale, pesce 2 le subisce
{
	float r = dist(PosFish1, PosFish2);
	//float Forze[3];
	for (int i = 0; i < 3; i++)
		arr[i] = ((3.f) * (PosFish2[i] - PosFish1[i])) / (r * (pow(abs(r - LUNGHEZZA_PESCE / 2.f - Spazio_Vitale), 4)));
	//return Forze;
}

float RepulsivePotenzialFish(float* PosFish1, float* PosFish2) //potenziale, primo pesce crea il potenziale, il secondo lo subisce
{
	float r = dist(PosFish1, PosFish2);
	return 1.f / (pow(abs(r - LUNGHEZZA_PESCE / 2.f - Spazio_Vitale), 3));
}


//####################################
//Interazioni Attrattive Banco-pesce

//si potrebbero fare due funzioni per trovare forza parallela e perp e delle funzioni per proiettare sugli assi

float AttractiveForceSchoolX(float* PosSchool, float* VelSchool, float* PosFish, float RSchool) //Forza scalare potenziale di banco, guarda il .h
{
	float modulV = modul3(VelSchool);
	float velposS = ProdottoScalare3(PosSchool, VelSchool);
	float velposF = ProdottoScalare3(PosFish, VelSchool);
	return (1 - asimmetry) * 2 * VelSchool[0] * (velposF - velposS) / (RSchool * RSchool * modulV * modulV)
		+ 2 * (PosSchool[0] - PosFish[0]) / (RSchool * RSchool);
}

float AttractiveForceSchoolY(float* PosSchool, float* VelSchool, float* PosFish, float RSchool)
{
	float modulV = modul3(VelSchool);
	float velposS = ProdottoScalare3(PosSchool, VelSchool);
	float velposF = ProdottoScalare3(PosFish, VelSchool);
	return (1 - asimmetry) * 2 * VelSchool[1] * (velposF - velposS) / (RSchool * RSchool * modulV * modulV)
		+ 2 * (PosSchool[1] - PosFish[1]) / (RSchool * RSchool);
}
float AttractiveForceSchoolZ(float* PosSchool, float* VelSchool, float* PosFish, float RSchool)
{
	float modulV = modul3(VelSchool);
	float velposS = ProdottoScalare3(PosSchool, VelSchool);
	float velposF = ProdottoScalare3(PosFish, VelSchool);
	return (1 - asimmetry) * 2 * VelSchool[2] * (velposF - velposS) / (RSchool * RSchool * modulV * modulV)
		+ 2 * (PosSchool[2] - PosFish[2]) / (RSchool * RSchool);
}

void AttractiveForcesSchool(float* PosSchool, float* VelSchool, float* PosFish, float RSchool, float *arr, int len) //Forza vettoriale per il potenziale di banco
{
	//float Forzexyz[3];
	float modulV = modul3(VelSchool);
	/*if (modulV == 0) {
		modulV = 1;
	}*/
	float velposS = ProdottoScalare3(PosSchool, VelSchool);
	float velposF = ProdottoScalare3(PosFish, VelSchool);
	for (int i = 0; i < len; i++) {
		
		arr[i] = (1 - asimmetry) * 2 * VelSchool[i] * (velposF - velposS) / (RSchool * RSchool * modulV * modulV) //qua capita che modulV sia 0
			+ 2 * (PosSchool[i] - PosFish[i]) / (RSchool * RSchool);
	}
	//return Forzexyz;
}

float AttractivePotenzialSchool(float* PosSchool, float* VelSchool, float* PosFish, float RSchool) //da finire
{
	return 0;
}



//##############################
//Interazioni pesce-buca

float AttractiveForceHoleX(float* PosFish, float* PosHole) //interazione scalare pesce buca, primo argomento posizione pesce, secondo posizione buco
{
	float r = dist(PosFish, PosHole);
	return expf(-(r * r) / (2 * DIM_BUCA * DIM_BUCA)) * (-(PosFish[0] - PosHole[0]) / (DIM_BUCA * DIM_BUCA));
}

float AttractiveForceHoleY(float* PosFish, float* PosHole)
{
	float r = dist(PosFish, PosHole);
	return expf(-(r * r) / (2 * DIM_BUCA * DIM_BUCA)) * (-(PosFish[1] - PosHole[1]) / (DIM_BUCA * DIM_BUCA));
}

float AttractiveForceHoleZ(float* PosFish, float* PosHole)
{
	float r = dist(PosFish, PosHole);
	return expf(-(r * r) / (2 * DIM_BUCA * DIM_BUCA)) * (-(PosFish[2] - PosHole[2]) / (DIM_BUCA * DIM_BUCA));
}

void AttractiveForcesHole(float* PosFish, float* PosHole, float* arr) //interazione vettoriale pesce buca, primo argomento pos pesce, secondo pos buca
{
	float r = dist(PosFish, PosHole);
	//float Forzexyz[3];
	for (int i = 0; i < 3; i++)
		arr[i] = expf(-(r * r) / (2 * DIM_BUCA * DIM_BUCA)) * (-(PosFish[i] - PosHole[i]) / (DIM_BUCA * DIM_BUCA));

	//return Forzexyz;
}


//##########################
//Forze repulsive per pesci (overload)

float RepulsiveForceFishX(Pesce PesceGen, Pesce PesceSub) //il primo pesce genera il potenziale il secondo lo subisce
{
	return RepulsiveForceFishX(PesceGen.getPos(), PesceSub.getPos());
}

float RepulsiveForceFishY(Pesce PesceGen, Pesce PesceSub) //il primo pesce genera il potenziale il secondo lo subisce
{
	return RepulsiveForceFishY(PesceGen.getPos(), PesceSub.getPos());
}

float RepulsiveForceFishZ(Pesce PesceGen, Pesce PesceSub) //il primo pesce genera il potenziale il secondo lo subisce
{
	return RepulsiveForceFishZ(PesceGen.getPos(), PesceSub.getPos());
}



void RepulsiveForcesFish(Pesce PesceGen, Pesce PesceSub, float* arr) //il primo pesce genera il potenziale il secondo lo subisce
{
	RepulsiveForcesFish(PesceGen.getPos(), PesceSub.getPos(), arr);
}


float RepulsivePotentialFish(Pesce PesceGen, Pesce PesceSub) //il primo pesce genera il potenziale il secondo lo subisce
{

	return RepulsivePotenzialFish(PesceGen.getPos(), PesceSub.getPos());
}

void AttractiveForcesSchool(vector<pair<int, int>> s, vector<Pesce> p, int indexPerceivedSchools, int indexP, float* arr) //calcola la media della posizone dei pesci del banco(centro) e la velocità media poi fa il conto delle dimensioni massime del banco
{
	float AvgPosSchool[3] = { 0,0,0 };
	float AvgVelSchool[3] = { 0,0,0 };
	float r = 1;
	float maxR[3] = { 0,0,0 };
	float dim = 0;
	//calcola pos e vel media del banco (questa parte è da spostare tra le funzioni del banco)
	for (int k = 0; k < s.size(); k++)
		if (s[k].first == indexPerceivedSchools) {
			dim++;
			for (int i = 0; i < 3; i++) {
				AvgPosSchool[i] += p[s[k].second].getPos()[i];
				AvgVelSchool[i] += p[s[k].second].getVel()[i];
			}
		}
	for (int i = 0; i < 3; i++) {
		AvgPosSchool[i] = AvgPosSchool[i] / dim;
		AvgVelSchool[i] = AvgVelSchool[i] / dim;
	}
		//trova la distanza massima lungo un asse dal centro
	for (int k = 0; k < s.size(); k++)
		if (s[k].first == indexPerceivedSchools) {
			for (int i = 0; i < 3; i++) {
				maxR[i] = maxR[i] > abs(p[s[k].second].getPos()[i] - AvgPosSchool[i]) ?
					maxR[i] : abs(p[s[k].second].getPos()[i] - AvgPosSchool[i]);
				r = maxR[i] > r ? maxR[i] : r;
			}
		}
	AttractiveForcesSchool(AvgPosSchool, AvgVelSchool, p[indexP].getPos(), r, arr, 3);
}

int WeightTot(vector<pair<int, int>> school) {
	int pesoTot = 0;
	for (int i = 0; i < school.size(); i++)
		if (school[i].first != -1)
			pesoTot++;
	return pesoTot;
}
int Weight(vector<pair<int, int>> school, int indexS)
{
	int peso = 0;
	for (int i = 0; i < school.size(); i++) 
		if (indexS == school[i].first)
			peso++;
	return peso;
}

bool seenSchools(vector<pair<int, int>> s, vector<Pesce> p, vector<int>& ps, int pesce) {
	int indexS, indexP, compIndexS, compIndexP;
	indexS = indexP = compIndexS = compIndexP = -1;
	ps.clear();
	for (int i = 0; i < s.size(); i++) {
		//estraggo l'indice del banco di cui fa parte il pesce
		indexS = s[i].first;
		if (indexS != compIndexS) {
			indexP = s[i].second;
			if (indexP != pesce) {
				if (dist(p[indexP].getPos(), p[pesce].getPos()) < MinDist) {
					ps.push_back(indexS);
					compIndexS == indexS;
				}
			}
		}
	}
}