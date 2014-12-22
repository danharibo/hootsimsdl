#ifndef _DRAWMANAGER_HPP_
#define _DRAWMANAGER_HPP_

#include <Entity.h>
#include <Controller.h>
#include <hootgl.h>
#include <vector>

class ArrayBuffer;

struct DrawData
{
	ArrayBuffer* geometry;
	int base;
	int count;
	GLuint texture0;
};

class DrawManager
{
public:
	
	void enqueue(const DrawData& draw)
	{
		drawqueue.push_back(draw);
	}
	
	void sort();
	
	void draw();
	
private:
	
	std::vector<DrawData> drawqueue;
};

#endif