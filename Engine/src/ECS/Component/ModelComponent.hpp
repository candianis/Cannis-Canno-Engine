#pragma once

#include "ccpch.h"
#include "Component.h"
#include "Renderer/VertexArray/VertexArray.h"
#include "Renderer/Buffer/IndexBuffer/IndexBuffer.h"
#include "Renderer/Buffer/VertexBuffer/VertexBuffer.h"
#include "Renderer/Buffer/BufferLayout/BufferLayout.h"

namespace Cannis {
	struct ModelComponent {
		ModelComponent() : modelMatrix(1) {}

		ModelComponent(float* p_vertices, size_t p_verticesSize, uint32_t* p_indices, size_t p_indicesSize, const BufferLayout& p_bufferLayout) : modelMatrix(glm::mat4(1)) {
			vertexArray = VertexArray::Create();

			std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(p_vertices, p_verticesSize);
			vertexBuffer->SetLayout(p_bufferLayout);
			vertexArray->AddVertexBuffer(vertexBuffer);

			std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(p_indices, p_indicesSize);
			vertexArray->SetIndexBuffer(indexBuffer);
		}

		glm::mat4 modelMatrix;
		std::shared_ptr<VertexArray> vertexArray;
	};
}