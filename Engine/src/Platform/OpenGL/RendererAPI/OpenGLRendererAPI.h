#pragma once

#include "ccpch.h"
#include "Renderer/RendererAPI/RendererAPI.h"

namespace Cannis {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		void Init() override;
		void SetClearColor(const glm::vec4& p_color) override;
		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& p_vertexArray) override;

	private:
		//void GLAPIENTRY	MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	};
}