#include "Window.h"

Window::Window()
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

Window::~Window()
{
	SDL_GL_DeleteContext(m_Window);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
	

}

void Window::Input(float _dt)
{


}

void Window::Update(float _dt)
{
}

void Window::Draw(float _dt)
{

}

void Window::Quit()
{

	

}

bool Window::GetQuit()
{
	return m_Quit;
}
