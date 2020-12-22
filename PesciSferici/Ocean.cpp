#include "Ocean.h"
#include <vector>
#include <algorithm>

Ocean::Ocean() {
	float pos[FISHNUMBER][3];
	float vel[FISHNUMBER][3];
	float x, y, z, vx, vy, vz;
	y = -10;
	x = z = vx = vy = vz = 0;
	for (int i = 0; i < FISHNUMBER; i++) {
		pos[i][0] = x;
		pos[i][1] = y;
		pos[i][2] = z;
		if (i % 10 == 0){
			x += 2;
			y = -10;
		}
		y += 2;
		//srand(time(NULL));
		vx = 0;
		vy = 0;
		vel[i][0] = vx;
		vel[i][1] = vy;
		vel[i][2] = 0;
		Pesce app = Pesce(pos[i], vel[0]);
		p.push_back(app);
		s.push_back(app);
		ocean.insert(pair<int, int>(i, i));

		reversedocean.insert(pair<int, vector<int>>(i, vector<int> (1,i)));
	}
	
}

/*void Ocean::addPesce()
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
	vel[0] = 0;
	vel[1] = 0;
	vel[2] = 0;
	//estraggo l'ultimo index dei banchi e l'ultimo index dei pesci (in realta' cosi' facendo posso mettere un numeero di pesci pari a MAXINT)
	int indexS = ocean.back().first;
	int indexP = ocean.back().second;
	//inserisco il pesce nel vector dei pesci e l'indice nel vector dei banchi
	p.push_back(Pesce(pos, vel));
	ocean.push_back(pair<int, int>(indexS, indexP));
}*/
/*void Ocean::Nuota() {
	itS = s.begin();
	int i = 0;
	float avgVel[3] = { 0, 0, 0 };
	float avgPos[3] = { 0, 0, 0 };
	//calcolo tutte le varie cose dei vari banchi
	while (i < ocean.size() && ocean[i].first == -1)
		i++;
	int indexS = ocean[i].second;
	int nElem = 0;
	while (i < ocean.size()) {
		if (ocean[i].first == indexS) {
			for (int j = 0; j < 3; j++) {
				avgVel[j] += p[indexS].getVel()[j];
				avgPos[j] += p[indexS].getPos()[j];
			}
			nElem++;
		}
		else {
			for (int j = 0; j < 3; j++) {
				avgPos[j] /= nElem;
				avgVel[j] /= nElem;
			}
			(*itS).setCenter(avgPos);
			(*itS).setVel(avgVel);
			itS++;
			for (int j = 0; j < 3; j++) {
				avgPos[j] = 0;
				avgVel[j] = 0;
			}
			nElem = 1;
			indexS = ocean[i].first;
		}
		i++;
	}
	for (int j = 0; j < 3; j++) {
		avgPos[j] /= nElem;
		avgVel[j] /= nElem;
	}
	cout << "\n";
	(*itS).setCenter(avgPos);
	(*itS).setVel(avgVel);
	//faccio nuotare tutti i pesci
	//poi idealmente dentro nuota passo la "direttrice" della direzione del banco e poi i pesci calcolano l'angolo di rotazione in base a quella 
	for (int i = 0; i < ocean.size(); i++) {
		p[ocean[i].second].Nuota();
	}
}*/


void Ocean::Merge(int indexP) {
	int compIndexS = -1;

	//estraggo l'indice del banco di cui fa parte il pesce
	int indexS = ocean[indexP];
	int j = 0;
	bool sameS = true;
	while(j < ocean.size() && !p[indexP].getMerged()) {
		compIndexS = ocean[j];
		if (compIndexS != -1 && compIndexS != indexS) 
			//se la distanza fra i due pesci
			if (dist(p[indexP].getPos(), p[j].getPos()) < MinDist) {
				//resto nel mio banco dato che � pi� grande, fondamentalmente resta invariato
				//if (reversedocean[indexS].size() > reversedocean[compIndexS].size()) {
				//}
					//il mio banco � pi� piccolo quindi cambio
				if (reversedocean[indexS].size() <= reversedocean[compIndexS].size()) { 
					ocean[indexP] = compIndexS;
					reversedocean[compIndexS].push_back(indexP);
					int i = 0;
					while (indexP != reversedocean[indexS][i]) {
						i++;
					}
					reversedocean[indexS].erase(reversedocean[indexS].begin()+i);
					if (reversedocean[indexS].size() == 0) reversedocean.erase(indexS);
				}
					//se sono grossi uguale decido con una probabilit� del 50% di restare o di andare nell'altro
				/*else if (reversedocean[indexS].size() == reversedocean[compIndexS].size()) {
					srand(time(0));
					int p = rand() % 10;
					//if (p < 5) {
						//ocean[indexP] = indexS;
					//}
					if(p>5) {
						ocean[indexP] = compIndexS;
					}
				}*/
				p[indexP].setMerged();
			}
		j++;
	}
}

/*
void Ocean::Split() {
	int indexS, indexP, compIndexS, compIndexP;
	int lastIndex = ocean.back().first;
	indexS = indexP = compIndexS = compIndexP = -1;
	for (int i = 0; i < ocean.size(); i++) {
		//estraggo l'indice del banco di cui fa parte il pesce
		indexS = ocean[i].first;
		bool split = true;
		if (indexS != -1) {
			//estraggo l'indice del pesce
			indexP = ocean[i].second;
			int j = 0;
			while (j < ocean.size() && split) {
				if (j != i) {
					compIndexS = ocean[j].first;
					if (compIndexS == indexS) {
						compIndexP = ocean[j].second;
						//se la distanza fra i due pesci
						if (!dist(p[indexP].getPos(), p[compIndexP].getPos()) > MinDist)
							split = false;
					}
				}
				j++;
			}
			//scorro l'array per mettere il nuovo elemento che ho tirato fuori in fondo, cosi' da mantenere l'ordine
			if (split) {
				lastIndex++;
				int appI = i;
				int appP = ocean[i].second;
				for (int j = i + 1; j < ocean.size(); j++) {
					ocean[appI].first = ocean[j].first;
					ocean[appI].second = ocean[j].second;
					appI++;
				}
				ocean[appI].first = lastIndex;
				s.push_back(p[appP]);
				ocean[appI].second = appP;
			}
		}
	}
}*/
/*
void Ocean::SetAccelerazioni()
{
	vector<int> perceivedSchools;
	int pesoTot = WeightTot(ocean);
	for (int i = 0; i < ocean.size(); i++) {

		float accTot[3] = { 0.f, 0.f, 0.f };
		float forza[3];
		//----------------------
		//indice del banco in esame
		int indexS = ocean[i].first;
		//indice del pesce appartenente al banco in esame
		int indexP = ocean[i].second;
		int pesoBanco = Weight(ocean, indexS);
		seenSchools(ocean, p, perceivedSchools, indexP);
		for (int j = 0; j < perceivedSchools.size(); j++) {
			int pesoBanco = Weight(ocean, perceivedSchools[j]);
			AttractiveForcesSchool(ocean, p, perceivedSchools[j], indexP, forza);
			for (int u = 0; u < 3; u++) {
				accTot[u] += (forza[u] / massa) * pesoBanco / pesoTot;
			}
			//consideriamo i potenziali repulsivi quindi escludiamo di star considerando lo stesso pesce
			for (int k = 0; k < ocean.size(); k++) {
				//se il pesce preso in considerazione fa parte del banco preso in considerazione e non e' il pesce originale e si trova ad una distanza apprezzabile dal pesce originale
				if ((ocean[k].first == perceivedSchools[j]) && (indexP != ocean[k].second) && (dist(p[indexP].getPos(), p[ocean[k].second].getPos()) < MinDist)) {
					RepulsiveForcesFish(p[ocean[k].second], p[indexP], forza);
					for (int u = 0; u < 3; u++)
						accTot[u] += forza[u] / massa;
					for (int h = 0; h < 8; h++)
					{
						float* PosHole = p[ocean[k].second].getHoles()[h].getPos();
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

/*void Ocean::setDir(float* arr) {
	for (int i = 0; i < 3; i++) dir[i] = arr[i];
}*/
/*
void Ocean::computeAVGDir(int index, float* centro) {
	int dim = 0;
	for (int i = 0; i < ocean.size(); i++) {
		//cout << ocean[i].first;

		if (ocean[i].first == index) {
			for (int j = 0; j < DIMARR; j++)
				centro[j] += p[ocean[i].second].getPos()[j];
			dim++;
 		}
	}
	for (int j = 0; j < DIMARR; j++) {
		centro[j] /= dim;
	}
}
*/
//TODO: calcolare l'asse per centrare il banco di pesci
//ossia calcolare la lunghezza del banco (EZ) e calcolare l'angolo della direzione media del banco (?)
//come se calcola l'angolo, in base a cosa? Che poi in realt� sono due angoli, uno tra x,z e uno tra x,y o z,y dipende





