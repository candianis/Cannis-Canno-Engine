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
		//f22.AddComponent<Cannis::MaterialComponent>(Cannis::ShaderImplementation::Blinn_Phong ,glm::vec3(0.5f), 64.0f);
	
		//f22.SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
		//f22.SetRotation(glm::vec3(45.0f, 90.0f, 0.0f));
		//f22.SetScale(glm::vec3(0.5f));

		Cannis::EntityHandle f22PBR(p_world, "F22 (PBR)");
		f22PBR.AddComponent<Cannis::ModelComponent>("../Engine/assets/3DModels/f22.obj");
		f22PBR.GetComponent<Cannis::ModelComponent>().model->AddTexture(0, "../Engine/assets/Textures/f22.png", Cannis::TextureType::AlbedoTex);
		f22PBR.GetComponent<Cannis::ModelComponent>().model->AddTexture(0, "../Engine/assets/Textures/rustediron1-alt2-Unreal-Engine/rustediron2_normal.png", Cannis::TextureType::NormalTex);
		f22PBR.GetComponent<Cannis::ModelComponent>().model->AddTexture(0, "../Engine/assets/Textures/rustediron1-alt2-Unreal-Engine/rustediron2_metallic.png", Cannis::TextureType::MetallicTex);
		f22PBR.GetComponent<Cannis::ModelComponent>().model->AddTexture(0, "../Engine/assets/Textures/rustediron1-alt2-Unreal-Engine/rustediron2_roughness.png", Cannis::TextureType::RoughnessTex);
		f22PBR.AddComponent<Cannis::PBRMaterialComponent>(glm::vec3(0.5f, 0.0f, 0.0f));

		f22PBR.SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
		f22PBR.SetScale(glm::vec3(0.5));

		Cannis::EntityHandle light1(p_world, "Light1");
		light1.SetPosition(glm::vec3(0, 10, 0));
		light1.AddComponent<Cannis::PBRLightComponent>(glm::vec3(0), glm::vec3(1.0f, 1.0f, 1.0f));
		light1.SetPosition(glm::vec3(0.0f, 1.0f, .0f));

		Cannis::EntityHandle light2(p_world, "Light2");
		light2.SetPosition(glm::vec3(0, 10, 0));
		light2.AddComponent<Cannis::PBRLightComponent>(glm::vec3(0), glm::vec3(0.2f, 0.2f, 0.2f));
		light2.SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));

		Cannis::EntityHandle light3(p_world, "Light3");
		light3.SetPosition(glm::vec3(0, 10, 0));
		light3.AddComponent<Cannis::PBRLightComponent>(glm::vec3(0), glm::vec3(0.2f, 0.2f, 0.2f));
		light3.SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));

		Cannis::EntityHandle light4(p_world, "Light4");
		light4.SetPosition(glm::vec3(0, 10, 0));
		light4.AddComponent<Cannis::PBRLightComponent>(glm::vec3(0), glm::vec3(0.2f, 0.2f, 0.2f));
		light4.SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));

		//Cannis::EntityHandle f22BP(p_world, "F22 (Blinn_Phong)");
		//f22BP.AddComponent<Cannis::ModelComponent>("../Engine/assets/3DModels/f22.obj");
		//f22BP.GetComponent<Cannis::ModelComponent>().model->AddTexture(0, "../Engine/assets/Textures/f22.png", Cannis::TextureType::DiffuseTex);
		//f22BP.AddComponent<Cannis::MaterialComponent>(Cannis::ShaderImplementation::Blinn_Phong, glm::vec3(0.5), 64.0f);

		//f22BP.SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
		//f22BP.SetScale(glm::vec3(0.5f));

		//Cannis::EntityHandle lightBP(p_world, "Light (Blinn_Phong)");
		//lightBP.AddComponent<Cannis::LightComponent>();
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