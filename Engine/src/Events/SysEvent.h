#pragma once

#include "ccpch.h"
#include "Core/Core.h"

namespace Cannis {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		Demo
	};

	enum EventCategory {
		None = 0,
		ECApplication = BIT(0),
		ECInput = BIT(1),
		ECKeyboard = BIT(2),
		ECMouse = BIT(3)
	};

	class CANNIS_API SysEvent {
	public:
		virtual ~SysEvent() = default;
		virtual EventType GetType() const = 0;
		virtual EventCategory GetCategory() const = 0;
		virtual std::string ToString() const = 0;
	};

	class CANNIS_API DemoEvent : SysEvent {
	public:
		DemoEvent() = default;

		static constexpr EventType type = EventType::Demo;

		EventType GetType() const override { return type; }
		EventCategory GetCategory() const override { return EventCategory::None; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "DemoEvent";
			return ss.str();
		}
	};

}