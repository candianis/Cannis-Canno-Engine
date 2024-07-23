#pragma once

#include <memory>
#include <mutex>

class IndexBuffer {
private:
	unsigned int m_rendererID;
	unsigned int m_count;
	mutable std::mutex m;

public:
	// @brief Default constructor for a IBO
	// @param p_data Data the IBO holds
	// @param p_count Element size of the data
	IndexBuffer(const unsigned int* p_data, unsigned int p_count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_count; }
};