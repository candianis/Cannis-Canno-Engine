#pragma once 

#include "ccpch.h"
#include "Core/Core.h"
#include "Events/Event.h"
#include "Subsystem/Subsystem.h"

namespace Cannis {
	class CANNIS_API Root {
	private:
		std::vector<std::shared_ptr<Subsystem>> m_subsystems;

	public:
		Root() = default;

		void Init(GLFWwindow* p_window);
		void Update();
		void Shutdown();
	};
}