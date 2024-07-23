#pragma once

#include "../VertexBuffer/VertexBuffer.h"
#include "../VertexBufferLayout/VertexBufferLayout.h"

class VertexArray {
private:
	unsigned int m_rendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& p_vb, const VertexBufferLayout& p_layout);

	void Bind() const;
	void Unbind() const;
};