#include "EventHandler.h"

EventHandler::EventHandler()
{
}

void EventHandler::HandleEvents()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_Exit = true;
				break;

			case SDL_MOUSEMOTION:
				//https://gamedev.stackexchange.com/questions/139547/sdl2-mouse-camera-movement
				
				m_MouseMotion = true;
				m_MouseRelX = event.motion.xrel;
				m_MouseRelY = event.motion.yrel;


				break;

			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						m_Attack = true;
						break;

					default:
						break;

				}
				break;
			
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						m_Attack = false;
						break;
					case SDL_BUTTON_RIGHT:
						m_MouseMotion = false;
						break;

					default:
						break;
				}
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_w:
						m_MoveForward = true;
						
						break;
				
					case SDLK_s:
						m_MoveBack = true;
						break;
				
					case SDLK_d:
						m_MoveRight = true;
						break;
				
					case SDLK_a:
						m_MoveLeft = true;
						break;

					case SDLK_ESCAPE:
						m_Exit = true;
						break;

					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_w:
						m_MoveForward = false;
						break;

					case SDLK_s:
						m_MoveBack = false;
						break;

					case SDLK_d:
						m_MoveRight = false;
						break;

					case SDLK_a:
						m_MoveLeft = false;
						break;

					default:
						break;
				}
				break;


			default:
				break;
		}
	}

}

bool EventHandler::GetMoveRight()
{
	return m_MoveRight;
}

bool EventHandler::GetMoveLeft()
{
	return m_MoveLeft;
}

bool EventHandler::GetMoveForward()
{
	return m_MoveForward;
}

bool EventHandler::GetMoveBack()
{
	return m_MoveBack;
}

bool EventHandler::GetJump()
{
	return m_Jump;
}

bool EventHandler::GetAttack()
{
	return m_Attack;
}

bool EventHandler::GetExit()
{
	return m_Exit;
}



bool EventHandler::GetMouseMoving()
{
	return m_MouseMotion;
}

int EventHandler::GetMouseX()
{
	return m_MouseRelX;
}

int EventHandler::GetMouseY()
{
	return m_MouseRelY;
}
