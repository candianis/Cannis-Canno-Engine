#pragma once

#include "ccpch.h"
#include "Renderer/VertexArray/VertexArray.h"

namespace Cannis {
	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1,
			DirectX11 = 2,
			DirectX12 = 3,
			Metal = 4,
			Vulkan = 5
		};

		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& p_color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& p_vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;

	};
}