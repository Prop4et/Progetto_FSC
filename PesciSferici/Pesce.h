#define _USE_MATH_DEFINES
#include "Frame.h"
#include "Hole.h"
#include <stdlib.h>     
#include <vector>
#include <stdlib.h>
#include <math.h>
#include "define.h"
//#include "utilities.h"
//#include "Potenziali.h"

#pragma once
//#define L 5
//#define SFERETTA 7


using namespace std;

/*Class: Pesce, descrive un pesce
*
* Attributes:
*	pos: vector delle posizioni, potrebbe essere array
*	vel: vector delle velocità, potrebbe essere array
*	acc: vector delle accelerazioni, potrebbe essere array
* TODO: aggiungere i buchi in cui possono buttarsi gli altri pesci
* Methods:
*	Pesce costruttore vuoto
*	Pesce(vector, vector, vector) costruttore che inizializza le velocità, posizione e accelerazione del pesce
*	setters and getters
*	Nuota: metodo che calcola lo spostamento del pesce
*/
class Pesce {
private:
	float pos[DIMARR];
	float vel[DIMARR];
	float acc[DIMARR];
	Hole holes[8];
	float theta;
	float omega[DIMARR]{0,0,0};
	float omegapunto[DIMARR]{ 0,0,0 };
public:
	Pesce();
	Pesce(float* p, float* v, float* a);
	Pesce(float* p, float* v);
	void setPos(float* p);
	void setVel(float* v);
	void setAcc(float* a);
	void setTheta(float t);
	void setOmegaPunto(float*);
	float* getPos() { return pos; }
	float* getVel() { return vel; }
	float* getAcc() { return acc; }
	Hole* getHoles() { return holes; }
	float getTheta() { return theta; }
	void Nuota();
	void NuotainCerchio(float& t, int i);
	float computeTheta();
	void computePolarization();
	void computePolJack();
};
