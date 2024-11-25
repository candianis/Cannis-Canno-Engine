#include "ccpch.h"
#include <Cannis.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SandboxSystem : public Cannis::Subsystem {
public:
	SandboxSystem() : Cannis::Subsystem("Sandbox System") {
		CC_CLIENT_WARN("Initiating SandboxSystem");
	}

	void Start(std::shared_ptr<Cannis::WorldCoordinator>& p_world) {
		Cannis::EntityHandle f22(p_world, "F22");

		f22.AddComponent<Cannis::ModelComponent>("../Engine/assets/3DModels/f22.obj");
		f22.GetComponent<Cannis::ModelComponent>().model->AddTexture(0, "../Engine/assets/Textures/f22.png");
		f22.AddComponent<Cannis::MaterialComponent>(Cannis::ShaderImplementation::Blinn_Phong ,glm::vec3(0.5f), 64.0f);
	
		f22.SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
		f22.SetRotation(glm::vec3(45.0f, 90.0f, 0.0f));
		f22.SetScale(glm::vec3(0.5f));

		Cannis::EntityHandle light(p_world, "Light");
		light.SetPosition(glm::vec3(0, 10, 0));
		light.AddComponent<Cannis::LightComponent>(glm::vec3(0), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));

		Cannis::EntityHandle efa(p_world, "EFA");
		efa.AddComponent<Cannis::ModelComponent>("../Engine/assets/3DModels/efa.obj");
		efa.GetComponent<Cannis::ModelComponent>().model->AddTexture(0, "../Engine/assets/Textures/efa.png");
		efa.AddComponent<Cannis::MaterialComponent>(Cannis::ShaderImplementation::Blinn_Phong, glm::vec3(0.5), 64.0f);

		efa.SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
		efa.SetRotation(glm::vec3(45.0f, 90.0f, 0.0f));
		efa.SetScale(glm::vec3(0.5f));
	}

	void Update(Cannis::ComponentManager& p_componentManager, const Cannis::Timestep p_timestep) override {
		if (Cannis::Input::IsKeyPressed(CC_KEY_G))
			CC_CLIENT_INFO("G key is pressed");
	}

	void OnUIRender() override {
		
	}

	void Shutdown() override {
		CC_CLIENT_INFO("Shutdown from Sandbox");
	}

private:
	// ------ All variables go here ----- //
};

class Sandbox : public Cannis::Application {
public:
	Sandbox() {
		//GetCoordinator()->AddSubsystem<SandboxSystem>();
		CC_CLIENT_ERROR("Testing");
		AddSubsystem<SandboxSystem>();

		auto& sandbox = GetCoordinator()->GetSubsystem<SandboxSystem>();
		sandbox->Start(GetCoordinator());
	}

	~Sandbox() {

	}
};

Cannis::Application* Cannis::CreateApplication() {
	return new Sandbox();
}