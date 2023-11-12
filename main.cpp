#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"ShadersTextures.h"
#include"Objects.h"
#include"Camera.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 800;

struct vertex {
	float xPos;
	float yPos;
	float zPos;
	float xTex;
	float yTex;
};

vertex vertices[] = {
	vertex { -0.5f, 0.0f,  0.5f,   0.0f, 0.0f },
	vertex { -0.5f, 0.0f, -0.5f,   1.0f, 0.0f },
	vertex {  0.5f, 0.0f, -0.5f,   0.0f, 0.0f },
	vertex {  0.5f, 0.0f,  0.5f,   1.0f, 0.0f },
	vertex {  0.0f, 0.8f,  0.0f,   0.5f, 1.0f }
};

struct triangle {
	unsigned int i;
	unsigned int j;
	unsigned int k;
};

triangle triangles[] = {
	triangle { 0, 1, 2 },
	triangle { 0, 2, 3 },
	triangle { 0, 1, 4 },
	triangle { 1, 2, 4 },
	triangle { 2, 3, 4 },
	triangle { 3, 0, 4 }
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "YoutubeOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, screen_width, screen_height);

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1((float*)vertices, sizeof(vertices));
	EBO EBO1((unsigned int*)triangles, sizeof(triangles));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Shader shaderProgram("default.vert", "default.frag");
	Texture brickTex("Textures/obama.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_LINE, GL_FILL
	glEnable(GL_DEPTH_TEST);
	glfwSwapInterval(1);

	Camera camera(screen_width, screen_height, glm::vec3(0.0f, 0.0f, 2.0f));
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		brickTex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(triangles) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}