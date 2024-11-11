#include "ccpch.h"
#include "Core/Application.h"
#include "ECS/Component/TransformComponent.hpp"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cannis {
	UIService::UIService() : m_time(0.0f) {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		//io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		//io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		//io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		//io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		//io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		//io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		//io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		//io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		//io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		//io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		//io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		//io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		//io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		//io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		//io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		//io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		//io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		//io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		//io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		//io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	UIService::~UIService() {

	}

	void UIService::Begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UIService::End() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backupContextCurrent = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupContextCurrent);
		}
	}

	void UIService::Update(std::shared_ptr<WorldCoordinator> p_world) {
		static bool show_demo_window = false;
		ImGui::ShowDemoWindow(&show_demo_window);

		CreateEditor(p_world);
	}

	void UIService::Shutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}
		
	void UIService::SubscribeToEvent(const std::shared_ptr<SysEventDispatcher>& p_sysEventDispatcher) {
		p_sysEventDispatcher->Subscribe(EventType::WindowClose, std::bind(&UIService::OnWindowClose, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::WindowResize, std::bind(&UIService::OnWindowResize, this, std::placeholders::_1));

		p_sysEventDispatcher->Subscribe(EventType::KeyPressed, std::bind(&UIService::OnKeyPressedEvent, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::KeyReleased, std::bind(&UIService::OnKeyReleasedEvent, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::KeyTyped, std::bind(&UIService::OnKeyTypedEvent, this, std::placeholders::_1));

		p_sysEventDispatcher->Subscribe(EventType::MouseMoved, std::bind(&UIService::OnMouseMovedEvent, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::MouseButtonPressed, std::bind(&UIService::OnMouseButtonPressedEvent, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::MouseButtonReleased, std::bind(&UIService::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::MouseScrolled, std::bind(&UIService::OnMouseScrolledEvent, this, std::placeholders::_1));
	}

	void UIService::CreateEditor(std::shared_ptr<WorldCoordinator>& p_world) {
		bool showEntitiesWindow = true;
		ImGui::Begin("Scene", &showEntitiesWindow);

		size_t i = 0;
		for (const Entity entity : p_world->GetEntities()) {
			ImGui::PushID(i);
			//auto& signature = p_world->getsi
			if (ImGui::CollapsingHeader(entity.name.c_str())) {
				//Go through each component 

				TransformComponent& transform = p_world->GetComponent<TransformComponent>(entity);

				ImGui::SeparatorText("Transform");
				ImGui::InputFloat3("Position", glm::value_ptr(transform.position));
				ImGui::InputFloat3("Rotation", glm::value_ptr(transform.rotation));
				ImGui::InputFloat3("Scale", glm::value_ptr(transform.scale));
				ImGui::Spacing();
			}
			ImGui::PopID();
			i++;
		}
		ImGui::End();

		ImGui::Begin("Files", &showEntitiesWindow);

		ImGui::End();

		ImGui::Begin("Inspector", &showEntitiesWindow);

		ImGui::End();
	}

	void UIService::OnWindowClose(const SysEvent& p_event) {
		CC_CORE_INFO("UI subsystem was informed the window is closing");

		const WindowCloseEvent& curEvent = static_cast<const WindowCloseEvent&>(p_event);
		
	}

	void UIService::OnWindowResize(const SysEvent& p_event) {
		const WindowResizeEvent& curEvent = static_cast<const WindowResizeEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(curEvent.GetWidth(), curEvent.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, curEvent.GetWidth(), curEvent.GetHeight());
	}

	void UIService::OnMouseButtonPressedEvent(const SysEvent& p_event) {
		const MouseButtonPressedEvent& curEvent = static_cast<const MouseButtonPressedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[curEvent.GetMouseButton()] = true;
	}

	void UIService::OnMouseButtonReleasedEvent(const SysEvent& p_event) {
		const MouseButtonReleasedEvent& curEvent = static_cast<const MouseButtonReleasedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[curEvent.GetMouseButton()] = false;
	}

	void UIService::OnMouseScrolledEvent(const SysEvent& p_event) {
		const MouseScrolledEvent& curEvent = static_cast<const MouseScrolledEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += curEvent.GetXOffset();
		io.MouseWheel += curEvent.GetYOffset();
	}

	void UIService::OnMouseMovedEvent(const SysEvent& p_event) {
		const MouseMovedEvent& curEvent = static_cast<const MouseMovedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(curEvent.GetX(), curEvent.GetY());

	}

	void UIService::OnKeyPressedEvent(const SysEvent& p_event) {
		const KeyPressedEvent& curEvent = static_cast<const KeyPressedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[curEvent.GetKey()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
	}

	void UIService::OnKeyReleasedEvent(const SysEvent& p_event) {
		const KeyReleasedEvent& curEvent = static_cast<const KeyReleasedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[curEvent.GetKey()] = false;
	}

	void UIService::OnKeyTypedEvent(const SysEvent& p_event) {
		const KeyTypedEvent& curEvent = static_cast<const KeyTypedEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		int keycode = curEvent.GetKey();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);
	}
}