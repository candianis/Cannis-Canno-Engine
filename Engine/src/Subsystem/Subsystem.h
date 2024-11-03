#pragma once

#include "ccpch.h"

#include "Core/Core.h"
#include "ECS/Entity/Entity.h"
#include "ECS/ECSOptions.h"
#include "Events/SysEvent.h"
#include "Events/SysEventDispatcher/SysEventDispatcher.h"

namespace Cannis {
	// @brief Engine susbsytems
	class CANNIS_API Subsystem {
	public:
		Subsystem(const std::string& p_name = "Subsystem");
		virtual ~Subsystem();

		virtual void Update() {}
		virtual void Shutdown() {}
		virtual void OnUIRender() {}
		virtual void OnEvent(SysEvent& p_event) {}

		inline const std::string& GetName() const { return m_debugName; }
		inline const Signature& GetSignature() const { return m_desiredComponentSignature; }
		inline void SetSignature(const Signature& p_signature) { m_desiredComponentSignature = p_signature; }

		virtual void SubscribeToEvent(const std::shared_ptr<SysEventDispatcher>& p_sysEventDispatcher) {}
		void OnEntityDestroyed(const SysEvent& p_sysEvent);
		void OnSignatureChanged(const SysEvent& p_sysEvent);

	protected:
		std::string m_debugName;
		std::set<Entity> m_entities;
		Signature m_desiredComponentSignature;
	};
}