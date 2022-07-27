#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:

	GLuint ID;

	VAO();

	// Links
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds
	void Bind();
	// Unbinds
	void Unbind();
	// Deletes
	void Delete();
};

#endif