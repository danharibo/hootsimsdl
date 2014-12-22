#include "HootsimSDLApp.hpp"
#include "MessageQueue.h"

#include <iostream>

HootsimSDLApp::HootsimSDLApp()
	: window(nullptr)
{

}

HootsimSDLApp::~HootsimSDLApp()
{
	if( window != nullptr )
	{
		SDL_DestroyWindow(window);
	}
}

void HootsimSDLApp::createWindow(const std::string& title)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	
	window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	
	if( window == nullptr )
	{
		/** @todo add throw block in main to capture useful errors like this */
		std::cerr << "Error Creating Window: " << SDL_GetError() << std::endl;
	}
	
	SDL_GL_CreateContext(window);
}

void HootsimSDLApp::handleEvents()
{
	SDL_Event event;
	while( SDL_PollEvent(&event) )
	{
		switch(event.type)
		{
		case SDL_KEYDOWN:
			getMessageQueue().broadcast("key_down", -1, -1, std::to_string(event.key.keysym.sym));
			break;
		case SDL_KEYUP:
			getMessageQueue().broadcast("key_up", -1, -1, std::to_string(event.key.keysym.sym));
			break;
		case SDL_QUIT:
			quit();
		break;
		}
	}
}

void HootsimSDLApp::swapBuffers()
{
	if( window != nullptr )
	{
		SDL_GL_SwapWindow(window);
	}
}


