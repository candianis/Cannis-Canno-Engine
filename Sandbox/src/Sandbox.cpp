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
		//Cannis::EntityHandle f22(p_world, "F22");

		//f22.AddComponent<Cannis::ModelComponent>("../Engine/assets/3DModels/cube.obj");
		//f22.GetComponent<Cannis::ModelComponent>().model->AddTexture(0, "../Engine/assets/Textures/f22.jpg");
		//f22.AddComponent<Cannis::MaterialComponent>(Cannis::ShaderImplementation::Blinn_Phong ,glm::vec3(0.5f), 64.0f);
	
		//f22.SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
		//f22.SetRotation(glm::vec3(45.0f, 90.0f, 0.0f));
		//f22.SetScale(glm::vec3(0.5f));

		Cannis::EntityHandle sphere(p_world, "Sphere");
		sphere.AddComponent<Cannis::ModelComponent>("../Engine/assets/3DModels/square.obj");
		sphere.AddComponent<Cannis::PBRMaterialComponent>();

		Cannis::EntityHandle light1(p_world, "Light 1");
		light1.SetPosition(glm::vec3(0, 10, 0));
		light1.AddComponent<Cannis::PBRLightComponent>(glm::vec3(0), glm::vec3(0.2f, 0.2f, 0.2f));
		light1.SetPosition(glm::vec3(-10.0f, 10.0f, 0.0f));

		Cannis::EntityHandle light2(p_world, "Light 2");
		light2.SetPosition(glm::vec3(0, 10, 0));
		light2.AddComponent<Cannis::PBRLightComponent>(glm::vec3(0), glm::vec3(0.2f, 0.2f, 0.2f));
		light2.SetPosition(glm::vec3(-10.0f, -10.0f, 0.0f));
		
		Cannis::EntityHandle light3(p_world, "Light 3");
		light3.SetPosition(glm::vec3(0, 10, 0));
		light3.AddComponent<Cannis::PBRLightComponent>(glm::vec3(0), glm::vec3(0.2f, 0.2f, 0.2f));
		light3.SetPosition(glm::vec3(10.0f, 10.0f, 0.0f));

		Cannis::EntityHandle light4(p_world, "Light 4");
		light4.SetPosition(glm::vec3(0, 10, 0));
		light4.AddComponent<Cannis::PBRLightComponent>(glm::vec3(0), glm::vec3(0.2f, 0.2f, 0.2f));
		light4.SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));

		//Cannis::EntityHandle sphere2(p_world, "Sphere (2)");
		//sphere2.AddComponent<Cannis::ModelComponent>("../Engine/assets/3DModels/sphere.obj");
		//sphere2.GetComponent<Cannis::ModelComponent>().model->AddTexture(0, "../Engine/assets/Textures/default.jpg");
		//sphere2.AddComponent<Cannis::MaterialComponent>(Cannis::ShaderImplementation::Blinn_Phong, glm::vec3(0.5), 64.0f);

		//sphere2.SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
		//sphere2.SetRotation(glm::vec3(45.0f, 90.0f, 0.0f));
		//sphere2.SetScale(glm::vec3(0.5f));
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