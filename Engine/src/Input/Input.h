#pragma once

#include "ccpch.h"
#include "Core/Core.h"

namespace Cannis {
	class CANNIS_API Input {
	public:
		inline static bool IsKeyPressed(int p_keyCode) { return s_instance->IsKeyPressedImpl(p_keyCode); }

		inline static bool IsMouseButtonPressed(int p_mouseButton) { return s_instance->IsMouseButtonPressedImpl(p_mouseButton); }
		inline static std::pair<float, float> GetMousePos() { return s_instance->GetMousePosImpl(); }
		inline static float GetMouseX() { return s_instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int p_keyCode) = 0;

		virtual bool IsMouseButtonPressedImpl(int p_mouseButton) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_instance;
	};
}