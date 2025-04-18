#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "GameWindow.h"

//only define in main but use stb image header where needed
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#undef main

int main()
{

	std::shared_ptr<GameWindow> game = std::make_shared<GameWindow>();
	SDL_SetRelativeMouseMode(SDL_TRUE);

	
	float dt = 1.0f / 60.0f;

	Uint32 startTime = SDL_GetTicks();
	Uint32 lastTime = startTime;
	float accumulatedTime = 0.0f;

	while (!game->GetQuit())
	{

		Uint32 currentTime = SDL_GetTicks();
		float frameTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		accumulatedTime += frameTime;

		
		game->Input();
		
		while (accumulatedTime >= dt)
		{
			
			game->Update(dt);
			

			accumulatedTime -= dt;
		}

		game->Draw(dt);
		

		//Render the frame


	}

	return 0;
}


////Prepare VBO

//// VBO is a memory buffer in the high speed memomry of the GPU. It holds information about the vertices

////triangle points - OpenGL vertices go counter clockwise
////This doesn't need to include z since it's 2D but it does here
//const GLfloat positions[] = {
//	0.0f, 0.5f, 0.0f,
//	-0.5f, 0.5f, 0.0f,
//	-0.5f, 0.0f, 0.0f,
//	-0.5f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f,
//	0.0f, 0.5f, 0.0f
//};


////define the colours for the points of the triangle
//const GLfloat colors[] = {
//	1.0f, 1.0f, 0.0f, 1.0f,
//	0.0f, 1.0f, 0.0f, 1.0f,
//	0.0f, 0.0f, 1.0f, 1.0f,
//	/*1.0f, 1.0f, 0.0f, 1.0f,
//	0.0f, 1.0f, 0.0f, 1.0f,
//	0.0f, 0.0f, 1.0f, 1.0f,*/

//};

//const GLfloat texCoords[] = {
//	1.0f,0.0f,
//	0.0f,0.0f,
//	0.0f,1.0f,
//	0.0f,1.0f,
//	1.0f,1.0f,
//	1.0f,0.0f,
//};

//
////handle to reference the VBO
//GLuint positionsVboId = 0;

////Create a new Vertex Buffer Object on the GPU and bind it
////Buffer Objects - store an array of unformatted memory allocated by the OpenGL context (GPU)
////glGenBufferes craetes the buffer object
//glGenBuffers(1, &positionsVboId);

//if (!positionsVboId)
//{
//	throw std::runtime_error("Couldn't bind the VBO");
//}


////This tells the GL_ARRAY_BUFFER that any data it gets is going to be copied into positionVboId 
//glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

//// Upload a copy of the data from memory into the new VBO
////GL_STATIC_DRAW - static memory on the graphics card
////GL_ARRAY_BUFFER is given the positions so it copies the vertex data into the VBO
//glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);




//GLuint colorsVboId = 0;

////Create a colours VBO on the GPU and bind it

//glGenBuffers(1, &colorsVboId);

//if (!colorsVboId)
//{
//	throw std::runtime_error("Couldn't bind the colours VBO");
//}

//glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

//glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);



//// Reset the state
////Clear GL_ARRAY_BUFFER since it doesn't need the positions data anymore
////since positionsVboId has it now
//glBindBuffer(GL_ARRAY_BUFFER, 0);


////Prepare VAO
////VAOs contain VBOs. Designed to store info about the complete rendered object
////So it stores each VBO(vertex) of the triangle

////handle to reference the VAO
//GLuint vaoId = 0;

//// Create a new Vertex Array Object on the GPU and assign it to vaoId
//glGenVertexArrays(1, &vaoId);

//if (!vaoId)
//{
//	throw std::runtime_error("Couldn't bind the VAO");
//}

////Bind the VAO as the current used object - This object is going to be drawn
//glBindVertexArray(vaoId);

//// Bind the position VBO, assign it to position 0 on the bound VAO
//// and flag it to be used
//glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);


////Specify how the cooridinate data goes into attribute index 0 and has 3 floats per vertex
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

////Enable attribute index 0 as being used
//glEnableVertexAttribArray(0);


////Bind the color VBO and assign it to position 1 on the Bound VAO
//glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);
//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
//glEnableVertexAttribArray(1);


//// Reset the state
//glBindBuffer(GL_ARRAY_BUFFER, 0);
//glBindVertexArray(0);


//orthographic projection
		//projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f,(float)WINDOW_HEIGHT, 0.0f, 1.0f);

		// Prepare model matrix. The scale is important because now our triangle
		// would be the size of a single pixel when mapped to an orthographic
		// projection.
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(100, WINDOW_HEIGHT - 100, 0));
		//model = glm::scale(model, glm::vec3(100, 100, 1));

			// Upload the model matrix
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			// Upload the projection matrix
		//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,glm::value_ptr(projection));

		//Draw the vertices of the triangle
		//glDrawArrays(GL_TRIANGLES, 0, 6);

	

