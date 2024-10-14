#pragma once

#include "ccpch.h"
#include "Input/Input.h"

namespace Cannis {
	class WindowsInput : public Input {
	protected:
		bool IsKeyPressedImpl(int p_keyCode) override;
		bool IsMouseButtonPressedImpl(int p_mouseButton) override;
		std::pair<float, float> GetMousePosImpl() override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};
}