#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Camera.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
GLfloat vertices[] =
{ // COORDINATES          /     COLORS      //  Texture coords

   -0.5f, 0.0f,  1.0f, 0.8f, 0.3f,  0.02f,  0.0f, 1.0f, // 0 pyramid
   -0.5f, 0.0f,  0.0f, 0.8f, 0.3f,  0.02f,  1.0f, 0.0f, // 1
	0.5f, 0.0f,  0.0f, 0.8f, 0.3f,  0.02f,  1.0f, 1.0f, // 2
	0.5f, 0.0f,  1.0f, 0.8f, 0.3f,  0.02f,  0.0f, 0.0f, // 3
	0.0f, 1.5f,  0.5f, 0.8f, 0.3f,  0.02f,  0.5f, 0.5f, // 4

   -0.5f,-2.0f,  1.0f, 0.8f, 0.3f,  0.02f,  1.0f, 0.0f, // 5 square
   -0.5f,-2.0f,  0.0f, 0.8f, 0.3f,  0.02f,  0.0f, 1.0f, // 6
	0.5f,-2.0f,  0.0f, 0.8f, 0.3f,  0.02f,  0.0f, 0.0f, // 7
	0.5f,-2.0f,  1.0f, 0.8f, 0.3f,  0.02f,  1.0f, 1.0f, // 8

   -3.0f, -2.0f,  3.0f, 0.8f, 0.3f,  0.02f,  0.0f, 1.0f, // 9 plane
   -3.0f, -2.0f, -3.0f, 0.8f, 0.3f,  0.02f,  1.0f, 0.0f, // 10
	3.0f, -2.0f,  3.0f, 0.8f, 0.3f,  0.02f,  1.0f, 1.0f, // 11
	3.0f, -2.0f, -3.0f, 0.8f, 0.3f,  0.02f,  0.0f, 0.0f, // 12

   -2.0f, -2.0f,  2.0f, 0.8f, 0.3f,  0.02f,  0.0f, 1.0f, // 13 square 2
   -2.0f, -2.0f, -2.0f, 0.8f, 0.3f,  0.02f,  1.0f, 0.0f, // 14
	2.0f, -2.0f,  2.0f, 0.8f, 0.3f,  0.02f,  1.0f, 1.0f, // 15
	2.0f, -2.0f, -2.0f, 0.8f, 0.3f,  0.02f,  0.0f, 0.0f, // 16
   -2.0f, -1.5f,  2.0f, 0.8f, 0.3f,  0.02f,  0.0f, 1.0f, // 17 
   -2.0f, -1.5f, -2.0f, 0.8f, 0.3f,  0.02f,  1.0f, 0.0f, // 18
	2.0f, -1.5f,  2.0f, 0.8f, 0.3f,  0.02f,  1.0f, 1.0f, // 19
	2.0f, -1.5f, -2.0f, 0.8f, 0.3f,  0.02f,  0.0f, 0.0f  // 20
};

// Indices for vertices order
GLuint indices[] =
{
		   0, 1, 2, // pyramid
		   0, 2, 3,
		   0, 1, 4,
		   1, 2, 4,
		   2, 3, 4,
		   3, 0, 4,


		   0, 5, 1, // square
		   1, 6, 5,
		   0, 5, 3,
		   3, 5, 8,
		   1, 6, 2,
		   2, 6, 7,
		   2, 7, 3,
		   3, 7, 8,

		   9, 10, 11, // plane
		   11, 12, 10,

		   13, 14, 15, // square 2
		   14, 15, 16,
		   17, 18, 19,
		   18, 19, 20,

		   13, 14, 17,
		   13, 14, 18,
		   15, 16, 19,
		   15, 16, 20,

		   13, 15, 17,
		   13, 15, 18,
		   14, 16, 19,
		   14, 16, 20

	
};

//lightbox vertices
GLfloat lightVertices[] =
{
	//  coordinates 
	-0.1f, -0.1f,   0.1f,
	-0.1f, -0.1f,  -0.1f,
	 0.1f, -0.1f,  -0.1f,
	 0.1f, -0.1f,   0.1f,
	-0.1f,  0.1f,   0.1f,
	-0.1f,  0.1f,  -0.1f,
	 0.1f,  0.1f,  -0.1f,
	 0.1f,  0.1f,   0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};



int main()
{
	// Initialize GLFW
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow 
	GLFWwindow* window = glfwCreateWindow(width, height, "Mikayla Grady Final Project", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//Load GLAD 
	gladLoadGL();
	glViewport(0, 0, width, height);



	// Generates Shader 
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object 
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object 
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes 
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind 
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	
	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();



	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));



	// Texture

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("pngwing.com.png", &widthImg, &heightImg, &numColCh, 0);



	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// camera inputs
		camera.Inputs(window);

		// camera matrix
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// exports camera matrix to the vertex shader
		camera.Matrix(shaderProgram, "camMatrix");

		

		//binds texture 
		glBindTexture(GL_TEXTURE_2D, texture);

		// Bind the VAO 
		VAO1.Bind();

		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Swap back buffer with the front buffer
		glfwSwapBuffers(window);


		glfwPollEvents();
	}



	// Delete objects created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();
	// Delete window 
	glfwDestroyWindow(window);
	// Terminate GLFW 
	glfwTerminate();
	return 0;
}