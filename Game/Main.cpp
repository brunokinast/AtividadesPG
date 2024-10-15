#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <assert.h>
#include <glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <text/text.h>
#include "Game.cpp"

using namespace glm;

const GLuint WIDTH = 512, HEIGHT = 512;

// Vertex shader source code
const GLchar *vertexShaderSource = "#version 400\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "layout (location = 1) in vec2 texc;\n"
                                   "uniform mat4 projection;\n"
                                   "uniform mat4 model;\n"
                                   "out vec2 texCoord;\n"
                                   "void main()\n"
                                   "{\n"
                                   "gl_Position = projection * model * vec4(position.x, position.y, position.z, 1.0);\n"
                                   "texCoord = vec2(texc.s, 1.0 - texc.t);\n"
                                   "}\0";

// Fragment shader source code
const GLchar *fragmentShaderSource = "#version 400\n"
                                     "in vec2 texCoord;\n"
                                     "uniform sampler2D texBuffer;\n"
                                     "uniform vec2 offsetTex;\n"
                                     "out vec4 color;\n"
                                     "void main()\n"
                                     "{\n"
                                     "color = texture(texBuffer, texCoord + offsetTex);\n"
                                     "}\n\0";

int setupShader();
GLFWwindow *setupGlfw();
void setupView(GLuint shaderID);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void processKeys();

keyInfo keys[1024];

Game *game;

int main()
{
    GLFWwindow *window = setupGlfw();
    GLuint shaderID = setupShader();
    setupView(shaderID);
    init_text_rendering("Textures/freemono.png", "Textures/freemono.meta", WIDTH, HEIGHT);

    game = new Game(WIDTH, HEIGHT);
    
    while (!glfwWindowShouldClose(window))
    {
        processKeys();
        glfwPollEvents();
        game->handleInput(keys);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game->render(shaderID);
        setupView(shaderID);

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

GLFWwindow *setupGlfw()
{
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    const float UPSCALED_WIDTH = WIDTH * 1.5;
    const float UPSCALED_HEIGHT = HEIGHT * 1.5;

    GLFWwindow *window = glfwCreateWindow(UPSCALED_WIDTH, UPSCALED_HEIGHT, "Gaming game! -- Bruno Kinast", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, UPSCALED_WIDTH, UPSCALED_HEIGHT);

    return window;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
        keys[key].pressed = true;
    else if (action == GLFW_RELEASE)
        keys[key].pressed = false;
}

void processKeys()
{
    for (int i = 0; i < 1024; i++)
        keys[i].held = keys[i].pressed;
}

void setupView(GLuint shaderID)
{
    glUseProgram(shaderID);
    glUniform1i(glGetUniformLocation(shaderID, "texBuffer"), 0);

    mat4 projection = ortho(0.0f, static_cast<GLfloat>(WIDTH), static_cast<GLfloat>(HEIGHT), 0.0f, -1.0f, 1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"), 1, GL_FALSE, value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
}

int setupShader()
{
    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Link shaders to create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
