#pragma once

#include <Logger.h>

#include <memory>

namespace Pinni {

class Application {
	Logger& logger = Logger::GetInstance();

	public:
	Application();
	~Application();
	virtual void Run();
	bool SmokeTest() { return true; };
};

}  // namespace Pinni
