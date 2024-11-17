#include "ccpch.h"
#include "OpenGLVertexArray.h"
#include "Renderer/Shader/ShaderDataType.h"

#include <glad/glad.h>

namespace Cannis {
	OpenGLVertexArray::OpenGLVertexArray() {
		//It 
		glGenVertexArrays(1, &m_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_ID);
	}

	void OpenGLVertexArray::UnBind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& p_vertexBuffer) {
		CC_CORE_ASSERT(p_vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layouts");
		
		glBindVertexArray(m_ID);
		p_vertexBuffer->Bind();

		uint32_t index = 0;
		const BufferLayout& layout = p_vertexBuffer->GetLayout();
		for (const BufferElement& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToGLEnum(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset
			);
			index++;
		}

		m_vertexBuffers.push_back(p_vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& p_indexBuffer) {
		glBindVertexArray(m_ID);

		//The index buffer is added to this vertex array by just binding it
		p_indexBuffer->Bind();

		m_indexBuffer = p_indexBuffer;
	}
}
