#include "utilities.h"
#include "define.h"
float dist(float* pos1, float* pos2) //calcolo della distanza tra due punti FUNZIONA 
{
	float a = 0;
	for (int i = 0; i < 3; i++)
		a += ((pos1[i] - pos2[i]) * (pos1[i] - pos2[i]));
	a = sqrtf(a);
	return a;
}

float modul3(float* Anyvect)//calcola il modulo
{
	float a = 0;
	for (int i = 0; i < 3; i++) {
		a += (Anyvect[i] * Anyvect[i]);
	}
	a = sqrtf(a);
	return a;
}

void FindDir(float* Anyvect, float* Directions) // trova theta, phi per le coordinate sferiche, il primo risultato e' l'angolo sul piano, il secondo e' l'angolo con le zeta
{								//se siamo in 0,0,0 da {0,0}
	float a = modul3(Anyvect);
	if (a > -0.00001f && a < 0.00001f)
		Directions[0] = Directions[1] = 0;
	if (Anyvect[0] >= -0.00001f && Anyvect[1] <= 0.00001f)
	{
		if (Anyvect[1] > 0)
			Directions[0] = PIGRECO / 2.f;
		if (Anyvect[0] <= 0)
			Directions[0] = 3.f * PIGRECO / 2.f;
	}
	if (Anyvect[0] > 0.00001f)
	{
		if (Anyvect[1] >= 0)
			Directions[0] = atanf(Anyvect[1] / Anyvect[0]);
		if (Anyvect[1] < 0)
			Directions[0] = (atanf(Anyvect[1] / Anyvect[0]) + 2 * PIGRECO);
	}
	if (Anyvect[0] < -0.00001f)
	{
		if (Anyvect[1] >= 0)
			Directions[0] = (atanf(Anyvect[1] / Anyvect[0]) + 2 * PIGRECO);
		if (Anyvect[1] < 0)
			Directions[0] = (atanf(Anyvect[1] / Anyvect[0]) + PIGRECO);
	}
	Directions[1] = acosf(Anyvect[2] / a);
}

float ProdottoScalare3(float* AnyVet1, float* AnyVet2)
{
	float a = 0;
	for (int i = 0; i < 3; i++)
		a += (AnyVet1[i] * AnyVet2[i]);
	return a;
}



/*void mySplit(vector<School>& Oceano) {
	int j = 0;
	for (int i = 0; i < Oceano.size(); i++)
		if (Oceano[i].getSchool().size() > 1) {
			for (j = 0; j < Oceano[i].getSchool().size() - 1; j++) {
				Pesce* fish = Oceano[i].getSchool().at(j);
				if (dist(fish->getPos(), Oceano[i].getSchool()[j + 1]->getPos()) <= MinDist)
					break;
			}
			if (j != Oceano[i].getSchool().size()) {
				Oceano[i].getSchool().erase
			}
		}
}*/


void Merge(vector<School>& Oceano)
{
	//sta cosa va rifatta, perche' potrebbe succedere che un pesce in un banco si stacchi dal banco per unirsi ad un altro mentre altri pesci no
	//quindi si deve fare magari che se piu' della meta' del banco vede il 
	for (int a = 0; a < Oceano.size(); a++) {
		for (int b = 0; b < Oceano[a].getSchool().size(); b++)
		{
			Pesce* fish = Oceano[a].getSchool().at(b);
			for (int i = 0; i < Oceano.size(); i++)
				if (a != i)
					for (int k = 0; k < Oceano[i].getSchool().size(); k++)
						if (dist(fish->getPos(), Oceano[i].getSchool()[k]->getPos()) < MinDist)
						{
							Oceano[a].Merge(Oceano[i]);
							Oceano.erase(Oceano.begin() + i);
						}
		}
	}
}