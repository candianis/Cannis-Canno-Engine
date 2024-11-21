#include "ccpch.h"
#include "Core/Application.h"
#include "ECS/Component/TransformComponent.hpp"
#include "ECS/Component/GUIComponent.hpp"
#include "ECS/Systems/RenderSystem/RenderSystem.h"

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
		io.DisplaySize = ImVec2((float) app.GetWindow().GetWidth(), (float) app.GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backupContextCurrent = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupContextCurrent);
		}
	}

	void UIService::Update(std::shared_ptr<WorldCoordinator> p_world, const Timestep p_timestep) {
		static bool show_demo_window = false;
		ImGui::ShowDemoWindow(&show_demo_window);

		CreateEditor(p_world, p_timestep);
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

	void UIService::CreateEditor(std::shared_ptr<WorldCoordinator>& p_world, const Timestep p_timestep) {
		bool showEntitiesWindow = true;
		ImGui::Begin("Scene", &showEntitiesWindow);

		size_t i = 0;

		//static bool selection[2] = { false, true };
		for (const Entity& entity : p_world->GetEntities()) {
			GUIComponent& gui = p_world->GetComponent<GUIComponent>(entity);
			if (ImGui::Selectable(entity.name.c_str(), &gui.isSelected)) {
				if (m_selectedEntity) {
					p_world->GetComponent<GUIComponent>(*m_selectedEntity).isSelected = false;
				}

				m_selectedEntity.reset();
				m_selectedEntity = std::make_shared<Entity>(entity);
			}

			ImGui::Spacing();
			i++;
		}
		ImGui::End();

		ImGui::Begin("Files", &showEntitiesWindow);

		ImGui::End();

		CreateInspector(p_world);

		CreateCameraEditor(p_world);

		CreateEngineInfo(p_timestep);
	}

	void UIService::CreateSceneEditor() {

	}

	void UIService::CreateEngineInfo(const Timestep p_timestep) {
		ImGui::Begin("Engine Info");
		ImGui::Text("Delta Time: %fs", p_timestep.GetSeconds());
		ImGui::Text("Delta Time (miliseconds): %fms", p_timestep.GetMilliseconds());

		ImGui::End();
	}

	void UIService::CreateCameraEditor(std::shared_ptr<WorldCoordinator>& p_world) {
		auto renderSys = p_world->GetSubsystem<RenderSystem>();

		Camera& cam = renderSys->camera;

		ImGui::Begin("Camera");

		ImGui::SeparatorText("Transform");
		ImGui::PushItemWidth(80);
		ImGui::SeparatorText("Position");
		ImGui::InputFloat("X", &cam.position.x); ImGui::SameLine();
		ImGui::InputFloat("Y", &cam.position.y); ImGui::SameLine();
		ImGui::InputFloat("Z", &cam.position.z);
		ImGui::PopItemWidth();
		ImGui::Spacing();

		ImGui::SeparatorText("Rotation");
		ImGui::PushItemWidth(80);
		ImGui::DragFloat("Yaw", &cam.yaw, 1.0f, -360.0f, 360.0f); ImGui::SameLine();
		ImGui::DragFloat("Pitch", &cam.pitch, 1.0f, -360.0f, 360.0f);
		ImGui::PopItemWidth();
			
		ImGui::SeparatorText("Perspective Settings");
		ImGui::DragFloat("FOV", &cam.fov, 1.0f, 45.0f, 65.0f);
		ImGui::Spacing();

		ImGui::End();
	}

	void UIService::CreateInspector(std::shared_ptr<WorldCoordinator>& p_world) {
		bool showInspector = true;
		ImGui::Begin("Inspector", &showInspector);
		CreateTransformComponent(p_world);
		ImGui::End();
	}

	void UIService::CreateTransformComponent(std::shared_ptr<WorldCoordinator>& p_world) {
		if (m_selectedEntity == nullptr) {
			return;
		}

		if (ImGui::CollapsingHeader(m_selectedEntity->name.c_str())) {
			//Go through each component 
			if (ImGui::TreeNode("Transform")) {
				TransformComponent& transform = p_world->GetComponent<TransformComponent>(*m_selectedEntity);

				// ----- Position -----//
				ImGui::PushID(0);
				ImGui::PushItemWidth(80);
				ImGui::SeparatorText("Position");
				ImGui::InputFloat("X", &transform.position.x); ImGui::SameLine();
				ImGui::InputFloat("Y", &transform.position.y); ImGui::SameLine();
				ImGui::InputFloat("Z", &transform.position.z);
				ImGui::PopItemWidth();
				ImGui::PopID();
				ImGui::Spacing();

				// ----- Rotation ------//
				ImGui::PushID(1);
				ImGui::PushItemWidth(80);
				ImGui::SeparatorText("Rotation");
				ImGui::DragFloat("X", &transform.rotation.x, 1.0f, -360.0f, 360.0f); ImGui::SameLine();
				ImGui::DragFloat("Y", &transform.rotation.y, 1.0f, -360.0f, 360.0f); ImGui::SameLine();
				ImGui::DragFloat("Z", &transform.rotation.z, 1.0f, -360.0f, 360.0f);
				ImGui::PopItemWidth();
				ImGui::PopID();
				ImGui::Spacing();

				// ----- Scale -----//
				ImGui::PushID(2);
				ImGui::PushItemWidth(80);
				ImGui::SeparatorText("Scale");
				ImGui::InputFloat("X", &transform.scale.x); ImGui::SameLine();
				ImGui::InputFloat("Y", &transform.scale.y); ImGui::SameLine();
				ImGui::InputFloat("Z", &transform.scale.z);
				ImGui::PopItemWidth();
				ImGui::PopID();
				ImGui::Spacing();

				ImGui::TreePop();
			}
		}
	}

	void UIService::OnWindowClose(const SysEvent& p_event) {
		const WindowCloseEvent& curEvent = static_cast<const WindowCloseEvent&>(p_event);
		
	}

	void UIService::OnWindowResize(const SysEvent& p_event) {
		const WindowResizeEvent& curEvent = static_cast<const WindowResizeEvent&>(p_event);

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float) curEvent.GetWidth(), (float) curEvent.GetHeight());
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