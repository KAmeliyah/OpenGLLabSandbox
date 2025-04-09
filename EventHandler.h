#pragma once
#include <SDL2/SDL.h>
#include <iostream>
struct EventHandler
{


	EventHandler();

	void HandleEvents();

	bool GetMouseMoving();
	int GetMouseX();
	int GetMouseY();

	bool GetMoveRight();
	bool GetMoveLeft();
	bool GetMoveForward();
	bool GetMoveBack();
	bool GetJump();
	bool GetAttack();
	bool GetExit();

	
	


private:
	SDL_Event event{ 0 };

	
	bool m_MouseMotion{ false };
	int m_MouseRelX{ 0 };
	int m_MouseRelY{ 0 };

	bool m_MoveRight{ false };
	bool m_MoveLeft{ false };
	bool m_MoveForward{ false };
	bool m_MoveBack{ false };
	bool m_Jump{ false };
	bool m_Attack{ false };
	bool m_Exit{ false };
	


};

