#include "ccpch.h"

#include "Renderer.h"

namespace Cannis {
	std::unique_ptr<Renderer::SceneData> Renderer::m_sceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::BeginScene(Camera& p_camera) {
		m_sceneData->viewProjectionMatrix = p_camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& p_shader, const std::shared_ptr<VertexArray>& p_vertexArray) {
		//Save both the shader and the VA so that they are drawn after the lights have been submitted
		
		p_shader->Bind();
		p_shader->UploadUniform("u_viewProjection", m_sceneData->viewProjectionMatrix);

		p_vertexArray->Bind();
		RenderCommand::DrawIndexed(p_vertexArray);
	}
}