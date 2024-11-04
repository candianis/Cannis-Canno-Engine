#pragma once

#include "Renderer/RenderingContext.h"

struct GLFWwindow;

namespace Cannis {
	class OpenGLContext : public RenderingContext {
	public:
		OpenGLContext(GLFWwindow* p_windowHandle);
		~OpenGLContext() = default;

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_windowHandle;
	};
}