#include "ccpch.h"
#include "UISubsystem.h"
#include "Core/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cannis {
	UISubsystem::UISubsystem() : Subsystem("GUI"), m_time(0.0f) {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 450");


	}

	UISubsystem::~UISubsystem() {

	}

	void UISubsystem::Update() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show_demo_window = true;
		ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
	}

	void UISubsystem::Shutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void UISubsystem::OnEvent(SysEvent& p_event) {

	}
		
	void UISubsystem::SubscribeToEvent(const std::unique_ptr<SysEventDispatcher>& p_sysEventDispatcher) {
		p_sysEventDispatcher->Subscribe(EventType::WindowClose, std::bind(&UISubsystem::OnWindowClose, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::WindowResize, std::bind(&UISubsystem::OnWindowResize, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::KeyPressed, std::bind(&UISubsystem::OnKeyPressedEvent, this, std::placeholders::_1));
	}

	void UISubsystem::OnWindowClose(const SysEvent& p_event) {
		CC_CORE_INFO("UI subsystem was informed the window is closing");

		const WindowCloseEvent& curEvent = static_cast<const WindowCloseEvent&>(p_event);
		
	}

	void UISubsystem::OnWindowResize(const SysEvent& p_event) {
		const WindowResizeEvent& curEvent = static_cast<const WindowResizeEvent&>(p_event);
		

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(curEvent.GetWidth(), curEvent.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, curEvent.GetWidth(), curEvent.GetHeight());

		CC_CORE_INFO(p_event.ToString());
	}

	void UISubsystem::OnMouseButtonPressedEvent(const SysEvent& p_event) {
		const MouseButtonPressedEvent& curEvent = static_cast<const MouseButtonPressedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[curEvent.GetMouseButton()] = true;
		CC_CORE_INFO("Mouse Button Pressed");
	}

	void UISubsystem::OnMouseButtonReleasedEvent(const SysEvent& p_event) {
		const MouseButtonReleasedEvent& curEvent = static_cast<const MouseButtonReleasedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[curEvent.GetMouseButton()] = false;
		CC_CORE_INFO("Mouse Button Released");
	}

	void UISubsystem::OnMouseScrolledEvent(const SysEvent& p_event) {
		const MouseScrolledEvent& curEvent = static_cast<const MouseScrolledEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += curEvent.GetXOffset();
		io.MouseWheel += curEvent.GetYOffset();
	}

	void UISubsystem::OnMouseMovedEvent(const SysEvent& p_event) {
		const MouseMovedEvent& curEvent = static_cast<const MouseMovedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(curEvent.GetX(), curEvent.GetY());
		CC_CORE_INFO(p_event.ToString());

	}

	void UISubsystem::OnKeyPressedEvent(const SysEvent& p_event) {
		const KeyPressedEvent& curEvent = static_cast<const KeyPressedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[curEvent.GetKey()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		CC_CORE_INFO("Key was pressed");
	}

	void UISubsystem::OnKeyReleasedEvent(const SysEvent& p_event) {
		const KeyReleasedEvent& curEvent = static_cast<const KeyReleasedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[curEvent.GetKey()] = false;
	}

	void UISubsystem::OnKeyTypedEvent(const SysEvent& p_event) {
		const KeyTypedEvent& curEvent = static_cast<const KeyTypedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		int keycode = curEvent.GetKey();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);
	}

	void UISubsystem::CreateEditor() {

	}
}