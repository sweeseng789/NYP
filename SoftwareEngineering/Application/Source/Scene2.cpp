#include "Scene2.h"
#include "GL\glew.h"
#include "Application.h"

#include "shader.hpp"


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	// Init VBO here
	rotateAngle = 0;
	rotateAngle2 = 0;
	translateX = 0;
	scaleAll = 1;
	randomiser = 0;

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	//Triangle
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat TRIANGLE_vertex[] = {
		0.0f, 1.0f, 0.0f, //vertex 0 of triangle
		1.0f, -1.0f, 0.0f, //vertex 1 of triangle
		-1.0f, -1.0f, 0.0f, //vertex 2 of triangle
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TRIANGLE]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(TRIANGLE_vertex), TRIANGLE_vertex, GL_STATIC_DRAW);

	// An Array of 3 vertors which represents the colors of the 3 vertices
	static const GLfloat TRIANGLE_color[] = {
		0.1f, 0.2f, 0.3f, //color of vertex 0
		0.4f, 0.5f, 0.6f, //color of vertex 1
		-0.4f, 0.8f, 0.9f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TRIANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TRIANGLE_color), TRIANGLE_color, GL_STATIC_DRAW);

	// Star
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat STAR_vertex[] = {
		0.0f, 0.8f, 0.0f, //vertex 0 of triangle
 		0.0f, -0.4f, 0.0f, //vertex 1 of triangle
		0.5f, -0.8f, 0.0f, //vertex 2 of triangle

		0.0f, 0.8f, 0.0f, //vertex 0 of triangle
		0.0f, -0.4f, 0.0f, //vertex 1 of triangle
		-0.5f, -0.8f, 0.0f, //vertex 2 of triangle

		-0.8f, 0.2f, 0.0f, //vertex 0 of triangle
		0.0f, -0.4f, 0.0f, //vertex 1 of triangle
		0.8f, 0.2f, 0.0f, //vertex 2 of triangle
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(STAR_vertex), STAR_vertex, GL_STATIC_DRAW);

	// An Array of 3 vertors which represents the colors of the 3 vertices
	static const GLfloat STAR_color[] = {
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2

		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2

		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(STAR_color), STAR_color, GL_STATIC_DRAW);
	
	// Octagon
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat OCTAGON_vertex[] = {
		0.4f, 0.9f, 0.0f, //vertex of vertex 0
		0.0f, 0.0f, 0.0f, //vertex of vertex 1
		0.9f, 0.4f, 0.0f, //vertex of vertex 2

		0.9f, 0.4f, 0.0f, //vertex of vertex 0
		0.0f, 0.0f, 0.0f, //vertex of vertex 1
		0.9f, -0.4f, 0.0f, //vertex of vertex 2

		0.9f, -0.4f, 0.0f, //vertex of vertex 0
		0.0f, 0.0f, 0.0f, //vertex of vertex 1
		0.4f, -0.9f, 0.0f, //vertex of vertex 2

		0.4f, -0.9f, 0.0f, //vertex of vertex 0
		0.0f, 0.0f, 0.0f, //vertex of vertex 1
		-0.4f, -0.9f, 0.0f, //vertex of vertex 2

		-0.4f, -0.9f, 0.0f, //vertex of vertex 0
		0.0f, 0.0f, 0.0f, //vertex of vertex 1
		-0.9f, -0.4f, 0.0f, //vertex of vertex 2

		-0.9f, -0.4f, 0.0f, //vertex of vertex 0
		0.0f, 0.0f, 0.0f, //vertex of vertex 1
		-0.9f, 0.4f, 0.0f, //vertex of vertex 2

		-0.9f, 0.4f, 0.0f, //vertex of vertex 0
		0.0f, 0.0f, 0.0f, //vertex of vertex 1
		-0.4f, 0.9f, 0.0f, //vertex of vertex 2

		-0.4f, 0.9f, 0.0f, //vertex of vertex 0
		0.0f, 0.0f, 0.0f, //vertex of vertex 1
		0.4f, 0.9f, 0.0f, //vertex of vertex 2
		
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[OCTAGON]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(OCTAGON_vertex), OCTAGON_vertex, GL_STATIC_DRAW);

	// An Array of 3 vertors which represents the colors of the 3 vertices
	static const GLfloat OCTAGON_color[] = {
		0.0f, 1.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 1.0f, 0.0f, //color of vertex 2

		0.0f, 1.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 1.0f, 0.0f, //color of vertex 2

		0.0f, 1.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 1.0f, 0.0f, //color of vertex 2

		0.0f, 1.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 1.0f, 0.0f, //color of vertex 2

		0.0f, 1.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 1.0f, 0.0f, //color of vertex 2

		0.0f, 1.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 1.0f, 0.0f, //color of vertex 2

		0.0f, 1.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 1.0f, 0.0f, //color of vertex 2

		0.0f, 1.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 1.0f, 0.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[OCTAGON]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(OCTAGON_color), OCTAGON_color, GL_STATIC_DRAW);
	
	// Square
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat SQUARE_vertex[] = {
		-0.8f, 0.8f, 0.0f, //vertex 0 of triangle
		0.0f, 0.0f, 0.0f, //vertex 1 of triangle
		0.8f, 0.8f, 0.0f, //vertex 2 of triangle

		0.8f, 0.8f, 0.0f, //vertex 0 of triangle
		0.0f, 0.0f, 0.0f, //vertex 1 of triangle
		0.8f, -0.8f, 0.0f, //vertex 2 of triangle

		0.8f, -0.8f, 0.0f, //vertex 0 of triangle
		0.0f, 0.0f, 0.0f, //vertex 1 of triangle
		-0.8f, -0.8f, 0.0f, //vertex 2 of triangle

		-0.8f, -0.8f, 0.0f, //vertex 0 of triangle
		0.0f, 0.0f, 0.0f, //vertex 1 of triangle
		-0.8f, 0.8f, 0.0f, //vertex 2 of triangle
	};

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE]);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(SQUARE_vertex), SQUARE_vertex, GL_STATIC_DRAW);

	// An Array of 3 vertors which represents the colors of the 3 vertices
	static const GLfloat SQUARE_color[] = {
		0.0f, 0.0f, 1.0f, //color of vertex 0
		0.0f, 0.0f, 1.0f, //color of vertex 1
		0.0f, 0.0f, 1.0f, //color of vertex 2

		0.0f, 0.0f, 1.0f, //color of vertex 0
		0.0f, 0.0f, 1.0f, //color of vertex 1
		0.0f, 0.0f, 1.0f, //color of vertex 2

		0.0f, 0.0f, 1.0f, //color of vertex 0
		0.0f, 0.0f, 1.0f, //color of vertex 1
		0.0f, 0.0f, 1.0f, //color of vertex 2

		0.0f, 0.0f, 1.0f, //color of vertex 0
		0.0f, 0.0f, 1.0f, //color of vertex 1
		0.0f, 0.0f, 1.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SQUARE_color), SQUARE_color, GL_STATIC_DRAW);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );

	//Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	// Use Our shader
	glUseProgram(m_programID);

	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
}

void Scene2::Update(double dt)
{
	if(Application::IsKeyPressed(VK_SPACE))
	{
		rotateAngle += (float)(50 * dt);
		if(rotateAngle >= 0 && rotateAngle <= 180)
		{
			rotateAngle2 = rotateAngle;
		}
		else if(rotateAngle >= 180 && rotateAngle <= 360)
		{
			rotateAngle2 = -rotateAngle;
		}
		else
		{
			rotateAngle = 0;
		}

		
		translateX += (float)(dt) * randomiser;
		if(translateX == 0)
		{
			randomiser = rand() % 100;
		}
		if(translateX >= 90)
		{
			translateX = 0;
			randomiser = rand() % 100;
		}

		scaleAll += (float)(2 * dt);
		if(scaleAll >= 10)
		{
			scaleAll = 0;
		}
	}
}

void Scene2::Render()
{
	// Render VBO here
	// Clear color buffer every frame
	//glClear(GL_COLOR_BUFFER_BIT);
	// Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;
	
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity(); //no need camera for now, set it at
	projection.SetToOrtho(-40, +40, -40, +40, -40, +40); //Our world is a cube defined by these boundaries

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(rotateAngle2, 0, 0, 1);
	translate.SetToTranslation(30, 30, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TRIANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TRIANGLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX - 45, -20, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TRIANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TRIANGLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(30, 5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TRIANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TRIANGLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	//Triangle
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(rotateAngle2, 0, 0, 1);
	translate.SetToTranslation(0, -translateX + 45, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[TRIANGLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[TRIANGLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Star
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(rotateAngle2, 0, 0, 1);
	translate.SetToTranslation(-20, -translateX + 45, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[STAR]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 9);
	
	// Octagon
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(rotateAngle2, 0, 0, 1);
	translate.SetToTranslation(12, -translateX + 45, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[OCTAGON]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[OCTAGON]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 24);

	// Square
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(rotateAngle2, 0, 0, 1);
	translate.SetToTranslation(-10, -translateX + 45, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; // Remember, matrix multiplication is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}