
#pragma once

#include <Application.h>

extern Pinni::Application* CreateApplication();

int main(int argc, char** argv) {
	auto app = CreateApplication();
	app->Run();
	delete app;
}
