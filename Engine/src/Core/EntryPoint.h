#pragma once 

#ifdef CC_PLATFORM_WINDOWS

extern Cannis::Application* Cannis::CreateApplication();

int main(int argc, char** argv) {
	Cannis::Log::Init();
	CC_CORE_WARN("Initialized Log!");
	int a = 5;
	CC_CLIENT_WARN("Initialized Log! Var={0}", a);

	printf("Cannis Canno Engine");
	auto app = Cannis::CreateApplication();
	app->Run();
	delete app;
}

#endif