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
		Cannis::EntityHandle cube(p_world, "Cube");
		float vertices[] = {
		  -1.0f,1.0f,0.0f,
		  -1.0f,-1.0f,0.0f,
		  1.0f,1.0f,0.0f,
		  1.0f,-1.0f,0.0f,
		  -1.0f,1.0f,-1.0f,
		  -1.0f,-1.0f,-1.0f,
		  1.0f,1.0f,-1.0f,
		  1.0f,-1.0f,-1.0f
		};

		uint32_t indices[] = {
		  0, 2, 3, 0, 3, 1,
		  2, 6, 7, 2, 7, 3,
		  6, 4, 5, 6, 5, 7,
		  4, 0, 1, 4, 1, 5,
		  0, 4, 6, 0, 6, 2,
		  1, 5, 7, 1, 7, 3,
		};

		Cannis::BufferLayout bufferLayout = {
			{ "a_Position", Cannis::ShaderDataType::Float3 },
			{ "a_Color", Cannis::ShaderDataType::Float4}
		};

		cube.AddComponent<Cannis::ModelComponent>(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(uint32_t), bufferLayout);

		std::string vertexSourceSquare = "../Engine/assets/Shaders/FlatColor/flatColor.vert";
		std::string fragmentSourceSquare = "../Engine/assets/Shaders/FlatColor/flatColor.frag";
		cube.AddComponent<Cannis::ShaderComponent>(vertexSourceSquare, fragmentSourceSquare);

		cube.SetRotation(glm::vec3(45.0f, 90.0f, 0.0f));
		cube.SetScale(glm::vec3(0.5f));
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