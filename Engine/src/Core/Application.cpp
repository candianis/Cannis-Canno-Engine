#include "Application.h"

#include <stdio.h>

namespace CannisCanno {
	Application::Application() {
		printf("Hello here");
	}

	Application::~Application() {

	}

	void Application::Run() {
		printf("Hello there");
		while (true);
	}
}