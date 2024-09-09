#pragma once

#include "Core/Core.h"
#include "Events/SysEvent.h"

namespace Cannis {
	class CANNIS_API AppResizeEvent : public SysEvent {
	public:
		AppResizeEvent(unsigned int p_width, unsigned int p_height);
		~AppResizeEvent();

		inline Events::IEventType GetType() const override { return Events::IEventType::WindowResize; }
		inline Events::IEventCategory GetCategory() const override { return Events::IEventCategoryApplication; }
		std::string ToString() const override;

	private:
		unsigned int m_width, m_height;
	};

	class CANNIS_API AppCloseEvent : public SysEvent {
	public:
		AppCloseEvent();
		~AppCloseEvent();

		Events::IEventType GetType() const override { return Events::IEventType::WindowClose; }
		Events::IEventCategory GetCategory() const override { return Events::IEventCategoryApplication; }
		std::string ToString() const override;
	};

	class CANNIS_API CCAppTickEvent : SysEvent {
	public: 
		CCAppTickEvent();
		~CCAppTickEvent();

		inline Events::IEventType GetType() const override { return Events::IEventType::AppTick; }
		inline Events::IEventCategory GetCategory() const override { return Events::IEventCategoryApplication; }
		std::string ToString() const override;
	};

	class CANNIS_API CCAppUpdateEvent : SysEvent {
	public: 
		CCAppUpdateEvent();
		~CCAppUpdateEvent();

		inline Events::IEventType GetType() const override { return Events::IEventType::AppUpdate; }
		inline Events::IEventCategory GetCategory() const override { return Events::IEventCategoryApplication; }
		std::string ToString() const override;
	};

	class CANNIS_API CCAppRenderEvent : SysEvent {
	public:
		CCAppRenderEvent();
		~CCAppRenderEvent();

		inline Events::IEventType GetType() const override { return Events::IEventType::AppRender; }
		inline Events::IEventCategory GetCategory() const override { return Events::IEventCategoryApplication; }
		std::string ToString() const override;
	};
}