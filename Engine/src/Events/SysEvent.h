#pragma once

#include "ccpch.h"
#include "Core/Core.h"

namespace Cannis {
	namespace Events {
		enum class IEventType {
			None = 0,
			WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
			AppTick, AppUpdate, AppRender,
			KeyPressed, KeyReleased,
			MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
		};

		enum IEventCategory {
			None = 0,
			IEventCategoryApplication = BIT(0),
			IEventCategoryInput = BIT(1),
			IEventCategoryKeyboard = BIT(2),
			IEventCategoryMouse = BIT(3)
		};
	}

	class CANNIS_API SysEvent {
	public:
		~SysEvent() = default;
		virtual Events::IEventType GetType() const = 0;
		virtual Events::IEventCategory GetCategory() const = 0;
		virtual std::string ToString() const = 0;

		SysEvent() = default;
	protected:
	};

}