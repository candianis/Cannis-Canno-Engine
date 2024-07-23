#pragma once

#include <memory>
#include <mutex>

class VertexBuffer {
private:
	// @brief Interal ID for OpenGL to identify the buffer
	unsigned int m_rendererID;
	mutable std::mutex m;

public:
	// @brief Default constructor for a VBO
	// @param p_data pointer to the data the VBO will hold
	// @param p_size size of the data in bytes
	VertexBuffer(const void* p_data, unsigned int p_size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	// @brief Threadsafe 
	void SetData();
};