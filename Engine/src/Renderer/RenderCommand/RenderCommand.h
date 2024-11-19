#pragma once

#include "ccpch.h"
#include "Renderer/RendererAPI/RendererAPI.h"

namespace Cannis {
	class RenderCommand {
	public:
		inline static void Init() {
			s_rendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& p_color) {
			s_rendererAPI->SetClearColor(p_color);
		}

		inline static void Clear() {
			s_rendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& p_vertexArray) {
			s_rendererAPI->DrawIndexed(p_vertexArray);
		}

	private:
		static std::unique_ptr<RendererAPI> s_rendererAPI;
	};
}