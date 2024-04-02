#pragma once

#include "../GraphicsManager/Framebuffer/Framebuffer.h"
#include "../../Shaders/Shader.h"

// Note: glad must always be included before GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <memory>

namespace Cannis {
	class GuiManager {
	public:
		// @brief 
		GuiManager(GLFWwindow* p_window, int p_screenWidth, int p_screenHeight);

		// @brief 
		void update();

		// @brief
		void clean() const;

		// @brief
		void bindFramebuffer(bool p_shouldBind) const;

		// @brief 
		void rescaleFramebuffer(int p_newWidth, int p_newHeight);

	private:
		ImGuiIO m_io;

		ImVec4 m_clearColor;

		std::unique_ptr<Framebuffer> m_fbo;

		// @brief 
		void createEditor();

	};
}