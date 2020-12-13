#include "School.h"
#include <vector>
#include <algorithm>
School::School() {
	float pos[FISHNUMBER][3];
	float vel[FISHNUMBER][3];
	float x, y, z, vx, vy, vz;
	x = y = z = vx = vy = vz = 0;
	for (int i = 0; i < FISHNUMBER; i++) {
		pos[i][0] = x;
		pos[i][1] = y;
		pos[i][2] = z;
		x += 2;
		y += 2;
		srand(time(NULL));
		vx = rand() % 10;
		vy = rand() % 10;
		vel[i][0] = vx;
		vel[i][1] = vy;
		vel[i][2] = 0;
		p.push_back(Pesce(pos[i], vel[i]));
		school.push_back(pair<int, int>(i, i));
	}
}

void School::addPesce()
{ 
	float x, y, z, vx, vy, vz;
	//generare posizioni plausibili con le posizioni attuali del banco
	x = y = z = vx = vy = vz = 0;
	float pos[3];
	float vel[3];
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	srand(time(NULL));
	vx = rand() % 10;
	vy = rand() % 10;
	vel[0] = vx;
	vel[1] = vy;
	vel[2] = 0;
	//estraggo l'ultimo index dei banchi e l'ultimo index dei pesci (in realta' cosi' facendo posso mettere un numeero di pesci pari a MAXINT)
	int indexS = school.back().first;
	int indexP = school.back().second;
	//inserisco il pesce nel vector dei pesci e l'indice nel vector dei banchi
	p.push_back(Pesce(pos, vel));
	school.push_back(pair<int, int>(indexS+1, indexP));
}
void School::Nuota() {
	for (int i = 0; i < p.size(); i++) {
		p[i].Nuota();
	}
}

void School::Merge() {

	int indexS, indexP, compIndexS, compIndexP;
	indexS = indexP = compIndexS = compIndexP = -1;
	for (int i = 0; i < school.size() - 1; i++) {
		//estraggo l'indice del banco di cui fa parte il pesce
		indexS = school[i].first;
		if (indexS != -1) {
			//estraggo l'indice del pesce
			indexP = school[i].second;
			for (int j = i + 1; j < school.size(); j++) {
				compIndexS = school[j].first;
				if (compIndexS != indexS) {
					compIndexP = school[j].second;
					//se la distanza fra i due pesci
					if (dist(p[indexP].getPos(), p[indexP].getPos()) < MinDist)
						//assegno il minimo tra i due indici se i pesci fanno parte dello stesso banco
						//la funzione minimo viene applicato perche' il vector non ha valori monotoni crescenti nel primo campo della coppia
						//mentre nel secondo si'
						//niente sche c'ho messo il sort ora e' molto carino pero' il min ce lo lascio comunque
						school[j].first = min(indexS, compIndexS);
				}
			}
		}
	}
	sort(school.begin(), school.end());
}

/*void School::setDir(float* arr) {
	for (int i = 0; i < 3; i++) dir[i] = arr[i];
}*/
/*
void School::computeAVGDir() {
	int i = 0;
	float avgcentro[3] = { 0,0,0 };
	for (int j = 0; j < school.size(); j++) {
		for (i = 0; i < 3; i++)
			avgcentro[i] += school[j]->getPos()[i];
	}
	for (i = 0; i < 3; i++) {
		avgcentro[i] = avgcentro[i] / school.size();
		//printf("%f ", avgcentro[i]);
	}
	printf("\n");
}
*/
//TODO: calcolare l'asse per centrare il banco di pesci
//ossia calcolare la lunghezza del banco (EZ) e calcolare l'angolo della direzione media del banco (?)
//come se calcola l'angolo, in base a cosa? Che poi in realtà sono due angoli, uno tra x,z e uno tra x,y o z,y dipende

void draw_direction(float x, float y, float z) {
	glColor3f(1, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0); glVertex3f(x, y, z);
	glEnd();
}
/*
void School::Merge(School S)
{
	for (int i = 0; i < S.getSchool().size(); i++)
		school.push_back(S.getSchool()[i]);
}*/
/*
vector<School> School::split()
{
	vector<School> Singoletti;
	for (int j = 0; j < school.size(); j++)
		Singoletti.push_back(School(school[j]));
	return Singoletti;
}*/









