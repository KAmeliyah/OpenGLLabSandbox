#pragma once
#include <SDL2/SDL.h>
struct EventHandler
{


	EventHandler();

	void HandleEvents();

private:
	SDL_Event event;
	


};

