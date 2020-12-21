#include <FL/Fl.H>
#include <stdio.h>

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <deque>

#include "Ocean.h"
#include "form.h"
#include "frame.h"

using namespace std;
//---------------------------------
std::condition_variable canPop;
std::condition_variable canPush;
std::mutex mPush;
std::mutex mPop;
std::queue<float* > Q;
//---------------------------------
extern Frame* scene;
//---------------------------------
void idle_cb(void*)
{
	scene->redraw();
	Fl::repeat_timeout(1 / 120, idle_cb);
}
//---------------------------------
void graphics()
{
	CreateMyWindow();
	Fl::add_timeout(1 / 120, idle_cb);
	//Fl::add_idle(idle_cb, 0);
	Fl::run();
}

// ********************************************************************************************************
int main(int argc, char** argv) {
	Ocean o = Ocean();
	std::thread consumer(graphics);
	while (1) {
		o.Merge();
		o.Split();
		o.SetAccelerazioni();
		o.Nuota();
		for(int i = 0; i < FISHNUMBER; i++)
			Q.push(o.getP()[i].getPos());
	}
	consumer.join();
	/*CreateMyWindow();
	Fl::add_timeout(1 / 120, idle_cb);
//	Fl::add_idle(idle_cb, 0);
	return Fl::run();*/
}
