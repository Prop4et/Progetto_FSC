#include "School.h"
#include "define.h"

School::School(Pesce p) {
	for (int i = 0; i < DIMARR; i++) {
		center[i] = p.getPos()[i];
		vel[i] = p.getVel()[i];
	}
}

void School::setVel(float* arr) {
	for (int j = 0; j < 3; j++)
		vel[j] = arr[j];
}

void School::setCenter(float* arr) {
	for (int j = 0; j < 3; j++)
		center[j] = arr[j];
}