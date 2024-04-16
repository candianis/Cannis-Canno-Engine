#include "GuiManager.h"

#include <iostream>

using Cannis::GuiManager;

GuiManager::GuiManager(GLFWwindow* p_window, int p_screenWidth, int p_screenHeight) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init();

	m_fbo = std::make_unique<Framebuffer>(p_screenWidth, p_screenHeight);
}

void GuiManager::update() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	createEditor();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	m_fbo->update();
}

void GuiManager::lateUpdate() {
	m_fbo->lateUpdate();
}

void GuiManager::clean() const {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	m_fbo->clean();
}

void GuiManager::bindFramebuffer(bool p_shouldBind) const {
	//If it is true then this uint will have the same value as m_fbo 
	//Else then we assign 0 to unbind the current fbo 
	if (p_shouldBind) {
		m_fbo->bind();
		return;
	}

	m_fbo->unbind();
}

void GuiManager::createEditor() {
	bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Begin("Scene");

	const float windowWidth = ImGui::GetContentRegionAvail().x;
	const float windowHeight = ImGui::GetContentRegionAvail().y;

	rescaleFramebuffer(windowWidth, windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	ImVec2 mousePosition = ImGui::GetCursorScreenPos();

	ImGui::GetWindowDrawList()->AddImage((void*)m_fbo->getTextureID(), ImVec2(mousePosition), ImVec2(mousePosition.x + windowWidth, mousePosition.y + windowHeight), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}

void GuiManager::rescaleFramebuffer(int p_newWidth, int p_newHeight) {
	m_fbo->resize(p_newWidth, p_newHeight);
}
