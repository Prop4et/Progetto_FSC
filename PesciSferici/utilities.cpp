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

