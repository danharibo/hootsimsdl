#ifndef _HOOTSIMSDLAPP_HPP_
#define _HOOTSIMSDLAPP_HPP_

#include <HootsimApp.hpp>
#include <SDL2/SDL.h>

class HootsimSDLApp : public HootsimApp
{
public:
	
	HootsimSDLApp();
	~HootsimSDLApp();
	
	void createWindow(const std::string& title);
	virtual void handleEvents();
	virtual void swapBuffers();
	
private:
	
	SDL_Window* window;
};

#endif // HOOTSIMSDLAPP_H
