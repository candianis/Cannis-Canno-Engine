#pragma once

#include "Core/Core.h"
#include "Events/SysEvent.h"

namespace Cannis {
	class CANNIS_API WindowResizeEvent : public SysEvent {
	public:
		WindowResizeEvent(unsigned int p_width, unsigned int p_height) : m_width(p_width), m_height(p_height) {}
		~WindowResizeEvent() = default;

		inline unsigned int GetWidth() const { return m_width; }
		inline unsigned int GetHeight() const { return m_height; }
		inline EventType GetType() const override { return EventType::WindowResize; }
		inline EventCategory GetCategory() const override { return EventCategory::ECApplication; }
		std::string ToString() const override;

	private:
		unsigned int m_width, m_height;
	};

	class CANNIS_API WindowCloseEvent : public SysEvent {
	public:
		WindowCloseEvent() = default;
		~WindowCloseEvent() = default;

		EventType GetType() const override { return EventType::WindowClose; }
		EventCategory GetCategory() const override { return EventCategory::ECApplication; }
		std::string ToString() const override;
	};

	class CANNIS_API AppTickEvent : SysEvent {
	public: 
		AppTickEvent();
		~AppTickEvent();

		inline EventType GetType() const override { return EventType::AppTick; }
		inline EventCategory GetCategory() const override { return EventCategory::ECApplication; }
		std::string ToString() const override;
	};

	class CANNIS_API AppUpdateEvent : SysEvent {
	public: 
		AppUpdateEvent();
		~AppUpdateEvent();

		inline EventType GetType() const override { return EventType::AppUpdate; }
		inline EventCategory GetCategory() const override { return EventCategory::ECApplication; }
		std::string ToString() const override;
	};

	class CANNIS_API AppRenderEvent : SysEvent {
	public:
		AppRenderEvent();
		~AppRenderEvent();

		inline EventType GetType() const override { return EventType::AppRender; }
		inline EventCategory GetCategory() const override { return EventCategory::ECApplication; }
		std::string ToString() const override;
	};
}