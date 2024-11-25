#pragma once

#include "ccpch.h"
#include "Subsystem/Subsystem.h"
#include "Renderer/Camera/Camera.h"
#include "Renderer/Shader/ShaderLibrary/ShaderLibrary.h"

namespace Cannis {
	class RenderSystem : public Subsystem {
	public:
		RenderSystem(ComponentManager& p_componentManager);
		~RenderSystem();
		
		void Init() override;

		void Update(ComponentManager& p_componentManager, const Timestep p_timestep) override;
		void UpdateLights(ComponentManager& p_componentManager);
		void UpdateEntities(ComponentManager& p_componentManager);
		void UpdatePBREntities(ComponentManager& p_componentManager);
		
		void Shutdown() override;
		void OnEvent(SysEvent& p_event);

		void SubscribeToEvent(const std::shared_ptr<SysEventDispatcher>& p_sysEventDispatcher) override;
		void OnSignatureChanged(const SysEvent& p_sysEvent) override;

		Camera camera;
	
	private:
		ShaderLibrary m_shaderLibrary;

		// @brief Desired bitset for an entity to have for light simulation with Blinn Phong
		Signature m_desiredLightSignature;
		std::set<Entity> m_lightEntities;

		// @brief Desired bitset for an entity to have for a model to implement PBR 
		Signature m_desiredPBRSignature;
		std::set<Entity> m_PBREntities;
	};
}