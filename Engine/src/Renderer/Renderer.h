#pragma once

namespace Cannis {
	enum RendererAPI {
		None = 0, 
		OpenGL = 1,
		DirectX11 = 2,
		DirectX12 = 3,
		Metal = 4,
		Vulkan = 5
	};

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_rendererAPI; }

	private:
		static RendererAPI s_rendererAPI;

	};
}