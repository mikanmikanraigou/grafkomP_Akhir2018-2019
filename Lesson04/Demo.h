#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram;
	//texture 1 : Grass
	GLuint texture, VAO, VBO, EBO;
	//texture 2 : Hotel Floor
	GLuint texture2, VAO2, VBO2, EBO2;
	//texture 3 : Carpet
	GLuint texture3, VAO3, VBO3, EBO3;
	//texture 4 : Bed Frame 1
	GLuint texture4, VAO4, VBO4, EBO4;
	//texture 5 : Bed Frame 2
	GLuint texture5, VAO5, VBO5, EBO5;
	//texture 6 : Bed
	GLuint texture6, VAO6, VBO6, EBO6;
	//texture 7 : Wall
	GLuint texture7, VAO7, VBO7, EBO7;
	//texture 8 : Drawer
	GLuint texture8, VAO8, VBO8, EBO8;
	//texture 9 : Lamp
	GLuint texture9, VAO9, VBO9, EBO9;
	//texture 10 : Door
	GLuint texture10, VAO10, VBO10, EBO10;
	//Texure 11 : Window 
	GLuint texture11, VAO11, VBO11, EBO11;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);

	//Grass
	void Buildgrass();
	void Drawgrass();
	//Hotel Floor
	void BuildHotelFloor();
	void DrawHotelFloor();
	//Carpet
	void BuildCarpet();
	void DrawCarpet();
	//Bed
	void BuildBedFrame1();
	void BuildBedFrame2();
	void BuildBed();
	void DrawBedFrame1();
	void DrawBedFrame2();
	void DrawBed();
	//Wall 1
	void BuildWall();
	void DrawWall();
	//Drawer
	void BuildDrawer();
	void DrawDrawer();
	//Lamp
	void BuildLamp();
	void DrawLamp();
	//Door
	void BuildDoor();
	void DrawDoor();
	//Window
	void BuildWindow();
	void DrawWindow();
	
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};

