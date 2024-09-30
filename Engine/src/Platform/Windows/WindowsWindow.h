#pragma once

#include "Window/Window.h"
#include <GLFW/glfw3.h>

namespace Cannis {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& p_props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		inline unsigned int GetWidth() const override { return m_data.width; }
		inline unsigned int GetHeight() const override { return m_data.height; }

		//Window Attributes
		inline void SetSysEventCallback(const SysEventCallback& p_callback) override { m_data.sysEventCallback = p_callback; }
		void SetVSync(bool p_enabled) override;
		bool IsVSync() const override;
		
	private:
		virtual void Init(const WindowProps& p_props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_window;

		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vsync;
			SysEventCallback sysEventCallback;
			std::vector<SysEvent> eventStack;

			WindowData() : width(0), height(0), vsync(false) {}
		};

		WindowData m_data;
	};
}