//Practica 08          Fernanda García Ortega 
// Fecha de entrega:10/04/2026    320301159
// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
glm::vec3 lightPos(0.5f, 0.5f, 2.5f);
glm::vec3 lightPos2(0.5f, 0.5f, 2.5f);

float movelightPos = 0.0f;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool activanim = false;

//Variables de control 
bool esDia = true; 
float tiempo = 0.0f; 
float orbita = 0.0f;

float sunRotation = 0.0f;
float moonRotation = 0.0f;

float anguloOrbita = glm::radians(90.0f);
float velocidadOrbita = 1.0f;
float radio = 25.0f;

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Materiales e Iluminacion Practica 08  Fernanda Garcia Ortega", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");



    // Load models
    Model dog((char*)"Models/RedDog.obj");
    Model table((char*)"Models/coffee_table.obj");
    Model cloud((char*)"Models/Low Poly Clouds.obj");
    Model grass((char*)"Models/grass.obj");
    Model arbour((char*)"Models/Arbour.obj");
    Model tree((char*)"Models/Tree.obj");
    Model hydrant((char*)"Models/hidrant_1.obj");
    Model bench((char*)"Models/PARKTABLE.obj");
    Model frisbee((char*)"Models/10505_Frisbee_v3_L3.obj");
    Model corgi((char*)"Models/Corgi.obj");
    Model play((char*)"Models/Playground_OBJ.obj");
    Model pbench((char*)"Models/Classic_Garden_Bench.obj");
    Model shiba((char*)"Models/Shiba.obj");
    Model gtree((char*)"Models/GenTree_105_AE3D_03122023-F2.obj");
    //Cargando modelos de Sol y Luna 
	Model sun((char*)"Models/P8/13913_Sun_v2_l3.obj");
	Model moon((char*)"Models/P8/Moon.obj");
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);


    // Load textures

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    image = stbi_load("Models/Texture_albedo.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
   
        // SOL
        lightPos.x = radio * cos(anguloOrbita);
        lightPos.y = (radio * sin(anguloOrbita)) * 0.4f + 6.0f;
        lightPos.z = -8.0f;

        // LUNA (misma órbita pero 180° adelante)
        float anguloLuna = anguloOrbita + glm::radians(180.0f);

        lightPos2.x = radio * cos(anguloLuna);
        lightPos2.y = (radio * sin(anguloLuna)) * 0.4f + 6.0f;
        lightPos2.z = -8.0f;

        if (lightPos.y > lightPos2.y)
        {
            esDia = true;   // el sol domina
        }
        else
        {
            esDia = false;  // la luna domina
        }

        sunRotation += 30.0f * deltaTime;
        moonRotation += 20.0f * deltaTime;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        lightingShader.Use();
        glm::mat4 view = camera.GetViewMatrix();
        if (esDia) {
            glClearColor(0.75f, 0.85f, 0.92f, 1.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.4f, 0.35f, 0.2f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 1.0f, 0.9f, 0.6f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 0.95f, 0.7f);
			// Para que no haya luz de la luna durante el día, se apagan sus componentes
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.specular"), 0.0f, 0.0f, 0.0f);
        }
        else {
            glClearColor(0.08f, 0.1f, 0.2f, 1.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.0f, 0.0f, 0.0f);
			// Para que no haya luz del sol durante la noche, se apagan sus componentes
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.ambient"), 0.15f, 0.15f, 0.25f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.diffuse"), 0.6f, 0.7f, 1.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light2.specular"), 0.8f, 0.9f, 1.0f);
        }
        GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
        GLint light2PosLoc = glGetUniformLocation(lightingShader.Program, "light2.position");
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(lightPosLoc, lightPos.x + movelightPos, lightPos.y + movelightPos, lightPos.z + movelightPos);
        glUniform3f(light2PosLoc, lightPos2.x + movelightPos, lightPos2.y + movelightPos, lightPos2.z + movelightPos);
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Set material properties
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

        // Draw the loaded model
        glm::mat4 model(1);
        //Modelo de perro
        model = glm::translate(model, glm::vec3(-8.0f, 0.0f, 7.0f));
        model = glm::rotate(model, glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(lightingShader);
		
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.0f, -0.6f, 5.0f));
        model = glm::scale(model, glm::vec3(0.009f, 0.009f, 0.009f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        corgi.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.7f, -0.5f, -1.0f));
        model = glm::rotate(model, glm::radians(25.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        shiba.Draw(lightingShader);

        //Modelo de mesa 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-5.0f, -0.4f, 6.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        table.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(7.0f, 0.7f, 6.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bench.Draw(lightingShader);

        //Modelo banca 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(8.0f, -0.1f, -5.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pbench.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f, -0.1f, -4.0f));
        model = glm::rotate(model, glm::radians(75.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pbench.Draw(lightingShader);


        

        //Modelo de pasto 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-20.0f, -1.45f, -10.0f));
        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        grass.Draw(lightingShader);

        //Modelo de techo 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.0f, -0.3f, -5.0f));
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        arbour.Draw(lightingShader);

        //Modelo de árboles 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(5.0f, -0.6f, -5.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tree.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-10.0f, -0.7f, -5.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tree.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(10.0f, -0.7f, -5.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tree.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-10.0f, -0.6f, 3.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        gtree.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(12.0f, -0.6f, 3.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        gtree.Draw(lightingShader);

        //Modelo de hidrante 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.0f, 0.2f, 4.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        hydrant.Draw(lightingShader);

        //Modelo de frisbee
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(0.8f, 1.7f, 1.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        frisbee.Draw(lightingShader);


        //Modelo de juegos de parque 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(16.0f, -1.0f, -4.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.8f, 1.8f, 1.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        play.Draw(lightingShader);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        

        shader.Use();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        model = glm::mat4(1.0f);
      
        if (esDia)
        {
			// Escena de día: se muestra el sol y las nubes, pero no la luna
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::rotate(model, glm::radians(sunRotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            sun.Draw(shader);

            //Modelo de nubes 
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(0.0f, 6.0f, -30.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            cloud.Draw(lightingShader);

            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-8.0f, 8.0f, -30.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            cloud.Draw(lightingShader);

            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(8.0f, 8.5f, -30.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            cloud.Draw(lightingShader);

            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-16.0f, 6.0f, -30.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            cloud.Draw(lightingShader);

            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(16.0f, 7.0f, -30.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            cloud.Draw(lightingShader);

            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-24.0f, 8.0f, -30.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            cloud.Draw(lightingShader);
        }
        else
        {
			// Escena de noche: se muestra la luna, pero no el sol ni las nubes
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos2);
            model = glm::rotate(model, glm::radians(moonRotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f ));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            moon.Draw(shader);
        }

        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (activanim)
    {
        if (rot > -90.0f)
            rot -= 0.1f;
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_O])
    {
       
        movelightPos += 0.1f;
    }

    if (keys[GLFW_KEY_L])
    {
        
        movelightPos -= 0.1f;
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) //Dia
    {
        anguloOrbita += glm::radians(3.0f);
    }

    if (key == GLFW_KEY_G && action == GLFW_PRESS) //Noche 
    {
        anguloOrbita -= glm::radians(3.0f);
    }

}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


