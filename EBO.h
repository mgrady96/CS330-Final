#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:

	GLuint ID;
	// constructor
	EBO(GLuint* indices, GLsizeiptr size);

	// Binds EBO
	void Bind();
	// Unbinds EBO
	void Unbind();
	// Deletes EBO
	void Delete();
};

#endif