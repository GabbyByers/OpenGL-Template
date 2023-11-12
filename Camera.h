#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include"ShaderTexture.h"

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	bool firstClick = true;
	int screen_width;
	int screen_height;
	float speed = 0.0015f;
	float sensitivity = 100.0f;

	Camera(int width, int height, glm::vec3 position) {
		screen_width = width;
		screen_height = height;
		Position = position;
	}

	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(Position, Position + Orientation, Up);
		projection = glm::perspective(glm::radians(FOVdeg), (float)screen_width / screen_height, nearPlane, farPlane);

		glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
	}

	void Inputs(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			Position += speed * Orientation;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			Position += speed * -glm::normalize(glm::cross(Orientation, Up));
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			Position += speed * -Orientation;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			Position += speed * glm::normalize(glm::cross(Orientation, Up));
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			Position += speed * Up;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			Position += speed * -Up;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			if (firstClick) {
				glfwSetCursorPos(window, (screen_width / 2), (screen_height / 2));
				firstClick = false;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotX = sensitivity * (float)(mouseY - (screen_height / 2)) / screen_height;
			float rotY = sensitivity * (float)(mouseX - (screen_width / 2)) / screen_width;

			glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

			if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
				Orientation = newOrientation;

			Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

			glfwSetCursorPos(window, (screen_width / 2), (screen_height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}
	}
};