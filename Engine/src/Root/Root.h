#pragma once 

#include "ccpch.h"
#include "Core/Core.h"
#include "Events/Event.h"
#include "Subsystem/Subsystem.h"
#include "Events/SysEventDispatcher/SysEventDispatcher.h"

namespace Cannis {
	class CANNIS_API Root {
	private:
		std::vector<std::shared_ptr<Subsystem>> m_subsystems;

	
	public:
		Root() = default;

		void Init();
		void SubscribeSystemsToEvents(const std::unique_ptr<SysEventDispatcher>& p_sysEventDispatcher);
		void Update();
		void Shutdown();
	};
}