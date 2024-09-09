#pragma once

#include "ccpch.h"

#include "Core/Core.h"
#include "Events/Event.h"
#include "Events/EventBus/EventBus.h"

namespace Cannis {
	struct WindowProps {
		string title;
		unsigned int width;
		unsigned int height;
		WindowProps(string p_title = "Cannis Canno Engine", unsigned int p_width = 1280, unsigned int p_height = 720) : title(p_title), width(p_width), height(p_height) {}
	};

	// @brief Interface representing a desktop system based window
	class CANNIS_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& p_callback) = 0;
		virtual void SetVSync(bool p_enabled) = 0;
		virtual void IsVSync() const = 0;

		// @note This static function must be implemented per platform
		static Window* Create(const WindowProps& p_props = WindowProps());

	protected:
		std::unique_ptr<EventBus> m_eventBus;
	};
}