#include "ccpch.h"
#include "Root.h"

#include "UI/UISubsystem.h"

namespace Cannis {
	void Root::Init(GLFWwindow* p_window) {
		m_subsystems.push_back(std::make_shared<UISubsystem>(p_window));

	}

	void Root::Update() {
		for (std::shared_ptr<Subsystem>& subsystem : m_subsystems) {
			subsystem->Update();
		}
	}

	void Root::Shutdown() {
		for (std::shared_ptr<Subsystem>& subsystem : m_subsystems) {
			subsystem->Shutdown();
		}
	}
}