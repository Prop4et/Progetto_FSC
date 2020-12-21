#include "Pesce.h"

class School {
private:
	//float dir[3] = { 0, 0, 0 };
	float vel[3] = { 0, 0, 0 };
	float center[3] = { 0, 0, 0 };
	//float extension[3] = { 0, 0 ,0 };
public:
	School() { };
	School(Pesce p);
	void setVel(float *arr);
	void setCenter(float *arr);
	float* getVel() { return vel; }
	float* getCenter() { return center; }
};