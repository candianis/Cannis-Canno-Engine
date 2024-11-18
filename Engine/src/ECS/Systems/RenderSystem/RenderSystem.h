#pragma once

#include "ccpch.h"
#include "Subsystem/Subsystem.h"

namespace Cannis {
	class RenderSystem : public Subsystem {
	public:
		RenderSystem(ComponentManager& p_componentManager);
		~RenderSystem();

		void Update(ComponentManager& p_componentManager) override;
		void Shutdown() override;
		void OnEvent(SysEvent& p_event);

		void SubscribeToEvent(const std::shared_ptr<SysEventDispatcher>& p_sysEventDispatcher) override;

	private:

	};
}