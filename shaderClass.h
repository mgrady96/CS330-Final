#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:

	GLuint ID;
	// Constructor 
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates
	void Activate();
	// Deletes the Shader
	void Delete();
private:
	// Checks if compiled properly
	void compileErrors(unsigned int shader, const char* type);
};


#endif