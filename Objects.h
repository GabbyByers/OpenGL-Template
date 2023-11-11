#pragma once
#include<glad/glad.h>

class VBO {
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;

	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLfloat* vertices, GLsizeiptr size) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	// Binds the VBO
	void Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	// Unbinds the VBO
	void Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Deletes the VBO
	void Delete() {
		glDeleteBuffers(1, &ID);
	}
};

class VAO {
public:
	// ID reference for the Vertex Array Object
	GLuint ID;

	// Constructor that generates a VAO ID
	VAO() {
		glGenVertexArrays(1, &ID);
	}

	// Links a VBO Attribute such as a position or color to the VAO
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
		VBO.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}

	// Binds the VAO
	void Bind() {
		glBindVertexArray(ID);
	}

	// Unbinds the VAO
	void Unbind() {
		glBindVertexArray(0);
	}

	// Deletes the VAO
	void Delete() {
		glDeleteVertexArrays(1, &ID);
	}
};

class EBO {
public:
	// ID reference of Elements Buffer Object
	GLuint ID;

	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	// Binds the EBO
	void Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	// Unbinds the EBO
	void Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// Deletes the EBO
	void Delete() {
		glDeleteBuffers(1, &ID);
	}
};