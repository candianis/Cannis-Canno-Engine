#include "ccpch.h"
#include "RenderSystem.h"
#include "Core/Application.h"

#include "Renderer/Renderer.h"
#include "ECS/Component/TransformComponent.hpp"
#include "ECS/Component/ModelComponent.hpp"
#include "ECS/Component/ShaderComponent.hpp"
#include "ECS/Component/LightComponent.hpp"
#include "ECS/Component//MaterialComponent.hpp"

#include "Renderer/Shader/Shader.h"
#include "Renderer/Model/Model.h"

namespace Cannis {
	RenderSystem::RenderSystem(ComponentManager& p_componentManager) : Subsystem("RenderSystem"), camera(glm::vec3(0.0f, 0.0f, 8.0f)) {
		Signature newSignature = GetSignature();
		newSignature.set(p_componentManager.GetComponentID<TransformComponent>());
		newSignature.set(p_componentManager.GetComponentID<ModelComponent>());
		newSignature.set(p_componentManager.GetComponentID<ShaderComponent>());
		//newSignature.set(p_componentManager.GetComponentID<LightComponent>());
		//newSignature.set(p_componentManager.GetComponentID<MaterialComponent>());

		SetSignature(newSignature);

		Application& app = Application::Get();
		camera.SetPerspective(45.0f, (float)app.GetWindow().GetWidth() / (float)app.GetWindow().GetHeight(), 0.1f, 1000.0f);
	}

	RenderSystem::~RenderSystem() {

	}
	
	void RenderSystem::Init() {
		RenderCommand::Init();
	}

	void RenderSystem::Update(ComponentManager& p_componentManager, const Timestep p_timestep) {
		camera.Update();

		RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

		Renderer::BeginScene(camera);

		for (const Entity& entity : m_entities) {
			TransformComponent& transform = p_componentManager.GetComponent<TransformComponent>(entity);
			ShaderComponent& shaderComponent = p_componentManager.GetComponent<ShaderComponent>(entity);
			
			ModelComponent& modelComponent = p_componentManager.GetComponent<ModelComponent>(entity);

			modelComponent.modelMatrix = glm::mat4(1.0f);

			// Translation
			modelComponent.modelMatrix = glm::translate(modelComponent.modelMatrix, transform.position);

			// Y rotation
			modelComponent.modelMatrix = glm::rotate(modelComponent.modelMatrix, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			// X rotation
			modelComponent.modelMatrix = glm::rotate(modelComponent.modelMatrix, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			// Z rotation
			modelComponent.modelMatrix = glm::rotate(modelComponent.modelMatrix, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

			// Scale
			modelComponent.modelMatrix = glm::scale(modelComponent.modelMatrix, transform.scale);

			shaderComponent.shader->Bind();
			shaderComponent.shader->UploadUniform("u_model", modelComponent.modelMatrix);

			Renderer::Submit(shaderComponent.shader, modelComponent.model);
			shaderComponent.shader->UnBind();
		}

		Renderer::EndScene();
	}

	void RenderSystem::Shutdown() {

	}

	void RenderSystem::OnEvent(SysEvent& p_event) {

	}

	void RenderSystem::SubscribeToEvent(const std::shared_ptr<SysEventDispatcher>& p_sysEventDispatcher) {
		p_sysEventDispatcher->Subscribe(EventType::EntityDestroyed, std::bind(&RenderSystem::OnEntityDestroyed, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::SignatureChanged, std::bind(&RenderSystem::OnSignatureChanged, this, std::placeholders::_1));
	}
}