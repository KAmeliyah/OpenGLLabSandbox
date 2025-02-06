#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#undef main

int main()
{

	SDL_Window* window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	//Connect to graphics card

	if (!SDL_GL_CreateContext(window))
	{
		throw std::runtime_error("No context");
	}

	//can't init glew without connection to graphics card

	int x = glewInit();

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialise glew");
	}

	

	//Prepare VBO

	//triangle points - OpenGL vertices go counter clockwise
	const GLfloat positions[] = {
	0.0f,0.5f,0.0f,
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f
	};


	GLuint positionsVboId = 0;

	//Create a new Vertex Buffer Object on the GPU and bind it
	
	glGenBuffers(1, &positionsVboId);

	if (!positionsVboId)
	{
		throw std::runtime_error("Couldn't bind the VBO");
	}

	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	// Upload a copy of the data from memory into the new VBO
	//GL_STATIC_DRAW - static memory on the graphics card

	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Prepare VAO

	GLuint vaoId = 0;

	// Create a new Vertex Array Object on the GPU and bind it
	glGenVertexArrays(1, &vaoId);

	if (!vaoId)
	{
		throw std::runtime_error("Couldn't bind the VAO");
	}

	glBindVertexArray(vaoId);

	// Bind the position VBO, assign it to position 0 on the bound VAO
	// and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(0);

	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	const GLchar* vertexShaderSrc =
		"attribute vec3 in_Position;            " \
		"                                       " \
		"void main()                            " \
		"{                                      " \
		" gl_Position = vec4(in_Position, 1.0); " \
		"}                                      ";



	// Create a new vertex shader, attach source code, compile it and
	// check for errors.
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("Error while making the vertex shader");
	}




	const GLchar* fragmentShaderSrc =
		"void main()                       " \
		"{                                 " \
		" gl_FragColor = vec4(0, 0, 1, 1); " \
		"}                                 ";


	// Create a new fragment shader, attach source code, compile it and
	// check for errors.
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}


	// Create new shader program and attach our shader objects
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	// Ensure the VAO "position" attribute stream gets set as the first position
	// during the link.
	glBindAttribLocation(programId, 0, "in_Position");

	// Perform the link and check for failure
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	// Detach and destroy the shader objects. These are no longer needed
	// because we now have a complete shader program.
	glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);


	bool quit = false;

	while (!quit)
	{
		SDL_Event e = { 0 };

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			//Instruct OpenGL to use our shader program and our VAO
			glUseProgram(programId);
			glBindVertexArray(vaoId);

			//Draw the vertices of the triangle
			glDrawArrays(GL_TRIANGLES, 0, 3);

			//Reset the state
			glBindVertexArray(0);
			glUseProgram(0);

			//Do drawing

			SDL_GL_SwapWindow(window);
		}
	}

	return 0;
}