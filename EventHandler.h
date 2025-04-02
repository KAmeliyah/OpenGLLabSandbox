#pragma once
#include <SDL2/SDL.h>
struct EventHandler
{


	EventHandler();

	void HandleEvents();

	bool GetMoveRight();
	bool GetMoveLeft();
	bool GetMoveUp();
	bool GetMoveDown();
	bool GetJump();
	bool GetAttack();
	bool GetExit();

private:
	SDL_Event event{ 0 };

	bool m_MoveRight{ false };
	bool m_MoveLeft{ false };
	bool m_MoveUp{ false };
	bool m_MoveDown{ false };
	bool m_Jump{ false };
	bool m_Attack{ false };
	bool m_Exit{ false };
	


};

