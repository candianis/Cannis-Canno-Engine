#pragma once 

#ifdef CC_PLATFORM_WINDOWS

extern CannisCanno::Application* CannisCanno::CreateApplication();

int main(int argc, char** argv) {
	printf("Cannis Canno Engine");
	auto app = CannisCanno::CreateApplication();
	app->Run();
	delete app;
}

#endif