#ifndef _ARRAYBUFFER_HPP_
#define _ARRAYBUFFER_HPP_
#include <hootgl.h>

class GraphicsBuffer;

class ArrayBuffer
{
public:
	ArrayBuffer()
	: array(0), geometry(nullptr), indices(nullptr)
	{
	}
	
	void setGeometryBuffer(GraphicsBuffer* buffer)
	{
		geometry = buffer;
	}
	
	void setIndicesBuffer(GraphicsBuffer* buffer)
	{
		indices = buffer;
	}
	
	void update();
	
	GLuint name() const
	{
		return array;
	}
	
private:
	GLuint array;
	GraphicsBuffer* geometry;
	GraphicsBuffer* indices;
};

#endif