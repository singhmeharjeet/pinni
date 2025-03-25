#include <Application.h>
namespace Pinni {

Application::Application() {
}

Application::~Application() {
}

void Application::Run() {
	logger.Log("Application is running...");

	int i = 0;
	while (i < 10) {
		if (i % 2 == 0) {
			logger.Warn("i is even");
		} else {
			logger.Error("i is odd");
		}
		i++;
	}
}

}  // namespace Pinni
