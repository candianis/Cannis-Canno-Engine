#pragma once

#include "Renderer/RenderCommand/RenderCommand.h"
#include "Renderer/Model/Model.h"
#include "Renderer/Camera/Camera.h"
#include "Renderer/Shader/Shader.h"

namespace Cannis {
	class Renderer {
	public:
		// 
		static void BeginScene(Camera& p_camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& p_shader, const std::shared_ptr<Model>& p_model);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> m_sceneData;
	};
}