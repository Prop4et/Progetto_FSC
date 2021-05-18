#include "School.h"



School::School(vector<Pesce*> s) {
	for (int i = 0; i < s.size(); i++)
		school.push_back(s[i]);
	SetPosAndVel();
}


void School::SetPosAndVel() {
	for (int i = 0; i < 3; i++)
	{
		pos[i] = 0;
		vel[i] = 0;
		for (int j = 0; j < school.size(); j++)
		{
			pos[i] += school[j]->getPos()[i];
			vel[i] += school[j]->getVel()[i];
		}
		if (school.size())
		{
			pos[i] = pos[i] / school.size();
			vel[i] = vel[i] / school.size();
		}
	}
}

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

void School::DrawSchool()
{	
	float avgvel[3] = { 0,0,0 };
	for (int i = 0; i < school.size(); i++)
	{
		school[i]->Nuota();
		glPushMatrix();
		glTranslated(school[i]->getPos()[0], school[i]->getPos()[1], school[i]->getPos()[2]);
		glCallList(SFERA);
		glPopMatrix();
	}

}

void School::Merge(School S)
{
	for (int i = 0; i < S.getSchool().size(); i++)
		school.push_back(S.getSchool()[i]);
}

vector<School> School::split()
{
	vector<School> Singoletti;
	for (int j = 0; j < school.size(); j++)
		Singoletti.push_back(School(school[j]));
	return Singoletti;
}






