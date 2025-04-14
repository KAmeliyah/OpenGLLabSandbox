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




	//can't init glew without connection to graphics card
	//Glew loads OpenGL and extensions at runtime
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialise glew");
	}

	

	m_WindowWidth = WINDOW_WIDTH;
	m_WindowHeight = WINDOW_HEIGHT;

	//set up event handler
	m_EventManager = std::make_shared<EventHandler>();

	
	//I'll make ground without using a model - i'll make the texture myself using a noise function to simulate gravel

	m_Player = std::make_shared<Player>("curuthers/curuthers.obj", "curuthers/Whiskers_diffuse.png");
	m_Player->SetEventManager(m_EventManager);
	



	//Set up main camera
	m_Camera = std::make_shared<TrackCamera>(m_WindowWidth, m_WindowHeight);
	m_Camera->SetEventManager(m_EventManager);
	m_Camera->SetTarget(m_Player);
	
	m_Specular = std::make_shared<ShaderProgram>("VertexShader.v", "SpecularFragmentShader.f");
	
	std::vector<std::string> pathsForFaces = {
		"assets/skybox/posx.jpg",
		"assets/skybox/negx.jpg",
		"assets/skybox/posy.jpg",
		"assets/skybox/negy.jpg",
		"assets/skybox/posz.jpg",
		"assets/skybox/negz.jpg" };

	m_Skybox = std::make_shared<Cubemap>("assets/skybox/reversed_cube.obj", pathsForFaces);

	m_SkyboxShader = std::make_shared<ShaderProgram>("Skybox.v", "Skybox.f");

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


	//Manages all input 
	m_EventManager->HandleEvents();

	if (m_EventManager->GetExit())
	{
		m_Quit = true;
	}


}



void GameWindow::Update(float _dt)
{
	//Apply movement

	m_Camera->Update(_dt);

	m_Player->Update(_dt);
	
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Player->OnCollision(m_Enemies.at(i)->GetCollider());

		m_Enemies.at(i)->Update(_dt);
		m_Enemies.at(i)->OnCollision(m_Player->GetCollider());
		
		//Collisions
		for (int j = 0; j < m_Enemies.size(); j++)
		{
			
			if (i != j)
			{
				m_Enemies.at(i)->OnCollision(m_Enemies.at(j)->GetCollider());
			}
		}
		
	}

	
}

void GameWindow::Draw(float _dt)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);


	glm::mat4 view = glm::mat4(glm::mat3(m_Camera->GetView()));

	//These call glUseProgram(skyboxshader)
	m_SkyboxShader->SetUniform("u_View", view);


	m_SkyboxShader->SetUniform("u_Projection", m_Camera->GetProjection());

	m_Skybox->Draw(m_SkyboxShader);

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	m_Specular->SetUniform("u_CameraPos", m_Camera->GetPosition());
	m_Specular->SetUniform("u_Projection", m_Camera->GetProjection());
	m_Specular->SetUniform("u_View", m_Camera->GetView());
	

	m_Player->Draw(_dt, m_Specular);

	for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies.at(i)->Draw(_dt,m_Specular);
	}



	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);


	

	SDL_GL_SwapWindow(m_Window);

}

void GameWindow::Quit()
{

}

bool GameWindow::GetQuit() const
{
	return m_Quit;
}
