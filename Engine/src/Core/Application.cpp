#include <ccpch.h>

#include "Application.h"
#include "Events/AppEvent/AppEvent.h"
#include "Events/MouseEvent.h"
#include "Input/Input.h"

#include "Renderer/Buffer/BufferLayout/BufferLayout.h"
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


		m_vertexArray = std::move(VertexArray::Create());

		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.3f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout bufferLayout = {
			{ "a_Position", ShaderDataType::Float3 },
			{ "a_Color", ShaderDataType::Float4 }
		};

		m_vertexBuffer->SetLayout(bufferLayout);
		m_vertexArray->AddVertexBuffer(m_vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		m_indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		std::string vertexSource =
			"#version 330 core\n"
			"layout (location = 0) in vec3 a_Position;\n"
			"layout (location = 1) in vec4 a_Color;\n"
			"out vec3 v_Position;\n"
			"out vec4 v_Color;\n"

			"void main()\n"
			"{\n"
			"v_Position = a_Position;"
			"v_Color = a_Color;"
			"   gl_Position = vec4(a_Position, 1.0);\n"
			"}\0";

		std::string fragmentSource =
			"#version 330 core\n"
			"layout (location = 0) out vec4 color;"
			"in vec3 v_Position;\n"
			"in vec4 v_Color;\n"

			"void main()\n"
			"{\n"
			"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"color = v_Color;"
			"}\n\0";

		m_shader = std::move(Shader::Create(vertexSource, fragmentSource));

		m_square = std::move(VertexArray::Create());


		float squareVertices[12] = {
			-0.5f, -0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		BufferLayout bufferLayoutSquare = {
			{ "a_Position", ShaderDataType::Float3 },
		};

		squareVB->SetLayout(bufferLayoutSquare);
		m_square->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_square->SetIndexBuffer(squareIB);

		std::string vertexSourceSquare =
			"#version 450 core\n"
			"layout (location = 0) in vec3 a_Position;\n"
			"out vec3 v_Position;\n"

			"void main()\n"
			"{\n"
			"	v_Position = a_Position;"
			"   gl_Position = vec4(a_Position, 1.0);\n"
			"}\0";

		std::string fragmentSourceSquare =
			"#version 450 core\n"
			"layout (location = 0) out vec4 color;"
			"in vec3 v_Position;\n"

			"void main()\n"
			"{\n"
				"color = vec4(0.2, 0.3f, 0.8f, 1.0f);\n"
			"}\n\0";

		m_squareShader = std::move(Shader::Create(vertexSourceSquare, fragmentSourceSquare));
	}

	Application::~Application() {
		m_worldCoordinator->Shutdown();
	}

	void Application::Run() {
		while (m_running) {
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_squareShader->Bind();
			m_square->Bind();
			glDrawElements(GL_TRIANGLES, m_square->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_shader->Bind();
			m_vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, GLsizei(m_indexBuffer->GetCount()), GL_UNSIGNED_INT, nullptr);

			m_worldCoordinator->Update();

			m_uiService->Begin();
			m_uiService->Update(m_worldCoordinator);
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
