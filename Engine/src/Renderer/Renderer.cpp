#include "ccpch.h"

#include "Renderer.h"

namespace Cannis {
	std::unique_ptr<Renderer::SceneData> Renderer::m_sceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::BeginScene(Camera& p_camera) {
		m_sceneData->viewProjectionMatrix = p_camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& p_shader, const std::shared_ptr<Model>& p_model) {
		//Save both the shader and the VA so that they are drawn after the lights have been submitted
		p_shader->Bind();
		p_shader->UploadUniform("u_viewProjection", m_sceneData->viewProjectionMatrix);

		for (size_t i = 0; i < p_model->GetMeshes().size(); i++) {
			p_model->GetMeshes()[i]->Bind(p_shader->GetID());
			RenderCommand::DrawIndexed(p_model->GetMeshes()[i]->GetVAO());
		}
	}
}