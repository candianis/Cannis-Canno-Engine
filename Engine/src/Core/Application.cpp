#include <ccpch.h>

#include "Application.h"
#include "Events/AppEvent/AppEvent.h"
#include "Events/MouseEvent.h"
#include "Input/Input.h"

#include "Platform/OpenGL/VertexBuffer/OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Cannis {
	Application* Application::s_instance = nullptr;

	Application::Application() : m_running(true) {
		CC_ASSERT(!s_instance, "Application already exists");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetSysEventCallback(std::bind(&Application::OnSysEvent, this, std::placeholders::_1));
		m_uiService = std::make_unique<UIService>();
		
		m_eventDispatcher = std::make_shared<SysEventDispatcher>();
		m_eventDispatcher->Subscribe(EventType::WindowClose, std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		m_worldCoordinator = std::make_shared<WorldCoordinator>(m_eventDispatcher);
		m_worldCoordinator->Init();
		m_worldCoordinator->SubscribeToEvent();

		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);

		float vertices[9] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[3] = { 0, 1, 2 };

		m_indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		std::string vertexSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		std::string fragmentSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
			"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

		m_shader = std::make_unique<Shader>(vertexSource, fragmentSource);
	}

	Application::~Application() {
		m_worldCoordinator->Shutdown();
	}

	void Application::Run() {
		while (m_running) {
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_shader->Bind();
			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_worldCoordinator->Update();

			m_uiService->Begin();
			m_uiService->Update();
			m_worldCoordinator->OnUIRender();
			m_uiService->End();
			
			m_window->OnUpdate();
		}
	}

	void Application::OnSysEvent(SysEvent& p_event) {
		m_eventDispatcher->EmitEvent(p_event);
	}

	void Application::OnWindowClose(const SysEvent& p_event) {
		m_running = false;
	}
}
