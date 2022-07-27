#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:

	GLuint ID;
	// Constructor 
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Binds 
	void Bind();
	// Unbinds
	void Unbind();
	// Deletes 
	void Delete();
};

#endif
