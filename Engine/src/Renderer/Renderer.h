#pragma once

#include "Renderer/RenderCommand/RenderCommand.h"
#include "VertexArray/VertexArray.h"

namespace Cannis {
	class Renderer {
	public:
		// 
		static void BeginScene();
		static void EndScene();


		static void Submit(const std::shared_ptr<VertexArray>& p_vertexArray);


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:

	};
}