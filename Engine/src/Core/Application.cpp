#include <ccpch.h>

#include "Application.h"
#include "Events/AppEvent/AppEvent.h"
#include "Events/MouseEvent.h"
#include "Input/Input.h"

#include "Renderer/Buffer/BufferLayout/BufferLayout.h"
#include "Platform/OpenGL/VertexBuffer/OpenGLVertexBuffer.h"

#include "Renderer/Renderer.h"

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

		m_triangle = VertexArray::Create();

		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.3f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout bufferLayout = {
			{ "a_Position", ShaderDataType::Float3 },
			{ "a_Color", ShaderDataType::Float4 }
		};

		vertexBuffer->SetLayout(bufferLayout);
		m_triangle->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		size_t test = sizeof(indices) / sizeof(uint32_t);

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_triangle->SetIndexBuffer(indexBuffer);

		std::string vertexSource = "../Engine/assets/Shaders/ColorPos/colorPos.vert";

		std::string fragmentSource = "../Engine/assets/Shaders/ColorPos/colorPos.frag";


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

		std::string vertexSourceSquare = "../Engine/assets/Shaders/Simple/simpleShader.vert";
		std::string fragmentSourceSquare = "../Engine/assets/Shaders/Simple/simpleShader.frag";

		m_squareShader = std::move(Shader::Create(vertexSourceSquare, fragmentSourceSquare));
	}

	Application::~Application() {
		m_worldCoordinator->Shutdown();
	}

	void Application::Run() {
		while (m_running) {

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
