#include <Cannis.h>

class Sandbox : public Cannis::Application {
public:
	Sandbox() {
		
	}

	~Sandbox() {

	}
};

Cannis::Application* Cannis::CreateApplication() {
	return new Sandbox();
}