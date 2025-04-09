#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <memory>

#include "EventHandler.h"
#include "GameObject.h"
#include "IndependentCamera.h"
#include "ShaderProgram.h"

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

	std::shared_ptr<ShaderProgram> m_Specular;

	std::vector<std::shared_ptr<GameObject>> m_Objects;

	std::shared_ptr<EventHandler> m_EventManager;

	std::shared_ptr<Camera> m_Camera;

	//For later, when there is multiple cameras
	std::vector<std::shared_ptr<Camera>> m_SceneCameras;

	bool m_Quit{ false };

};

