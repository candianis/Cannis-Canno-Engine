#include "ccpch.h"
#include "RenderSystem.h"

#include "Renderer/Renderer.h"
#include "ECS/Component/TransformComponent.hpp"
#include "ECS/Component/ModelComponent.hpp"
#include "ECS/Component/ShaderComponent.hpp"

namespace Cannis {
	RenderSystem::RenderSystem(ComponentManager& p_componentManager) : Subsystem("RenderSystem") {
		Signature newSignature = GetSignature();
		newSignature.set(p_componentManager.GetComponentID<TransformComponent>());
		newSignature.set(p_componentManager.GetComponentID<ModelComponent>());
		newSignature.set(p_componentManager.GetComponentID<ShaderComponent>());

		SetSignature(newSignature);
	}

	RenderSystem::~RenderSystem() {

	}

	void RenderSystem::Update(ComponentManager& p_componentManager) {
		RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

		Renderer::BeginScene();

		for (const Entity& entity : m_entities) {
			TransformComponent& transform = p_componentManager.GetComponent<TransformComponent>(entity);
			ShaderComponent& shaderComponent = p_componentManager.GetComponent<ShaderComponent>(entity);
			ModelComponent& modelComponent = p_componentManager.GetComponent<ModelComponent>(entity);

			shaderComponent.shader->Bind();
			Renderer::Submit(modelComponent.vertexArray);
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