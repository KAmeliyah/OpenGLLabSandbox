#pragma once

#include <SDL2/SDL.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include "Texture.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "EventHandler.h"
#include <memory>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


struct GameWindow
{

	GameWindow();
	~GameWindow();

	//Inputs are handled frame by frame
	void Input();

	void Update(float _dt);

	void Draw(float _dt);

	void Quit();

	bool GetQuit() const;

private:

	SDL_Window* m_Window{ nullptr };
	int m_WindowWidth{ 0 };
	int m_WindowHeight{ 0 };

	std::shared_ptr<EventHandler> eventHandler = std::make_shared<EventHandler>();

	bool m_Quit{ false };

};

