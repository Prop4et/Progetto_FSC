#include <FL/Fl.H>
#include <stdio.h>

#include "Ocean.h"
#include "form.h"
#include "frame.h"

using namespace std;
//---------------------------------
/*std::condition_variable canPop;
std::condition_variable canPush;
std::mutex mPush;
std::mutex mPop;
std::queue<vector<float*>> Q;*/
//---------------------------------
extern Frame* scene;
//---------------------------------
void idle_cb(void*)
{
	scene->redraw();
	//Fl::repeat_timeout(1 / 120, idle_cb);
}

// ********************************************************************************************************
int main(int argc, char** argv) {
	CreateMyWindow();
//	Fl::add_timeout(1 / 120, idle_cb);
	Fl::add_idle(idle_cb, 0);
	return Fl::run();
}
