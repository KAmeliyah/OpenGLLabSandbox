#include "GameWindow.h"

GameWindow::GameWindow()
{
	m_Window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	//Connect to graphics card

	if (!SDL_GL_CreateContext(m_Window))
	{
		std::cout << "No context" << std::endl;
		throw std::runtime_error("No context");
	}

}

GameWindow::~GameWindow()
{
	SDL_GL_DeleteContext(m_Window);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();

}

void GameWindow::Input()
{

	//Window Resizing
	SDL_GetWindowSize(m_Window, &m_WindowWidth, &m_WindowHeight);
	glViewport(0, 0, m_WindowWidth, m_WindowHeight);


	//Keyboard Event
	eventHandler->HandleEvents();


	if (eventHandler->GetExit())
	{
		m_Quit = true;
	}

}



void GameWindow::Update(float _dt)
{





}

void GameWindow::Draw(float _dt)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//GameObject in vector's vertex count

	//glDrawArrays(GL_TRIANGLES, 0, cat.vertex_count());

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

}

void GameWindow::Quit()
{
}

bool GameWindow::GetQuit() const
{
	return m_Quit;
}
