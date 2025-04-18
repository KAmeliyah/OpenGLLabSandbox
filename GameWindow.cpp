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
	

	//Could do a kill cam



	m_ObjectShader = std::make_shared<ShaderProgram>("ObjectVS.v", "ObjectFS.f");
	
	std::vector<std::string> pathsForFaces = {
		"assets/skybox/posx.jpg",
		"assets/skybox/negx.jpg",
		"assets/skybox/posy.jpg",
		"assets/skybox/negy.jpg",
		"assets/skybox/posz.jpg",
		"assets/skybox/negz.jpg" };

	m_Skybox = std::make_shared<Cubemap>("assets/skybox/reversed_cube.obj", pathsForFaces);

	m_SkyboxShader = std::make_shared<ShaderProgram>("Skybox.v", "Skybox.f");


	std::shared_ptr<Pickup> m_Powerup = std::make_shared<Pickup>("assets/primitives/cube.obj");
	m_Powerups.push_back(m_Powerup);

	m_PowerLight = std::make_shared<ShaderProgram>("Pickup.v", "Pickup.f");

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

		//Enemy collide with the player

	}


	for (int i = 0; i < m_Powerups.size(); i++)
	{
		m_Player->OnCollision(m_Powerups.at(i)->GetCollider());
	}

	//put in a guard to prevent more than four powerups at one time
	//Give them six possible locations to spawn in
}

void GameWindow::Draw(float _dt)
{

	//Render to render buffer object

	//Render to regular buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//SkyBox
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);


	glm::mat4 view = glm::mat4(glm::mat3(m_Camera->GetView()));

	m_SkyboxShader->SetUniform("u_View", view);
	m_SkyboxShader->SetUniform("u_Projection", m_Camera->GetProjection());

	m_Skybox->Draw(m_SkyboxShader);

	
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);


	//Enabling face culling
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);


	//Powerups
	m_PowerLight->SetUniform("u_Projection", m_Camera->GetProjection());
	m_PowerLight->SetUniform("u_View", m_Camera->GetView());
	m_PowerLight->SetUniform("u_LightColor", m_Powerups[0]->GetColor());
	m_Powerups[0]->Draw(_dt, m_PowerLight);

	
	//Other Objects
	//Need to find a way to have a dynamic thing for point lights
	m_ObjectShader->SetUniform("u_CameraPos", m_Camera->GetPosition());
	m_ObjectShader->SetUniform("u_Projection", m_Camera->GetProjection());
	m_ObjectShader->SetUniform("u_View", m_Camera->GetView());
	m_ObjectShader->SetUniform("u_DirLight", glm::vec3(0, 20, 0));
	m_ObjectShader->SetUniform("u_PLightPos", m_Powerups[0]->GetPosition());
	m_ObjectShader->SetUniform("u_PLightColor", m_Powerups[0]->GetColor());
	
	m_Player->Draw(_dt, m_ObjectShader);

	/*for (int i = 0; i < m_Enemies.size(); i++)
	{
		m_Enemies.at(i)->Draw(_dt,m_Specular);
	}*/



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
