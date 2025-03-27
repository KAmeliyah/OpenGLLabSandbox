#pragma once
#include <SDL2/SDL.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <memory>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//Double as engine effectively

struct Window
{
	Window();
	~Window();

	void Update();

	void Draw();

	void Quit();
	

private:
	
	SDL_Window* window{ nullptr };




};

