#include "ccpch.h"
#include "Model.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/Model/OpenGLModel.h"


namespace Cannis {
	std::shared_ptr<Model> Model::Create(const std::string& p_path) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				CC_CORE_ERROR("Renderer API selected is not supported");
				break;

			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLModel>(p_path);
				break;
		}
	}
}