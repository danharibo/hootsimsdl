#include "GraphicsBuffer.hpp"

#include <cstring>

GraphicsBuffer::~GraphicsBuffer()
{
	if( buffer != 0 )
	{
		glDeleteBuffers(1, &buffer);
	}
}

void GraphicsBuffer::allocate(int size)
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
	bufferSize = size;
}

void GraphicsBuffer::upload(int size, int offset, void *data)
{
	if( offset + size > bufferSize )
	{
		/// @todo error state
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	void* mem = glMapBufferRange(GL_ARRAY_BUFFER, offset, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	std::memcpy(mem, data, size);
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

