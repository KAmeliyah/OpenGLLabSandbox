#include "EventHandler.h"

void EventHandler::HandleEvents()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				break;

			}
			break;

		default:
			break;
		}
	}

}
