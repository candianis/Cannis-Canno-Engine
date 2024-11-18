#include "ccpch.h"
#include <Cannis.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 camera(float p_translate, glm::vec2 const& p_rotate) {
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0f, p_translate));
	view = glm::rotate(view, p_rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, p_rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

	return projection * view * model;
}

class SandboxSystem : public Cannis::Subsystem {
public:
	SandboxSystem() : Cannis::Subsystem("Sandbox System") {
		glm::mat4 cam = camera(5.0f, { 0.5f, 0.5f });
	}

	void Update(Cannis::ComponentManager& p_componentManager) override {
		if (Cannis::Input::IsKeyPressed(CC_KEY_G))
			CC_CLIENT_INFO("G key is pressed");
	}

	void OnUIRender() override {

	}
};

class Sandbox : public Cannis::Application {
public:
	Sandbox() {
		GetCoordinator()->AddSubsystem<SandboxSystem>();

		CC_CLIENT_ERROR("Testing");

		AddSubsystem<SandboxSystem>();

		Cannis::EntityHandle square(GetCoordinator(), "Square");
		square.SetPosition(glm::vec3(0));
		square.SetRotation(glm::vec3(90, 45, 360));
		square.SetScale(glm::vec3(2));
		square.AddComponent<Cannis::GUIComponent>();

		float squareVertices[12] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};

		Cannis::BufferLayout bufferLayoutSquare = {
			{ "a_Position", Cannis::ShaderDataType::Float3 },
		};

		square.AddComponent<Cannis::ModelComponent>(squareVertices, sizeof(squareVertices), squareIndices, sizeof(squareIndices) / sizeof(uint32_t), bufferLayoutSquare);

		std::string vertexSourceSquare = "../Engine/assets/Shaders/Simple/simpleShader.vert";
		std::string fragmentSourceSquare = "../Engine/assets/Shaders/Simple/simpleShader.frag";
		square.AddComponent<Cannis::ShaderComponent>(vertexSourceSquare, fragmentSourceSquare);

		//
		Cannis::EntityHandle triangle(GetCoordinator(), "Triangle");
		triangle.SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));
		triangle.SetRotation(glm::vec3(15.0f, 3.0f, 17.0f));
		triangle.SetScale(glm::vec3(1));

		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.3f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};


		uint32_t indices[3] = { 0, 1, 2 };


		Cannis::BufferLayout bufferLayout = {
			{ "a_Position", Cannis::ShaderDataType::Float3 },
			{ "a_Color", Cannis::ShaderDataType::Float4 }
		};

		triangle.AddComponent<Cannis::ModelComponent>(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(uint32_t), bufferLayout);

		std::string vertexSource = "../Engine/assets/Shaders/ColorPos/colorPos.vert";
		std::string fragmentSource = "../Engine/assets/Shaders/ColorPos/colorPos.frag";
		triangle.AddComponent<Cannis::ShaderComponent>(vertexSource, fragmentSource);
	}

	~Sandbox() {

	}
};

Cannis::Application* Cannis::CreateApplication() {
	return new Sandbox();
}