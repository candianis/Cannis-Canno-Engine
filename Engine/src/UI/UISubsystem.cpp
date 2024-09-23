#include "ccpch.h"
#include "UISubsystem.h"
#include "Events/KeyboardEvent/KeyboardEvent.h"
#include "Core/Application.h"

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
		
	void UISubsystem::SubscribeToEvent(const std::unique_ptr<EventBus>& p_eventBus) {
		p_eventBus->SubscribeToEvent<MouseMovedEvent>(this, &UISubsystem::OnMouseMovedEvent);
		p_eventBus->SubscribeToEvent<MouseButtonPressedEvent>(this, &UISubsystem::OnMouseButtonPressedEvent);
		p_eventBus->SubscribeToEvent<MouseButtonReleasedEvent>(this, &UISubsystem::OnMouseButtonReleasedEvent);
		p_eventBus->SubscribeToEvent<MouseScrolledEvent>(this, &UISubsystem::OnMouseScrolled);
	}

	void UISubsystem::OnMouseButtonPressedEvent(MouseButtonPressedEvent& p_event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[p_event.GetMouseButton()] = true;
		CC_CORE_INFO("Mouse Button Pressed");
	}

	void UISubsystem::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& p_event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[p_event.GetMouseButton()] = false;
		CC_CORE_INFO("Mouse Button Released");
	}

	void UISubsystem::OnMouseScrolled(MouseScrolledEvent& p_event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += p_event.GetXOffset();
		io.MouseWheel += p_event.GetYOffset();
	}

	void UISubsystem::OnMouseMovedEvent(MouseMovedEvent& p_event) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(p_event.GetX(), p_event.GetY());
		CC_CORE_INFO(p_event.ToString());
	}

	void UISubsystem::CreateEditor() {

	}
}