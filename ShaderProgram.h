#pragma once
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include<sstream>
#include <stdexcept>

#include "Texture.h"

struct ShaderProgram
{

	ShaderProgram(std::string _vertPath, std::string _fragPath);

	~ShaderProgram();
	
	void LoadProgram(const std::string _vertPath,const std::string _fragPath);

	//Matrix upload
	void SetUniform(std::string _uniform, glm::mat4 _value);

	//Vec4 upload
	void SetUniform(std::string _uniform, glm::vec4 _value);
	
	//Vec3 upload
	void SetUniform(std::string _uniform, glm::vec3 _value);
	
	void SetUniform(std::string _uniform, float _value);

	void SetUniform(std::string _uniform, Texture* _texture);

	GLuint GetId();

private:
	GLuint m_Id;



};

