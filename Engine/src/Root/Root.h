#pragma once 

#include "ccpch.h"
#include "Core/Core.h"
#include "Events/Event.h"
#include "Subsystem/Subsystem.h"
#include "Events/SysEventDispatcher/SysEventDispatcher.h"
#include "Events/ECSEvents/ECSEvent.h"
#include "ECS/ComponentManager/ComponentManager.h"

namespace Cannis {
	class CANNIS_API Root {
	private:
		std::unordered_map<std::type_index, std::shared_ptr<Subsystem>> m_subsystems;
		std::unordered_map<std::type_index, Signature> m_systemSignatures;

	public:
		Root() = default;

		void Init(ComponentManager& p_componentManager);
		void Update(ComponentManager& p_componentManager);
		void Shutdown();
		void OnUIRender();

		template<typename SystemType>
		void AddSubsystem();
		
		template<typename SystemType>
		std::shared_ptr<SystemType>& GetSubsystem();

		template<typename SystemType>
		void SetSubsystemSignature(const Signature& p_signature);

		void SubscribeSystemsToEvents(const std::shared_ptr<SysEventDispatcher>& p_sysEventDispatcher);
		void OnEntityDestroyed(const SysEvent& p_event);
		void OnSignatureChanged(const SysEvent& p_event);
	};

	template<typename SystemType>
	inline void Root::AddSubsystem() {
		m_subsystems.insert(std::make_pair(std::type_index(typeid(SystemType)), std::make_shared<SystemType>()));
	}

	template<typename SystemType>
	inline std::shared_ptr<SystemType>& Root::GetSubsystem() {
		const auto& sysIndex = std::type_index(typeid(SystemType));
		CC_ASSERT(m_subsystems.find(sysIndex) != m_subsystems.end());

		return m_subsystems[sysIndex];
	}

	template<typename SystemType>
	inline void Root::SetSubsystemSignature(const Signature& p_signature) {
		CC_ASSERT(m_subsystems.find(std::type_index(typeid(SystemType))) != m_subsystems.end(), "System's signature has already been registered");

		m_subsystems[std::type_index(typeid(SystemType))]->SetSignature(p_signature);
		m_systemSignatures.insert(std::pair(std::type_index(typeid(SystemType)), p_signature));
	}
}