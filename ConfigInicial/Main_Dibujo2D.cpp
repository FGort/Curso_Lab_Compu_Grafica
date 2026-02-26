//Garcia Ortega Fernanda   320301159
//Fecha de entrega 20/02/2026    Practica 2
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D - Garcia Ortega Fernanda", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//Primer cuadrante 
		-4.8f/18.0f, 1.0f/18.0f, 0.0f,    1.0f,0.80f,0.78f,//V1 0
		-4.0f/18.0f, 4.8f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V2 1
		-3.0f/18.0f, 3.5f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V3 2
		-1.1f/18.0f, 6.0f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V4 3
		-0.8f/18.0f, 4.3f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V5 4 
		-1.0f/18.0f, 2.4f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V38 5
		-0.4f/18.0f, 1.5f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V39 6
		 0.0f/18.0f, 1.0f/18.0f, 0.0f,    1.0f,0.55f,0.75f,//V40 7
		//Segundo cuadrante 
		2.6f/18.0f, 6.4f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V6 8
		2.2f/18.0f, 4.8f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V7 9
		5.4f/18.0f, 5.4f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V8 10
		4.6f/18.0f, 3.55f/18.0f, 0.0f,   0.80f,0.20f,0.50f,//V9 11
		1.8f/18.0f, 2.5f/18.0f, 0.0f,    1.0f,0.55f,0.75f,//V10 12
		7.75f/18.0f, 3.15f/18.0f, 0.0f,  0.80f,0.20f,0.50f,//V11 13
		5.9f/18.0f, 1.3f/18.0f, 0.0f,    1.0f,0.55f,0.75f,//V12 14 
		8.4f/18.0f, 0.2f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V13 15
		6.0f/18.0f, 0.9f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V43 16
		//Tercer cuadrante
		7.0f/18.0f, -0.9f/18.0f, 0.0f,    1.0f,0.55f,0.75f,//V14 17
		7.2f/18.0f, -1.3f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V15 18
		8.1f/18.0f, -3.0f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V16 19
		4.9f/18.0f, -3.0f/18.0f, 0.0f,    1.0f,0.55f,0.75f,//V17 20
		7.0f/18.0f, -3.0f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V18 21
		6.9f/18.0f, -4.5f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V19 22
		5.9f/18.0f, -4.9f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V20 23 
		5.0f/18.0f, -6.0f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V21 24
		3.0f/18.0f, -6.0f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V22 25
		4.2f/18.0f, -5.3f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V23 26
		2.2f/18.0f, -4.3f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V24 27
		1.0f/18.0f, -6.0f/18.0f, 0.0f,    1.0f,0.80f,0.78f,//V25 28
		2.1f/18.0f, -0.6f/18.0f, 0.0f,    1.0f,0.55f,0.75f,//V42 29
		//Cuarto cuadrante 
		-0.2f/18.0f, -3.9f/18.0f, 0.0f,    1.0f,0.55f,0.75f,//V26 30
		-2.0f/18.0f, -6.0f/18.0f, 0.0f,    1.0f,0.80f,0.78f,//V27 31
		-4.2f/18.0f, -6.0f/18.0f, 0.0f,    1.0f,0.80f,0.78f,//V28 32
		-3.0f/18.0f, -4.5f/18.0f, 0.0f,    1.0f,0.80f,0.78f,//V29 33
		-1.6f/18.0f, -5.5f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V30 34
		-3.6f/18.0f, -4.2f/18.0f, 0.0f,    1.0f,0.80f,0.78f,//V31 35
		-6.7f/18.0f, -3.0f/18.0f, 0.0f,    1.0f,0.40f,0.70f,//V32 36 
		-4.0f/18.0f, -3.0f/18.0f, 0.0f,    1.0f,0.80f,0.78f,//V33 37
		-8.8f/18.0f, -2.0f/18.0f, 0.0f,    1.0f,0.40f,0.70f,//V34 38
		-7.8f/18.0f, -1.7f/18.0f, 0.0f,    1.0f,0.40f,0.70f,//V35 39
		-2.3f/18.0f, -0.4f/18.0f, 0.0f,    1.0f,0.80f,0.78f,//V36 40
		-0.3f/18.0f, -1.8f/18.0f, 0.0f,    0.80f,0.20f,0.50f,//V37 41
		-0.2f/18.0f, -0.2f/18.0f, 0.0f,    1.0f,0.55f,0.75f,//V41 42
		
		//Ojo
		-4.9f/18.0f, -0.9f/18.0f, 0.0f,		0.0f,0.0f,0.0f,//V44 43 
	
	};
	unsigned int indices[] = {  // note that we start from 0!
		/*3,2,1,// second Triangle
		0,1,3,*/
		0,1,2, //triangulo 1
		0,3,4, //triangulo 2
		0,4,5,
		4,8,12,
		4,12,5,
		5,12,6,
		9,10,12,
		10,11,12,
		11,13,14,
		11,14,12,
		14,15,16,
		12,16,29,
		16,18,20,
		18,19,20,
		20,21,22,
		20,22,26,
		23,24,27,
		27,24,25,
		16,20,29,
		29,20,27,
		20,26,27,
		27,26,25,
		27,25,28,
		27,28,30,
		29,27,30,
		29,30,41,
		30,28,31,
		33,34,31,
		30,34,35,
		33,31,32,
		6,12,7,
		7,12,29,
		7,29,42,
		42,29,41,
		41,30,37,
		37,30,35,
		40,41,37,
		7,41,40,
		5,7,40,
		0,5,40,
		0,40,37,
		0,37,39,
		37,35,36,
		39,37,36,
		38,39,36,
		12,14,16,
		17,18,20,
		15,17,16,
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);

        
        //glDrawArrays(GL_LINES,0,2);
        //glDrawArrays(GL_LINE_LOOP,0,4);
        
        //glDrawArrays(GL_TRIANGLES,0,3);
        glDrawElements(GL_TRIANGLES,144,GL_UNSIGNED_INT,0);

		glPointSize(15);
		glDrawArrays(GL_POINTS, 43, 1);
        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}