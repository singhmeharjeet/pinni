
#include <Pinni.h>

class Sandbox : public Pinni::Application {};

Pinni::Application* CreateApplication() {
	auto app =  new Sandbox();
	app->Run();
	return app;
}
