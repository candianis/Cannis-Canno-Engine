#pragma once

#include "Events/SysEvent.h"
#include "Events/Event.h"

namespace Cannis {
	class CANNIS_API PressedKeyboardEvent : SysEvent {
	public:
		PressedKeyboardEvent(int p_key);
		~PressedKeyboardEvent() = default;

		inline int GetKey() const { return m_keyCode; }

		inline Events::IEventType GetType() const override { return Events::IEventType::KeyPressed; }
		inline Events::IEventCategory GetCategory() const override { return Events::IEventCategoryKeyboard; }

	private:
		int m_keyCode;
	};

	class CANNIS_API ReleasedKeyboardEvent : SysEvent {
	public:
		ReleasedKeyboardEvent(int p_key);
		~ReleasedKeyboardEvent() = default;

		inline int GetKey() const { return m_keyCode; }

	private:
		int m_keyCode;
	};
}