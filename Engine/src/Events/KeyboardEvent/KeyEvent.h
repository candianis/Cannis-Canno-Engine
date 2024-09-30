#pragma once

#include "Events/SysEvent.h"
#include "Events/Event.h"

namespace Cannis {
	class CANNIS_API KeyPressedEvent : public SysEvent {
	public:
		KeyPressedEvent(int p_key);
		~KeyPressedEvent() = default;

		inline int GetKey() const { return m_keyCode; }

		inline EventType GetType() const override { return EventType::KeyPressed; }
		inline EventCategory GetCategory() const override { return EventCategory::ECKeyboard; }
		std::string ToString() const override;

	private:
		int m_keyCode;
	};

	class CANNIS_API KeyReleasedEvent : public SysEvent {
	public:
		KeyReleasedEvent(int p_key);
		~KeyReleasedEvent() = default;

		inline int GetKey() const { return m_keyCode; }

		inline EventType GetType() const override { return EventType::KeyReleased; }
		inline EventCategory GetCategory() const override { return EventCategory::ECKeyboard; }
		std::string ToString() const override;

	private:
		int m_keyCode;
	};

	class CANNIS_API KeyTypedEvent : public SysEvent {
	public:
		KeyTypedEvent(int p_key) : m_keyCode(p_key) {}
		~KeyTypedEvent() = default;

		inline int GetKey() const { return m_keyCode; }

		inline EventType GetType() const override { return EventType::KeyTyped; }
		inline EventCategory GetCategory() const override { return EventCategory::ECKeyboard; }
		std::string ToString() const override;

	private:
		int m_keyCode;
	};
}