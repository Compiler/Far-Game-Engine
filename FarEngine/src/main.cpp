#include <FarCore.h>
int main(int argc, char* argv[]){


	far::FarCore* core = new far::FarCore();
	
	
	core->load();
	while(core->isRunning()){
		core->update();
		core->render();
	}
	core->unload();
	
}


	


	