#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/maths.hpp>
#include <common/model.hpp>

// Function prototypes
void keyboardInput(GLFWwindow* window);

int main(void)
{
    // =========================================================================
    // Window creation — lab default
    // -------------------------------------------------------------------------
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1024, 768, "Computer Graphics Coursework", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Load shaders
    GLuint shaderProgram = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");

    // Load model
    Model suzanne("../assets/suzanne.obj");
    suzanne.addTexture("../assets/suzanne_diffuse.png", "diffuse");

    // View and projection
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f),  // camera position
        glm::vec3(0.0f, 0.0f, 0.0f),  // look at center
        glm::vec3(0.0f, 1.0f, 0.0f)   // up
    );

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        1024.0f / 768.0f,
        0.1f, 100.0f
    );

    // =========================================================================
    // Render loop
    // -------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        keyboardInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Transformations
        glm::mat4 translate = Maths::translate(glm::vec3(0.0f, 0.0f, -2.0f));
        glm::mat4 rotate = Maths::rotate(glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 scale = Maths::scale(glm::vec3(1.0f));
        glm::mat4 model = translate * rotate * scale;

        glm::mat4 MVP = projection * view * model;

        // Send MVP matrix to shader
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP[0][0]);

        // Bind texture manually
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, suzanne.textures[0].id); // First texture is "diffuse"
        glUniform1i(glGetUniformLocation(shaderProgram, "diffuseMap"), 0);

        // Draw model
        suzanne.draw(shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void keyboardInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
