#include "ccpch.h"
#include "Core/Core.h"
#include "../Event.h"


namespace Cannis {
	class CANNIS_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int p_width, unsigned int p_height) : m_width(p_width), m_height(p_height) {}
		inline unsigned int GetWidth() const { return m_width; }
		inline unsigned int GetHeight() const { return m_height; }

		// @brief This should only be used for debugging
		std::string ToString() const override;

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_width, m_height;
	};

	class CANNIS_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CANNIS_API AppTickEvent : public Event {
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CANNIS_API AppUpdateEvent : public Event {
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CANNIS_API AppRenderEvent : public Event {
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}