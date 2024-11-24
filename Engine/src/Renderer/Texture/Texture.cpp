#include "ccpch.h"

#include "Texture.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/Texture2D/OpenGLTexture2D.h"

namespace Cannis {
	std::shared_ptr<Texture> Texture::Create(const std::string& p_path, TextureType p_type) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				CC_CORE_ERROR("Renderer API is currently not supported");
				break;

			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(p_path, p_type);
				break;
		}
	}
}