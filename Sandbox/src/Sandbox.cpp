#include <Cannis.h>

class Sandbox : public CannisCanno::Application {
public:
	Sandbox() {
		printf("Hello over there");
	}

	~Sandbox() {

	}
};

CannisCanno::Application* CannisCanno::CreateApplication() {
	return new Sandbox();
}