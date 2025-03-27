#include "Window.h"

Window::Window()
{
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

}

Window::~Window()
{
	SDL_GL_DeleteContext(window);
	SDL_DestroyWindow(window);
	SDL_Quit();
	

}

void Window::Quit()
{

	

}
