// Garcia Ortega Fernanda    320301159 
//Fecha de entrega: 06/03/2026    Practica 4
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico Práctica 04 - Garcia Ortega Fernanda", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float verticesGray[] = {
		-0.5f, -0.5f, 0.5f, 0.52f, 0.54f, 0.46f,//Frente
		0.5f, -0.5f, 0.5f,  0.52f, 0.54f, 0.46f,
		0.5f,  0.5f, 0.5f,  0.52f, 0.54f, 0.46f,
		0.5f,  0.5f, 0.5f,  0.52f, 0.54f, 0.46f,
		-0.5f,  0.5f, 0.5f, 0.52f, 0.54f, 0.46f,
		-0.5f, -0.5f, 0.5f, 0.52f, 0.54f, 0.46f,
		
	    -0.5f, -0.5f,-0.5f, 0.52f, 0.54f, 0.46f,//Cara de atrás 
		 0.5f, -0.5f,-0.5f, 0.52f, 0.54f, 0.46f,
		 0.5f,  0.5f,-0.5f, 0.52f, 0.54f, 0.46f,
		 0.5f,  0.5f,-0.5f, 0.52f, 0.54f, 0.46f,
	    -0.5f,  0.5f,-0.5f, 0.52f, 0.54f, 0.46f,
	    -0.5f, -0.5f,-0.5f, 0.52f, 0.54f, 0.46f,
		
		 0.5f, -0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,//cara lateral derecha 
		 0.5f, -0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
		 0.5f,  0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
		 0.5f,  0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
		 0.5f,  0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,
		 0.5f,  -0.5f, 0.5f,  0.52f, 0.54f, 0.46f ,
      
		-0.5f,  0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,//cara lateral izquierda 
		-0.5f,  0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
		-0.5f, -0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
		-0.5f, -0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
		-0.5f, -0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,
		-0.5f,  0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,
		
		-0.5f, -0.5f, -0.5f, 0.52f, 0.54f, 0.46f ,//cara de abajo 
		0.5f, -0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
		0.5f, -0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,
		0.5f, -0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,
		-0.5f, -0.5f,  0.5f, 0.52f, 0.54f, 0.46f ,
		-0.5f, -0.5f, -0.5f, 0.52f, 0.54f, 0.46f ,
		
		-0.5f,  0.5f, -0.5f,0.47f, 0.49f, 0.41f,//cara de arriba (gris más oscuro)
		0.5f,  0.5f, -0.5f, 0.47f, 0.49f, 0.41f,
		0.5f,  0.5f,   0.5f,0.47f, 0.49f, 0.41f,
		0.5f,  0.5f,   0.5f,0.47f, 0.49f, 0.41f,
		-0.5f,  0.5f,  0.5f,0.47f, 0.49f, 0.41f,
		-0.5f,  0.5f, -0.5f,0.47f, 0.49f, 0.41f,
	};
	float verticesGrayF[] = {
	-0.5f, -0.5f, 0.5f, 0.47f, 0.49f, 0.41f,//Front
	0.5f, -0.5f, 0.5f,  0.47f, 0.49f, 0.41f,
	0.5f,  0.5f, 0.5f,  0.47f, 0.49f, 0.41f,
	0.5f,  0.5f, 0.5f,  0.47f, 0.49f, 0.41f,
	-0.5f,  0.5f, 0.5f, 0.47f, 0.49f, 0.41f,
	-0.5f, -0.5f, 0.5f, 0.47f, 0.49f, 0.41f,

	-0.5f, -0.5f,-0.5f, 0.47f, 0.49f, 0.41f,//Back
	 0.5f, -0.5f,-0.5f, 0.47f, 0.49f, 0.41f,
	 0.5f,  0.5f,-0.5f, 0.47f, 0.49f, 0.41f,
	 0.5f,  0.5f,-0.5f, 0.47f, 0.49f, 0.41f,
	-0.5f,  0.5f,-0.5f, 0.47f, 0.49f, 0.41f,
	-0.5f, -0.5f,-0.5f, 0.47f, 0.49f, 0.41f,

	 0.5f, -0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,//cara lateral derecha (gris claro)
	 0.5f, -0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
	 0.5f,  0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
	 0.5f,  0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
	 0.5f,  0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,
	 0.5f,  -0.5f, 0.5f,  0.52f, 0.54f, 0.46f ,

	-0.5f,  0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,//cara lateral izquierda (gris claro)
	-0.5f,  0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
	-0.5f, -0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
	-0.5f, -0.5f, -0.5f,  0.52f, 0.54f, 0.46f ,
	-0.5f, -0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,
	-0.5f,  0.5f,  0.5f,  0.52f, 0.54f, 0.46f ,

	-0.5f, -0.5f, -0.5f, 0.47f, 0.49f, 0.41f,//cara de abajo 
	0.5f, -0.5f, -0.5f,  0.47f, 0.49f, 0.41f ,
	0.5f, -0.5f,  0.5f,  0.47f, 0.49f, 0.41f,
	0.5f, -0.5f,  0.5f,  0.47f, 0.49f, 0.41f,
	-0.5f, -0.5f,  0.5f, 0.47f, 0.49f, 0.41f ,
	-0.5f, -0.5f, -0.5f, 0.47f, 0.49f, 0.41f ,

	-0.5f,  0.5f, -0.5f,0.47f, 0.49f, 0.41f,//cara de arriba 
	0.5f,  0.5f, -0.5f, 0.47f, 0.49f, 0.41f,
	0.5f,  0.5f,   0.5f,0.47f, 0.49f, 0.41f,
	0.5f,  0.5f,   0.5f,0.47f, 0.49f, 0.41f,
	-0.5f,  0.5f,  0.5f,0.47f, 0.49f, 0.41f,
	-0.5f,  0.5f, -0.5f,0.47f, 0.49f, 0.41f,
	};
	float verticesBeige[] = {
		-0.5f, -0.5f, 0.5f, 0.86f,0.82f,0.65f,//Front
		0.5f, -0.5f, 0.5f,  0.86f,0.82f,0.65f,
		0.5f,  0.5f, 0.5f,  0.86f,0.82f,0.65f,
		0.5f,  0.5f, 0.5f,  0.86f,0.82f,0.65f,
		-0.5f,  0.5f, 0.5f, 0.86f,0.82f,0.65f,
		-0.5f, -0.5f, 0.5f, 0.86f,0.82f,0.65f,

		-0.5f, -0.5f,-0.5f, 0.86f,0.82f,0.65f,//Back
		 0.5f, -0.5f,-0.5f, 0.86f,0.82f,0.65f,
		 0.5f,  0.5f,-0.5f, 0.86f,0.82f,0.65f,
		 0.5f,  0.5f,-0.5f, 0.86f,0.82f,0.65f,
		-0.5f,  0.5f,-0.5f, 0.86f,0.82f,0.65f,
		-0.5f, -0.5f,-0.5f, 0.86f,0.82f,0.65f,

		 0.5f, -0.5f,  0.5f,  0.86f,0.82f,0.65f ,//cara lateral derecha 
		 0.5f, -0.5f, -0.5f,  0.86f,0.82f,0.65f,
		 0.5f,  0.5f, -0.5f,  0.86f,0.82f,0.65f,
		 0.5f,  0.5f, -0.5f,  0.86f,0.82f,0.65f,
		 0.5f,  0.5f,  0.5f,  0.86f,0.82f,0.65f,
		 0.5f,  -0.5f, 0.5f,  0.86f,0.82f,0.65f,

		-0.5f,  0.5f,  0.5f,  0.86f,0.82f,0.65f,//cara lateral izquierda 
		-0.5f,  0.5f, -0.5f,  0.86f,0.82f,0.65f,
		-0.5f, -0.5f, -0.5f,  0.86f,0.82f,0.65f,
		-0.5f, -0.5f, -0.5f,  0.86f,0.82f,0.65f,
		-0.5f, -0.5f,  0.5f,  0.86f,0.82f,0.65f,
		-0.5f,  0.5f,  0.5f,  0.86f,0.82f,0.65f,

		-0.5f, -0.5f, -0.5f, 0.86f,0.82f,0.65f,//cara de abajo 
		0.5f, -0.5f, -0.5f,  0.86f,0.82f,0.65f,
		0.5f, -0.5f,  0.5f,  0.86f,0.82f,0.65f,
		0.5f, -0.5f,  0.5f,  0.86f,0.82f,0.65f,
		-0.5f, -0.5f,  0.5f, 0.86f,0.82f,0.65f,
		-0.5f, -0.5f, -0.5f, 0.86f,0.82f,0.65f,

		-0.5f,  0.5f, -0.5f, 0.86f,0.82f,0.65f,//cara de arriba 
		0.5f,  0.5f, -0.5f,  0.86f,0.82f,0.65f,
		0.5f,  0.5f,  0.5f,  0.86f,0.82f,0.65f,
		0.5f,  0.5f,  0.5f,  0.86f,0.82f,0.65f,
		-0.5f,  0.5f,  0.5f, 0.86f,0.82f,0.65f,
		-0.5f,  0.5f, -0.5f, 0.86f,0.82f,0.65f,
	};
	float verticesWhite[] = {
		-0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f,1.0f,1.0f,
		0.5f,  0.5f, 0.5f,  1.0f,1.0f,1.0f,
		0.5f,  0.5f, 0.5f,  1.0f,1.0f,1.0f,
		-0.5f,  0.5f, 0.5f, 1.0f,1.0f,1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,

		-0.5f, -0.5f,-0.5f, 1.0f,1.0f,1.0f,//Back
		 0.5f, -0.5f,-0.5f, 1.0f,1.0f,1.0f,
		 0.5f,  0.5f,-0.5f, 1.0f,1.0f,1.0f,
		 0.5f,  0.5f,-0.5f, 1.0f,1.0f,1.0f,
		-0.5f,  0.5f,-0.5f, 1.0f,1.0f,1.0f,
		-0.5f, -0.5f,-0.5f, 1.0f,1.0f,1.0f,

		 0.5f, -0.5f,  0.5f,  1.0f,1.0f,1.0f,//cara lateral derecha 
		 0.5f, -0.5f, -0.5f,  1.0f,1.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,1.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,1.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,1.0f,1.0f,
		 0.5f,  -0.5f, 0.5f,  1.0f,1.0f,1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f,1.0f,1.0f,//cara lateral izquierda 
		-0.5f,  0.5f, -0.5f,  1.0f,1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f,1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f,1.0f,1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f,1.0f,1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f,1.0f,1.0f,

		-0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,//cara de abajo 
		0.5f, -0.5f, -0.5f,  1.0f,1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f,1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f,1.0f,1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,//cara de arriba 
		0.5f,  0.5f, -0.5f,  1.0f,1.0f,1.0f,
		0.5f,  0.5f,  0.5f,  1.0f,1.0f,1.0f,
		0.5f,  0.5f,  0.5f,  1.0f,1.0f,1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f,1.0f,1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f,1.0f,1.0f,
	};
	float verticesBlack[] = {
		-0.5f, -0.5f, 0.5f, 0.1f,0.1f,0.1f,//Front
		0.5f, -0.5f, 0.5f,  0.1f,0.1f,0.1f,
		0.5f,  0.5f, 0.5f,  0.1f,0.1f,0.1f,
		0.5f,  0.5f, 0.5f,  0.1f,0.1f,0.1f,
		-0.5f,  0.5f, 0.5f, 0.1f,0.1f,0.1f,
		-0.5f, -0.5f, 0.5f, 0.1f,0.1f,0.1f,

		-0.5f, -0.5f,-0.5f, 0.1f,0.1f,0.1f,//Back
		 0.5f, -0.5f,-0.5f, 0.1f,0.1f,0.1f,
		 0.5f,  0.5f,-0.5f, 0.1f,0.1f,0.1f,
		 0.5f,  0.5f,-0.5f, 0.1f,0.1f,0.1f,
		-0.5f,  0.5f,-0.5f, 0.1f,0.1f,0.1f,
		-0.5f, -0.5f,-0.5f, 0.1f,0.1f,0.1f,

		 0.5f, -0.5f,  0.5f,  0.1f,0.1f,0.1f ,//cara lateral derecha 
		 0.5f, -0.5f, -0.5f,  0.1f,0.1f,0.1f ,
		 0.5f,  0.5f, -0.5f,  0.1f,0.1f,0.1f,
		 0.5f,  0.5f, -0.5f,  0.1f,0.1f,0.1f,
		 0.5f,  0.5f,  0.5f,  0.1f,0.1f,0.1f,
		 0.5f,  -0.5f, 0.5f,  0.1f,0.1f,0.1f ,

		-0.5f,  0.5f,  0.5f,  0.1f,0.1f,0.1f ,//cara lateral izquierda 
		-0.5f,  0.5f, -0.5f,  0.1f,0.1f,0.1f,
		-0.5f, -0.5f, -0.5f,  0.1f,0.1f,0.1f,
		-0.5f, -0.5f, -0.5f,  0.1f,0.1f,0.1f,
		-0.5f, -0.5f,  0.5f,  0.1f,0.1f,0.1f,
		-0.5f,  0.5f,  0.5f,  0.1f,0.1f,0.1f,

		-0.5f, -0.5f, -0.5f, 0.1f,0.1f,0.1f,//cara de abajo 
		0.5f, -0.5f, -0.5f,  0.1f,0.1f,0.1f,
		0.5f, -0.5f,  0.5f,  0.1f,0.1f,0.1f,
		0.5f, -0.5f,  0.5f,  0.1f,0.1f,0.1f,
		-0.5f, -0.5f,  0.5f, 0.1f,0.1f,0.1f,
		-0.5f, -0.5f, -0.5f, 0.1f,0.1f,0.1f,

		-0.5f,  0.5f, -0.5f, 0.1f,0.1f,0.1f,//cara de arriba 
		0.5f,  0.5f, -0.5f,  0.1f,0.1f,0.1f,
		0.5f,  0.5f,  0.5f,  0.1f,0.1f,0.1f,
		0.5f,  0.5f,  0.5f,  0.1f,0.1f,0.1f,
		-0.5f,  0.5f,  0.5f, 0.1f,0.1f,0.1f,
		-0.5f,  0.5f, -0.5f, 0.1f,0.1f,0.1f,
	};



	GLuint VBO_gray, VAO_gray;
	GLuint VBO_grayf, VAO_grayf;
	GLuint VBO_beige, VAO_beige;
	GLuint VBO_white, VAO_white;
	GLuint VBO_black, VAO_black;


	// GRIS
	// Enlazar  Vertex Array Object
	glGenVertexArrays(1, &VAO_gray);
	glGenBuffers(1, &VBO_gray);

	glBindVertexArray(VAO_gray);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_gray);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesGray), verticesGray, GL_STATIC_DRAW);
	//Posicion 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// GRIS Fuerte 
	glGenVertexArrays(1, &VAO_grayf);
	glGenBuffers(1, &VBO_grayf);

	glBindVertexArray(VAO_grayf);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_grayf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesGrayF), verticesGrayF, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// BEIGE
	glGenVertexArrays(1, &VAO_beige);
	glGenBuffers(1, &VBO_beige);

	glBindVertexArray(VAO_beige);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_beige);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBeige), verticesBeige, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//WHITE
	glGenVertexArrays(1, &VAO_white);
	glGenBuffers(1, &VBO_white);

	glBindVertexArray(VAO_white);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_white);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesWhite), verticesWhite, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// BLACK
	glGenVertexArrays(1, &VAO_black);
	glGenBuffers(1, &VBO_black);

	glBindVertexArray(VAO_black);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_black);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBlack), verticesBlack, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	///*glGenVertexArrays(1, &VAO_gray);
	//glGenBuffers(1, &VBO_gray);


	////glGenBuffers(1, &EBO);

	//// Enlazar  Vertex Array Object
	//glBindVertexArray(VAO);

	////2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	///*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	//// 4. Despues colocamos las caracteristicas de los vertices

	////Posicion
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	//glEnableVertexAttribArray(0);

	////Color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	//glBindVertexArray(0);// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.62f, 0.75f, 0.30f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//PARTES GRISES 
		//cuerpo base de 
		glBindVertexArray(VAO_gray);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 3.0f, 2.0f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//cabeza
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.5f, 1.5f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.2f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 1.0f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Patas 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.5f, 1.5f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// OREJAS		
		// IZQUIERDA
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 2.15f, -0.1f));
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 2.9f, -0.1f));
		model = glm::scale(model, glm::vec3(0.4f, 0.55f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 3.2f, -0.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.25f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// DERECHA
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, 2.15f, -0.1f));
		model = glm::scale(model, glm::vec3(0.2f, 1.0f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, 2.9f, -0.1f));
		model = glm::scale(model, glm::vec3(0.4f, 0.55f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, 3.2f, -0.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.25f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//nariz
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.25f, 1.1f));
		model = glm::scale(model, glm::vec3(0.6f, 0.3f, 0.2f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//pelo del torso
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.9f, 1.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.12f, 0.85f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.12f, 0.85f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.17f, 0.8f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.17f, 0.8f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.55f, 0.8f, 1.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.55f, 0.8f, 1.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.675f, 0.75f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.675f, 0.75f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.44f, 0.75f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.44f, 0.75f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.265f, 0.65f, 1.1f));
		model = glm::scale(model, glm::vec3(0.15f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.265f, 0.65f, 1.1f));
		model = glm::scale(model, glm::vec3(0.15f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.355f, 0.6f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.355f, 0.6f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.17f, 0.6f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.17f, 0.6f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.65f, 0.56f, 1.1f));
		model = glm::scale(model, glm::vec3(0.15f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.65f, 0.56f, 1.1f));
		model = glm::scale(model, glm::vec3(0.15f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.75f, 0.52f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.75f, 0.52f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.55f, 0.52f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.55f, 0.52f, 1.1f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.3f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//PARTES GRISES FUERTE 
		glBindVertexArray(VAO_grayf);
		//brazos
		//IZQUIERDO
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.25f, 0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 2.7f, 1.7f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.35f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 2.0f, 1.0f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.5f, 0.7f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.6f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 0.4f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//DERECHO
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.25f, 0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 2.7f, 1.7f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.35f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 2.0f, 1.0f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.5f, 0.7f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.6f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 0.4f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Cola
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.6f, -1.25f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Patas 
		glBindVertexArray(VAO_gray);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.95f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 0.4f, 1.0f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//PARTES BEIGE
		glBindVertexArray(VAO_beige);
		//torso
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 1.0f));
		model = glm::scale(model, glm::vec3(1.8f, 1.8f, 0.4f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	

		//PARTES BLANCAS

		//ojo izquierdo
		glBindVertexArray(VAO_white);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.6f, 1.6f, 1.0f));
		model = glm::scale(model, glm::vec3(0.55f, 0.45f, 0.2f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//ojo derecho 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.6f, 1.6f, 1.0f));
		model = glm::scale(model, glm::vec3(0.55f, 0.45f, 0.2f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//PARTES NEGRAS 
		glBindVertexArray(VAO_black);
		// PUPILAS
		// IZQUIERDA
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.457f, 1.5f, 1.1f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// DERECHA
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.457f, 1.5f, 1.1f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//nariz
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.4f, 1.15f));
		model = glm::scale(model, glm::vec3(0.4f, 0.08f, 0.2f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, 1.15f));
		model = glm::scale(model, glm::vec3(0.2f, 0.08f, 0.2f));//ancho, grosor, profundidad
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO_gray);
	glDeleteBuffers(1, &VBO_gray);
	glDeleteVertexArrays(1, &VAO_beige);
	glDeleteBuffers(1, &VBO_beige);
	glDeleteVertexArrays(1, &VAO_white);
	glDeleteBuffers(1, &VBO_white);
	glDeleteVertexArrays(1, &VAO_black);
	glDeleteBuffers(1, &VBO_black);
	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.04f;
 }


