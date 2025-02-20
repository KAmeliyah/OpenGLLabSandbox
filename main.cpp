#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>


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
	//Glew loads OpenGL and extensions at runtime

	int x = glewInit();

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialise glew");
	}

	float angle = 0;

	//Prepare VBO

	// VBO is a memory buffer in the high speed memomry of the GPU. It holds information about the vertices

	//triangle points - OpenGL vertices go counter clockwise
	//This doesn't need to include z since it's 2D but it does here
	const GLfloat positions[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	//0.0f, 0.5f, 0.0f,
	//0.5f, 0.5f, 0.0f,
	//0.5, -0.5f, 0.0f
	};


	//define the colours for the points of the triangle
	const GLfloat colors[] = {
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		/*1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,*/

	};

	
	//handle to reference the VBO
	GLuint positionsVboId = 0;

	//Create a new Vertex Buffer Object on the GPU and bind it
	//Buffer Objects - store an array of unformatted memory allocated by the OpenGL context (GPU)
	//glGenBufferes craetes the buffer object
	glGenBuffers(1, &positionsVboId);

	if (!positionsVboId)
	{
		throw std::runtime_error("Couldn't bind the VBO");
	}


	//This tells the GL_ARRAY_BUFFER that any data it gets is going to be copied into positionVboId 
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

	// Upload a copy of the data from memory into the new VBO
	//GL_STATIC_DRAW - static memory on the graphics card
	//GL_ARRAY_BUFFER is given the positions so it copies the vertex data into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);




	GLuint colorsVboId = 0;

	//Create a colours VBO on the GPU and bind it

	glGenBuffers(1, &colorsVboId);

	if (!colorsVboId)
	{
		throw std::runtime_error("Couldn't bind the colours VBO");
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);



	// Reset the state
	//Clear GL_ARRAY_BUFFER since it doesn't need the positions data anymore
	//since positionsVboId has it now
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Prepare VAO
	//VAOs contain VBOs. Designed to store info about the complete rendered object
	//So it stores each VBO(vertex) of the triangle

	//handle to reference the VAO
	GLuint vaoId = 0;

	// Create a new Vertex Array Object on the GPU and assign it to vaoId
	glGenVertexArrays(1, &vaoId);

	if (!vaoId)
	{
		throw std::runtime_error("Couldn't bind the VAO");
	}

	//Bind the VAO as the current used object - This object is going to be drawn
	glBindVertexArray(vaoId);

	// Bind the position VBO, assign it to position 0 on the bound VAO
	// and flag it to be used
	glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);


	//Specify how the cooridinate data goes into attribute index 0 and has 3 floats per vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	//Enable attribute index 0 as being used
	glEnableVertexAttribArray(0);


	//Bind the color VBO and assign it to position 1 on the Bound VAO
	glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(1);



	// Reset the state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);





	//const GLchar* vertexShaderSrc =
	//	"attribute vec3 in_Position;            " \
	//	"                                       " \
	//	"void main()                            " \
	//	"{                                      " \
	//	" gl_Position = vec4(in_Position, 1.0); " \
	//	"}                                      ";


	//v_Color needs to have the same name in each shader so that OpenGL knows how to link them
	const GLchar* vertexShaderSrc =
		"attribute vec3 a_Position;			   " \
		"attribute vec4 a_Color;               " \
		"                                       " \
		"varying vec4 v_Color;                 " \
		"uniform mat4 u_Projection;				"\
		"uniform mat4 u_Model;					"\
		"                                       " \
		"void main()                            " \
		"{                                      " \
		" gl_Position = u_Projection * u_Model * vec4(a_Position,1.0); " \
		" v_Color = a_Color;                  " \
		"}                                      " \
		"                                       ";


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


	/*

	const GLchar* fragmentShaderSrc =
		"void main()                       " \
		"{                                 " \
		" gl_FragColor = vec4(0, 0, 1, 1); " \
		"}                                 ";

	*/

	//Uniforms stay constant during the drawing of the entire shape

	//Uniforms act as variables within shaders that can be changed via code
	//u_Color can be changed instead of hard coding a colour value
	//const GLchar* fragmentShaderSrc =
	//	"uniform vec4 u_Color;    " \
	//	"                          " \
	//	"void main()               " \
	//	"{                         " \
	//	" gl_FragColor = u_Color; " \
	//	"}                         " \
	//	"                          ";
		
	
	const GLchar* fragmentShaderSrc =
		"varying vec4 v_Color;    " \
		"                          " \
		"void main()               " \
		"{                         " \
		" gl_FragColor = v_Color; " \
		"}                         " \
		"                          ";

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
	glBindAttribLocation(programId, 0, "a_Position");

	//a_color attribute stream gets set as the second position during the link
	glBindAttribLocation(programId, 1, "a_Color");

	// Perform the link and check for failure
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	

	////Store location of color uniform and check if successfully found
	////GLint is used for indexes and returns -1 as an error code
	//GLint colorUniformId = glGetUniformLocation(programId, "u_Color");
	//if (colorUniformId == -1)
	//{
	//	throw std::runtime_error("Location of uniform shader couldn't be found");
	//}


	// Detach and destroy the shader objects. These are no longer needed
	// because we now have a complete shader program.
	glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

	//Get location of uniform so that OpenGL knows where to upload data to
	GLint modelLoc = glGetUniformLocation(programId, "u_Model");
	if (modelLoc == -1)
	{
		throw std::runtime_error("Location of model matrix couldn't be found");
	}

	GLint projectionLoc = glGetUniformLocation(programId, "u_Projection");
	if (projectionLoc == -1)
	{
		throw std::runtime_error("Location of projection matrix couldn't be found");
	}


	bool quit = false;

	while (!quit)
	{

		int width = 0;
		int height = 0;

		SDL_GetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);

		SDL_Event e = { 0 };

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			
		}

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//Instruct OpenGL to use our shader program and our VAO
		glUseProgram(programId);
		glBindVertexArray(vaoId);

		//
		//glUniform4f(colorUniformId, 0, 1, 0, 1);

		//Prepare the perspective projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.1f, 100.0f);

		//Prep the model matrix
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, -2.5));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

		//Increase the angle for further rotation
		angle += 1.0f;

		//Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//Draw the vertices of the triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);




		//orthographic projection
		projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f,(float)WINDOW_HEIGHT, 0.0f, 1.0f);

		// Prepare model matrix. The scale is important because now our triangle
		// would be the size of a single pixel when mapped to an orthographic
		// projection.
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(100, WINDOW_HEIGHT - 100, 0));
		model = glm::scale(model, glm::vec3(100, 100, 1));

			// Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,glm::value_ptr(projection));

		//Draw the vertices of the triangle
		glDrawArrays(GL_TRIANGLES, 0, 6);


		//Reset the state
		glBindVertexArray(0);
		glUseProgram(0);

		//Do drawing
		SDL_GL_SwapWindow(window);
	}

	return 0;
}