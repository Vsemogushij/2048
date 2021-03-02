#include "Application.h"

int main() {
	
	Application* app = Application::Initilize();
	app->start();
	delete app;
	return 0;
}