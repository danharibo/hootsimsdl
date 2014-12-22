#include "DrawManager.hpp"
#include "graphics/GraphicsBuffer.hpp"
#include "graphics/ArrayBuffer.hpp"

void DrawManager::sort()
{
	/* Sort Tree:
	 * Transparent
	 *  Depth in scene (max -> min)
	 *   Geometry
	 *    Material (can be batched).
	 * Opqaue
	 *  Depth in scene (min -> max)
	 *   Geometry
	 *    Material
	 */
}

void DrawManager::draw()
{
	for(DrawData& d : drawqueue)
	{
		glBindVertexArray(d.geometry->name());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, d.texture0);
		glDrawElements(GL_TRIANGLES, d.count, GL_UNSIGNED_INT, (GLvoid*)(d.base * sizeof (GLuint)));
	}
	
	drawqueue.clear();
}

