#pragma once 

#ifdef CC_PLATFORM_WINDOWS

extern Cannis::Application* Cannis::CreateApplication();

int main(int argc, char** argv) {
	Cannis::Log::Init();

	auto app = Cannis::CreateApplication();
	app->Run();
	delete app;
}

#endif