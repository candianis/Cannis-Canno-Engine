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

	void Update() override {
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
		
		//
		Cannis::EntityHandle triangle(GetCoordinator(), "Triangle");
		triangle.SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));
		triangle.SetRotation(glm::vec3(15.0f, 3.0f, 17.0f));
		triangle.SetScale(glm::vec3(1));

		triangle.AddComponent<Cannis::ModelComponent>();
		if (triangle.HasComponent<Cannis::ModelComponent>())
			CC_CLIENT_INFO(triangle.GetInstance().name + " has Mesh component");

		triangle.RemoveComponent<Cannis::ModelComponent>();
		if (triangle.HasComponent<Cannis::ModelComponent>())
			CC_CLIENT_INFO(triangle.GetInstance().name + " does not have Mesh component");

		triangle.RemoveComponent<Cannis::ModelComponent>();

		Cannis::EntityHandle square(GetCoordinator(), "Square");
		square.SetPosition(glm::vec3(0));
		square.SetRotation(glm::vec3(90, 45, 360));
		square.SetScale(glm::vec3(2));
		square.AddComponent<Cannis::GUIComponent>();

		if (!square.HasComponent<Cannis::TransformComponent>())
			CC_CLIENT_INFO("This component does not have a Transform component");
	}

	~Sandbox() {

	}
};

Cannis::Application* Cannis::CreateApplication() {
	return new Sandbox();
}