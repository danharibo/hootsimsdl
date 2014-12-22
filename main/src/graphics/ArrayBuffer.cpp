#include "ArrayBuffer.hpp"
#include "GraphicsBuffer.hpp"

void ArrayBuffer::update()
{
	if( array == 0 )
	{
		glGenVertexArrays( 1, &array );
	}
	
	glBindVertexArray( array );
	
	glBindBuffer( GL_ARRAY_BUFFER, geometry->name() );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indices->name() );
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}
