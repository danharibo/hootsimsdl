#include "HootsimApp.hpp"
#include "DrawManager.hpp"
#include "graphics/GraphicsBuffer.hpp"
#include "graphics/ArrayBuffer.hpp"

#include <hootgl.h>
#include <Controller.h>
#include <Entity.h>

#include <chrono>
#include <string>

// this shouldn't be included in the generic application :<
#include <SDL2/SDL_keycode.h>

const GLchar* sprite_vertex = R"(#version 130
#extension GL_ARB_explicit_attrib_location : enable

layout(location=0) in vec3 a_position;

void main(void)
{
	gl_Position = vec4(a_position, 1.0);
}

)";

const GLchar* sprite_fragment = R"(#version 130
uniform sampler2D texture0;

out vec4 colour;

void main(void)
{
	vec4 tex0 = texture(texture0, vec2(0.5, 0.5));
	colour = tex0;
}
)";

float sprite_verticies[] = {
	 0.5f, 0.5f, 0.f,
	 0.5f,-0.5f, 0.f,
	-0.5f, 0.5f, 0.f,
	-0.5f,-0.5f, 0.f,
};
unsigned int sprite_indicies[] = {
	0, 1, 2,
	2, 1, 3
};

const GLuint sprite_red[] = { 0xFF5555 };
const GLuint sprite_blue[] = { 0x5555FF };

/* Temporary Controller for visuals */
class SpriteController : public Controller
{
public:
	SpriteController(DrawManager* dm, Simulator *sm)
	: Controller(sm), drawer(dm)
	{
		this->mq->subscribe("draw", this);
		this->mq->subscribe("change_sprite", this);
		
		vertices.allocate(sizeof(sprite_verticies));
		vertices.upload(sizeof(sprite_verticies), 0, sprite_verticies);
		
		indices.allocate(sizeof(sprite_indicies));
		indices.upload(sizeof(sprite_indicies), 0, sprite_indicies);
		
		geometry.setGeometryBuffer(&vertices);
		geometry.setIndicesBuffer(&indices);
		
		geometry.update();
		
		glGenTextures(2, sprites);

		glBindTexture(GL_TEXTURE_2D, sprites[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, sprite_red);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glBindTexture(GL_TEXTURE_2D, sprites[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, sprite_blue);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
	}
	
	virtual void notify(const std::string& id, int to, int from, const std::string& message)
	{
		if ( id == "draw" )
		{
			Entity* e = entities[to];
			int sprite = e->get_property("sprite");
			drawer->enqueue({ &geometry, 0, 6, sprites[sprite] });
		}
		else if ( id == "change_sprite" )
		{
			Entity* e = entities[to];
			int sprite = e->get_property("sprite");
			e->update_property("sprite", (++sprite) % 2);
		}
	}
	
	virtual void tick() { }

private:
	DrawManager* drawer;
	ArrayBuffer geometry;
	GraphicsBuffer vertices;
	GraphicsBuffer indices;
	
	GLuint sprites[2];
};

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

/**
 * An example of some way to turn input events into other kinds of messages.
 * Probably could be done much better.
 */
class InputHandler : public Receiver
{
public:
	
	InputHandler(MessageQueue* mq)
	{
		set_messagequeue(mq);
		mq->subscribe("key_up", this);
	}
	
	virtual void super_notify(const std::string &msg_type, int to, int from, const std::string &message)
	{
		if( msg_type == "key_up" )
		{
			int keysym = std::atoi(message.c_str());
			if( keysym == SDLK_SPACE )
			{
				mq->broadcast("change_sprite", -1, -1, "");
			}
		}
	}
};

int HootsimApp::run(int argc, char** argv)
{
	createWindow("Hootsim 2000");
	
	simulator = new Simulator(&mq);
	
	DrawManager dm;
	
	SpriteController sc(&dm, simulator);
	simulator->register_controller(&sc);
	sc.add_requirement("sprite");
	
	InputHandler ih(&mq);
	
	GLuint program = hglCreateProgram(sprite_vertex, sprite_fragment);
	
	glUseProgram(program);
	glUniform1i(0, 0);
	
	Entity ent(simulator);
	simulator->register_entity(&ent);
	
	ent.add_property("sprite", 0);
	
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
		
		mq.broadcast("draw", -1, -1, "");
		
		draw();
		
		glUseProgram(program);
		
		dm.draw();
		
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

