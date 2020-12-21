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
		//srand(time(NULL));
		vx = 2;
		vy = 1;
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
	school.push_back(pair<int, int>(indexS, indexP));
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
					if (dist(p[indexP].getPos(), p[compIndexP].getPos()) < MinDist)
						//assegno il minimo tra i due indici se i pesci fanno parte dello stesso banco
						//la funzione minimo viene applicato perche' il vector non ha valori monotoni crescenti nel primo campo della coppia
						//mentre nel secondo si'
						school[j].first = min(indexS, compIndexS);
				}
			}
		}
	}
	sort(school.begin(), school.end());
}


void School::Split() {
	int nSchool, nTimeDist;
	int indexS, indexP, compIndexS, compIndexP;
	int lastIndex = school.back().first;
	indexS = indexP = compIndexS = compIndexP = -1;
	for (int i = 0; i < school.size() - 1; i++) {
		//estraggo l'indice del banco di cui fa parte il pesce
		indexS = school[i].first;
		if (indexS != -1) {
			//estraggo l'indice del pesce
			nSchool = nTimeDist = 0;
			indexP = school[i].second;
			for (int j = i + 1; j < school.size(); j++) {
				compIndexS = school[j].first;
				if (compIndexS == indexS) {
					nSchool++;
					compIndexP = school[j].second;
					//se la distanza fra i due pesci
					if (dist(p[indexP].getPos(), p[compIndexP].getPos()) > MinDist)
						nTimeDist++;
				}
			}
			//scorro l'array per mettere il nuovo elemento che ho tirato fuori in fondo, cosi' da mantenere l'ordine
			if (nTimeDist == nSchool) {
				lastIndex++;
				int appI = i;
				int appP = school[i].second;
				for (int j = i + 1; j < school.size(); j++) {
					school[appI].first = school[j].first;
					school[appI].second = school[j].second;
					appI++;
				}
				school[appI].first = lastIndex;
				school[appI].second = appP;
			}
		}
	}
}

void School::SetAccelerazioni()
{
	vector<int> perceivedSchools;
	int pesoTot = WeightTot(school);
	for (int i = 0; i < school.size(); i++) {

		float accTot[3] = { 0.f, 0.f, 0.f };
		float forza[3];
		//----------------------
		//indice del banco in esame
		int indexS = school[i].first;
		//indice del pesce appartenente al banco in esame
		int indexP = school[i].second;
		//int pesoBanco = Weight(s.getSchool(), indexS, &i);
		seenSchools(school, p, perceivedSchools, indexP);
		for (int j = 0; j < perceivedSchools.size(); j++) {
			int pesoBanco = Weight(school, perceivedSchools[j]);
			AttractiveForcesSchool(school, p, perceivedSchools[j], indexP, forza);
			for (int u = 0; u < 3; u++) {
				accTot[u] += (forza[u] / massa) * pesoBanco / pesoTot;
			}
			//consideriamo i potenziali repulsivi quindi escludiamo di star considerando lo stesso pesce
			for (int k = 0; k < school.size(); k++) {
				//se il pesce preso in considerazione fa parte del banco preso in considerazione e non e' il pesce originale e si trova ad una distanza apprezzabile dal pesce originale
				if ((school[k].first == perceivedSchools[j]) && (indexP != school[k].second) && (dist(p[indexP].getPos(), p[school[k].second].getPos()) < MinDist)) {
					RepulsiveForcesFish(p[school[k].second], p[indexP], forza);
					for (int u = 0; u < 3; u++)
						accTot[u] += forza[u] / massa;
					for (int h = 0; h < 8; h++)
					{
						float* PosHole = p[school[k].second].getHoles()[h].getPos();
						AttractiveForcesHole(p[indexP].getPos(), PosHole, forza);
						for (int u = 0; u < 3; u++)
							accTot[u] += forza[u] / massa;
					}
				}
			}
		}
		p[indexP].setAcc(accTot);
	}
}

/*void School::setDir(float* arr) {
	for (int i = 0; i < 3; i++) dir[i] = arr[i];
}*/

void School::computeAVGDir(int index, float* centro) {
	int dim = 0;
	for (int i = 0; i < school.size(); i++) {
		//cout << school[i].first;

		if (school[i].first == index) {
			for (int j = 0; j < DIMARR; j++)
				centro[j] += p[school[i].second].getPos()[j];
			dim++;
 		}
	}
	for (int j = 0; j < DIMARR; j++) {
		centro[j] /= dim;
	}
}

//TODO: calcolare l'asse per centrare il banco di pesci
//ossia calcolare la lunghezza del banco (EZ) e calcolare l'angolo della direzione media del banco (?)
//come se calcola l'angolo, in base a cosa? Che poi in realtà sono due angoli, uno tra x,z e uno tra x,y o z,y dipende





