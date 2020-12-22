#include <FL/Fl.H>
#include <stdio.h>

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <deque>

#include "Ocean.h"
//#include "form.h"
//#include "frame.h"

using namespace std;
//---------------------------------
std::condition_variable canPop;
std::condition_variable canPush;
std::mutex mPush;
std::mutex mIndex;
std::mutex mPop;
std::queue<vector<float*>> Q;
//---------------------------------
//extern Frame* scene;
//---------------------------------
/*void idle_cb(void*)
{
	scene->redraw();
	//Fl::repeat_timeout(1 / 120, idle_cb);
}*/
void compute(Ocean &o) {
	int index;
	std::unique_lock<std::mutex> lck(mIndex, std::defer_lock);
	//estraggo l'indice del pesce su cui devo lavorare in mutua esclusione per il numero di iterazioni che voglio fare vabè
	for (int iter = 0; iter < ITNUMBER; iter++) {
		lck.lock();
		index = o.sharedIndex;
		o.sharedIndex++;
		if (o.sharedIndex == o.getP().size()) o.sharedIndex = 0;
		lck.unlock();
		if (o.getOcean()[index] != -1) {
			o.Merge(index);
		}
	}

	//faccio i vari calcoli relativi al pesce e poi metto le posizioni nella coda
	//se il pesce non è morto
	
}
// ********************************************************************************************************
int main(int argc, char** argv) {
	//CreateMyWindow();
//	Fl::add_timeout(1 / 120, idle_cb);
	//Fl::add_idle(idle_cb, 0);
	Ocean o = Ocean();
	std::thread producer[1];
	for(int i = 0; i < 1; i++) producer[i] = std::thread(compute, std::ref(o));
	for (int i = 0; i < 1; i++) producer[i].join();
	cout << "joined\n";
	for (int i = 0; i < o.getOcean().size(); i++) {
		cout << o.getOcean()[i] << " ";
	}
	//Fl::run();
	return 0;
}
