#pragma once
#include "Frame.h"
#include <stdlib.h>     
#include <time.h>
#include <vector>
#include <math.h>
#include "Pesce.h"



/*Class: School
* Description: classe che descrive un banco di pesci
*
* Attributes:
*	school: vector di classe pesce
*	vel: array delle velocità medie del banco
*Methods:
*	i primi tre sono costruttori, il primo vuoto per dovere, il secondo passando solo un pesce, il terzo passando un vector di pesci
*	setVel: setter per l'array di velocità
*	addPesce: aggiunge un pesce al vector
*	getShoal: restituisce il vector contenente tutti i pesci del banco
*	computeAVGVel: calcola la velocità "media" del banco dei pesci (per ora coordinate cartesiane)
*/
class School {
private:
	vector<Pesce*> school;
	float pos[3];
	float vel[3];
	float dimensions[3]; //dimensioni del banco (lunghezza, larghezza, altezza, modellato come un cilindro
	float max[3] = { 0, 0, 0 };
	float min[3] = { 0, 0, 0 };
	float theta; //angolo rispetto senza z
public:
	School() { SetPosAndVel(); }
	School(Pesce* p) { school.push_back(p); SetPosAndVel(); }
	School(vector<Pesce*> s);
	void addPesce(Pesce* p) { school.push_back(p); }
	vector<Pesce*> getSchool() { return school; }
	float* getPos() { return pos; }
	float* getVel() { return vel; }
	void SetPosAndVel();
	void Merge(School S);
	vector<School> split();
	void DrawSchool();
};
