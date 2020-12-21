#pragma once
#include "Frame.h"
#include <stdlib.h>     
#include <time.h>
#include <vector>
#include <math.h>
#include "Pesce.h"
#include "utilities.h"
#include "Potenziali.h"
#include "School.h"
#include <list>
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
class Ocean {
private:
	vector<pair<int, int>> ocean;
	list<School> s;
	list<School>::iterator itS;
	vector<Pesce> p; 
	//se ho il tutto fatto cosi' o mi faccio un vector di tutto oppure calcolo on the fly, vediamo, per ora e' on the fly
public:
	Ocean();
	//void setDir(float* arr);
	void addPesce();
	vector<pair<int, int>> getOcean() { return ocean; }
	vector<Pesce> getP() { return p; }
	list<School> getS() { return s; }
	void Nuota();
	void Merge();
	void Split();
	void SetAccelerazioni();
	void computeAVGDir(int i, float* centro);
};
