#ifndef _GRAHPICSBUFFER_HPP_
#define _GRAHPICSBUFFER_HPP_

#include <hootgl.h>

/**
 * Provides a managed life-time GPU buffer and an easy to use interface.
 * 
 * @todo Provide a way to stream data
 * @todo Allow double buffered uploads, for performance. 
 */
class GraphicsBuffer
{
public:
	
	GraphicsBuffer()
	: buffer(0), bufferSize(0)
	{ }
	
	~GraphicsBuffer();
	
	void allocate(int size);

	void upload(int size, int offset, void* data);

	GLuint name() const { return buffer; }
private:
	
	GLuint buffer;
	GLsizei bufferSize;
};

#endif