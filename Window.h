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

//Double as engine effectively

struct Window
{
	Window();
	~Window();


	void Input(float _dt);

	void Update(float _dt);

	void Draw(float _dt);

	void Quit();

	bool GetQuit();
	

private:
	
	SDL_Window* m_Window{ nullptr };
	
	//std::shared_ptr<EventHandler> eventHandler = std::make_shared()
	
	bool m_Quit{ false };
	




};

