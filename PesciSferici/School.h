#pragma once
#include "Frame.h"
#include <stdlib.h>     
#include <time.h>
#include <vector>
#include <math.h>
#include "Pesce.h"
#include "utilities.h"

/*Class: School
* Description: classe che descrive un banco di pesci
* cambiamo cose, mettiamo una coppia nel vector con -1 nel campo del banco per i pesci che muoiono nel primo campo della coppia
* Attributes:
*	school: vector di classe pesce
*	dir: array delle direzioni verso le quali si può muovere il banco
*Methods:
*	i primi tre sono costruttori, il primo vuoto per dovere, il secondo passando solo un pesce, il terzo passando un vector di pesci
*	setDir: setter per l'array di direzioni
*	addPesce: aggiunge un pesce al vector
*	getShoal: restituisce il vector contenente tutti i pesci del banco
*	computeAVGDir: calcola la direzione "media" del banco dei pesci (per ora coordinate cartesiane)
*/
class School {
private:
	vector<pair<int, int>> school;
	//Pesce p[FISHNUMBER];
	vector<Pesce> p;
	float dir[3] = { 0,0,0 };
	float dimensions[3] = { 0,0,0 }; //dimensioni del banco (lunghezza, larghezza, altezza, modellato come un cilindro
	float max[3] = { 0, 0, 0 };
	float min[3] = { 0, 0, 0 };
	float centro[3] = { 0, 0, 0 } ; //fulcro attorno al quale i pesci si stringono in presenza di un predatore
	float theta = 0; //angolo rispetto senza z
public:
	School();
	void setDir(float* arr);
	void addPesce();
	vector<pair<int, int>> getSchool() { return school; }
	vector<Pesce> getP() { return p; }
	void Nuota();
	void Merge();
	void orderVector();
};
