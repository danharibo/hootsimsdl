#include "HootsimApp.hpp"

#include <hootgl.h>

#include <chrono>

HootsimApp::HootsimApp()
	: running(true), simulator(nullptr)
{
	
}

HootsimApp::~HootsimApp()
{
	if( simulator )
	{
		delete simulator;
	}
}

int HootsimApp::run(int argc, char** argv)
{
	createWindow("Hootsim 2000");
	
	simulator = new Simulator(&mq);
	
	auto lastClock = std::chrono::steady_clock::now();
	float tickAccumulator = 0.f;
	
	while( running )
	{
		handleEvents();
		
		if( !running ) break;
		
		auto timeDiff = std::chrono::steady_clock::now() - lastClock;
		tickAccumulator += std::chrono::duration_cast<std::chrono::milliseconds>(timeDiff).count() / 1000.f;
		
		if( tickAccumulator >= HOOTSIM_TICK_TIME )
		{
			update(HOOTSIM_TICK_TIME);
			tickAccumulator -= HOOTSIM_TICK_TIME;
		}
		
		if( !running ) break;
		
		draw();
		
		swapBuffers();
	}
	
	return 0;
}

void HootsimApp::setup()
{
	// Create some entities here or something.
}

void HootsimApp::quit()
{
	running = false;
}

void HootsimApp::parseArguments(int argc, char** argv)
{

}

void HootsimApp::createWindow(const std::string& title)
{
	// Non-op, see HootsimSDLApp.
}

void HootsimApp::draw()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void HootsimApp::update(float timedelta)
{
	simulator->tick();
}

