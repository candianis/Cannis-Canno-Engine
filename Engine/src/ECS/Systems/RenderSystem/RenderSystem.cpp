#include "ccpch.h"
#include "RenderSystem.h"
#include "Core/Application.h"

#include "Renderer/Renderer.h"
#include "ECS/Component/TransformComponent.hpp"
#include "ECS/Component/ModelComponent.hpp"
#include "ECS/Component/ShaderComponent.hpp"
#include "ECS/Component/LightComponent.hpp"
#include "ECS/Component/MaterialComponent.hpp"
#include "ECS/Component/PBRMaterialComponent.hpp"
#include "ECS/Component/PBRLightComponent.hpp"

#include "Renderer/Shader/Shader.h"
#include "Renderer/Model/Model.h"

namespace Cannis {
	RenderSystem::RenderSystem(ComponentManager& p_componentManager) : Subsystem("RenderSystem"), camera(glm::vec3(0.0f, 0.0f, 8.0f)), m_shaderLibrary() {
		// This signature is for entities to implement a Blinn Phong shader
		Signature newSignature = GetSignature();
		newSignature.set(p_componentManager.GetComponentID<TransformComponent>());
		newSignature.set(p_componentManager.GetComponentID<ModelComponent>());
		newSignature.set(p_componentManager.GetComponentID<MaterialComponent>());
		SetSignature(newSignature);
		
		//
		m_desiredLightSignature.set(p_componentManager.GetComponentID<TransformComponent>());
		m_desiredLightSignature.set(p_componentManager.GetComponentID<LightComponent>());

		m_desiredPBRLightSignature.set(p_componentManager.GetComponentID<TransformComponent>());
		m_desiredPBRLightSignature.set(p_componentManager.GetComponentID<PBRLightComponent>());

		m_desiredPBRSignature.set(p_componentManager.GetComponentID<TransformComponent>());
		m_desiredPBRSignature.set(p_componentManager.GetComponentID<ModelComponent>());
		m_desiredPBRSignature.set(p_componentManager.GetComponentID<PBRMaterialComponent>());

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
		m_shaderLibrary.GetRegisteredShader(ShaderImplementation::PBR)->UploadUniform("camPos", camera.position);

		RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		RenderCommand::Clear();

		Renderer::BeginScene(camera);
		// Blinn-Phong
		m_shaderLibrary.BindShader(ShaderImplementation::Blinn_Phong);
		UpdateLights(p_componentManager);
		UpdateEntities(p_componentManager);
		m_shaderLibrary.UnbindShader(ShaderImplementation::Blinn_Phong);

		m_shaderLibrary.BindShader(ShaderImplementation::PBR);
		UpdatePBRLightEntities(p_componentManager);
		UpdatePBREntities(p_componentManager);
		m_shaderLibrary.UnbindShader(ShaderImplementation::PBR);

		Renderer::EndScene();
	}

	void RenderSystem::UpdateLights(ComponentManager& p_componentManager) {
		for (const Entity& entity : m_lightEntities) {
			TransformComponent& transform = p_componentManager.GetComponent<TransformComponent>(entity);
			LightComponent& light = p_componentManager.GetComponent<LightComponent>(entity);

			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::Blinn_Phong)->UploadUniform("light.position", transform.position);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::Blinn_Phong)->UploadUniform("light.ambient", light.ambient);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::Blinn_Phong)->UploadUniform("light.diffuse", light.diffuse);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::Blinn_Phong)->UploadUniform("light.specular", light.specular);
		}
	}

	void RenderSystem::UpdateEntities(ComponentManager& p_componentManager) {
		for (const Entity& entity : m_entities) {
			TransformComponent& transform = p_componentManager.GetComponent<TransformComponent>(entity);
			ModelComponent& modelComponent = p_componentManager.GetComponent<ModelComponent>(entity);
			MaterialComponent& material = p_componentManager.GetComponent<MaterialComponent>(entity);

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

			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::Blinn_Phong)->UploadUniform("u_model", modelComponent.modelMatrix);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::Blinn_Phong)->UploadUniform("material.specular", material.specular);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::Blinn_Phong)->UploadUniform("material.shininess", material.shininess);

			Renderer::Submit(m_shaderLibrary.GetRegisteredShader(ShaderImplementation::Blinn_Phong), modelComponent.model);
		}
	}

	void RenderSystem::UpdatePBRLightEntities(ComponentManager& p_componentManager) {
		size_t i = 0;
		for (const Entity& entity : m_pbrLightEntities) {
			TransformComponent& transform = p_componentManager.GetComponent<TransformComponent>(entity);
			PBRLightComponent& pbrLight = p_componentManager.GetComponent<PBRLightComponent>(entity);
			std::string baseName = "lights[" + std::to_string(i) + "].";
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::PBR)->UploadUniform(baseName + "position", transform.position);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::PBR)->UploadUniform(baseName + "color", pbrLight.color);
			i++;
		}
	}

	void RenderSystem::UpdatePBREntities(ComponentManager& p_componentManager) {
		for (const Entity& entity : m_PBREntities) {
			TransformComponent& transform = p_componentManager.GetComponent<TransformComponent>(entity);
			ModelComponent& model = p_componentManager.GetComponent<ModelComponent>(entity);
			PBRMaterialComponent pbrMaterial = p_componentManager.GetComponent<PBRMaterialComponent>(entity);

			model.modelMatrix = glm::mat4(1.0f);

			// Translation
			model.modelMatrix = glm::translate(model.modelMatrix, transform.position);

			// Y rotation
			model.modelMatrix = glm::rotate(model.modelMatrix, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			// X rotation
			model.modelMatrix = glm::rotate(model.modelMatrix, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			// Z rotation
			model.modelMatrix = glm::rotate(model.modelMatrix, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

			// Scale
			model.modelMatrix = glm::scale(model.modelMatrix, transform.scale);

			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::PBR)->UploadUniform("u_model", model.modelMatrix);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::PBR)->UploadUniform("u_albedo", pbrMaterial.albedo);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::PBR)->UploadUniform("u_metallic", pbrMaterial.metallic);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::PBR)->UploadUniform("u_roughness", pbrMaterial.roughness);
			m_shaderLibrary.GetRegisteredShader(ShaderImplementation::PBR)->UploadUniform("u_ambientOcclusion", pbrMaterial.ao);

			Renderer::Submit(m_shaderLibrary.GetRegisteredShader(ShaderImplementation::PBR), model.model);
		}
	}

	void RenderSystem::Shutdown() {

	}

	void RenderSystem::OnEvent(SysEvent& p_event) {

	}

	void RenderSystem::SubscribeToEvent(const std::shared_ptr<SysEventDispatcher>& p_sysEventDispatcher) {
		p_sysEventDispatcher->Subscribe(EventType::EntityDestroyed, std::bind(&RenderSystem::OnEntityDestroyed, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::SignatureChanged, std::bind(&RenderSystem::OnSignatureChanged, this, std::placeholders::_1));
	}

	void RenderSystem::OnSignatureChanged(const SysEvent& p_sysEvent) {
		const SignatureChangedEvent& curEvent = static_cast<const SignatureChangedEvent&>(p_sysEvent);

		// Check if this entity is carrying a transform and light component
		if ((curEvent.GetSignature() & m_desiredLightSignature) == m_desiredLightSignature) {
			m_lightEntities.insert(curEvent.GetEntity());
			return;
		}

		// Add entity if it has a simple material component and not anything of PBR
		if ((curEvent.GetSignature() & m_desiredComponentSignature) == m_desiredComponentSignature) {
			m_entities.insert(curEvent.GetEntity());
			return;
		}

		// Add entity if it has a simple material component and not anything of PBR
		if ((curEvent.GetSignature() & m_desiredPBRLightSignature) == m_desiredPBRLightSignature) {
			m_entities.insert(curEvent.GetEntity());
			return;
		}

		// Add entity if it has the desired components to implement PBR
		if ((curEvent.GetSignature() & m_desiredPBRSignature) == m_desiredPBRSignature) {
			m_entities.insert(curEvent.GetEntity());
		}
	}
}