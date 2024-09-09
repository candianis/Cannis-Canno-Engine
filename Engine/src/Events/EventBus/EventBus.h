#pragma once 

#include "ccpch.h"
#include "Events/Event.h"
#include "Events/EventCallback/EventCallback.h"

namespace Cannis {
	typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

	class CANNIS_API EventBus {
	public:
		EventBus();
		~EventBus();

		inline void Reset() { m_subscribers.clear(); }

		template <typename TEvent, typename TOwner>
		void SubscribeToEvent(TOwner* p_ownerInstance, void (TOwner::* p_callbackFunction)(TEvent&)) {
			if (!m_subscribers[typeid(TEvent)].get()) {
				m_subscribers[typeid(TEvent)] = std::make_shared<HandlerList>();
			}

			auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(p_ownerInstance, p_callbackFunction);
			m_subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
		}

		template <typename TEvent, typename ...TArgs>
		void EmitEvent(TArgs&& ...args) {
			auto handlers = m_subscribers[typeid(TEvent)].get();

			if (!handlers) {
				CC_CORE_ERROR("Event type does not exist");
				return;
			}

			for (auto it = handlers->begin(); it != handlers->end(); it++) {
				auto handler = it->get();
				TEvent event(std::forward<TArgs>(args)...);
				handler->Execute(event);
			}
		}

	private:
		std::map<std::type_index, std::shared_ptr<HandlerList>> m_subscribers;
	};
}