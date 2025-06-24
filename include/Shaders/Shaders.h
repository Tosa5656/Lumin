#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

#include <glad/glad.h>

class Shader
{
public:
	Shader() {};
	Shader(const std::string& filePath, int type);
	GLuint getId() { return m_Shader; }
	int getType() { return m_Type; }
private:
	std::string m_ReadShaderSource(const std::string& filePath);
	GLuint m_CreateShader(int type, const GLchar* source);

	GLuint m_Shader;
	int m_Type;
	std::string m_Source;
};

class ShaderProgram
{
public:
	ShaderProgram() {};
	ShaderProgram(Shader vertexShader, Shader fragmentShader);
	void LinkShaders();
	GLuint getId() { return m_ShaderProgram; }
private:
	GLuint m_ShaderProgram;
	Shader m_VertexShader;
	Shader m_FragmentShader;
};