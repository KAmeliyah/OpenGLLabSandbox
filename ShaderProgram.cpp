#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string _vertPath, std::string _fragPath): m_Id(0)
{
	LoadProgram(_vertPath, _fragPath);
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::LoadProgram(const std::string _vertPath,const std::string _fragPath)
{
	//open file 
	std::ifstream vertexFile(_vertPath.c_str());
	std::ifstream fragmentFile(_fragPath.c_str());

	//file openeing error handling
	if (!vertexFile.is_open())
	{
		throw std::runtime_error("Failed to open vertex shader file [" + _vertPath + "]");
	}

	if (!fragmentFile.is_open())
	{
		throw std::runtime_error("Failed to open vertex shader file [" + _fragPath + "]");
	}

	std::stringstream vertBuffer;
	std::stringstream fragBuffer;
	
	//load contents of the file into the string stream
	try
	{
		vertBuffer << vertexFile.rdbuf();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		fragBuffer << fragmentFile.rdbuf();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	//move contents into a string and then into const char* to create the shaders
	std::string vertexCode = vertBuffer.str();
	std::string fragmentCode = fragBuffer.str();

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	// Create a new vertex shader, attach source code, compile it and
	// check for errors.

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("Error while making the vertex shader");
	}


	// Create a new fragment shader, attach source code, compile it and
	// check for errors.
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("Error while making the fragment shader");
	}

	//Create the shader program and attach the shader objects

	m_Id = glCreateProgram();
	glAttachShader(m_Id, vertexShaderId);
	glAttachShader(m_Id, fragmentShaderId);
	
	glBindAttribLocation(m_Id, 0, "a_Position");
	glBindAttribLocation(m_Id, 1, "a_TexCoord");

	glLinkProgram(m_Id);
	glGetProgramiv(m_Id, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::runtime_error("Failed to link the shader program");
	}

	//Clean up the shader objects since they are no longer needed
	glDetachShader(m_Id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(m_Id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);

}

void ShaderProgram::SetUniform(std::string _uniform, glm::vec4 _value)
{


}

void ShaderProgram::SetUniform(std::string _uniform, float _value)
{
}

void ShaderProgram::SetUniform(std::string _uniform, Texture* _texture)
{
}

GLuint ShaderProgram::GetId()
{
	return GLuint();
}
