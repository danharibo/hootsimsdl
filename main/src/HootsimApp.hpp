#ifndef _HOOTSIMAPP_HPP_
#define _HOOTSIMAPP_HPP_
#include <string>

/// 30 Hz tick rate
#define HOOTSIM_TICK_TIME (1.f/30.f)

#include <Simulator.h>
#include <MessageQueue.h>

/**
 * Implements Basic logic for the hootsim client
 */
class HootsimApp
{
public:
	
	HootsimApp();
	~HootsimApp();
	
	int run(int argc, char** argv);
	
	void setup();
	
	void quit();
	
	void parseArguments(int argc, char** argv);
	
	/** Specialised to create windows by Implementors. */
	virtual void createWindow(const std::string& title);
	/** Consumes interface events in Implementors */
	virtual void handleEvents() = 0;
	/** Swaps the Implementors backbuffer */
	virtual void swapBuffers() = 0;
	
	Simulator* getSimulator() { return simulator; }
	
private:
	
	void update(float timedelta);
	
	void draw();
	
	bool running;
	
	MessageQueue mq;
	Simulator* simulator;
};

#endif
