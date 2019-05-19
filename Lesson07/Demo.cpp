#include "Demo.h"

Demo::Demo() {

}

Demo::~Demo() {
}

void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("coloredCube.vert", "coloredCube.frag", nullptr);
	shadowmapShader = BuildShader("texturedCube.vert", "texturedCube.frag", nullptr);
	switchShaderProgram();

	Buildgrass();
	BuildHotelFloor();
	BuildWall();
	BuildCarpet();
	BuildBedFrame1();
	BuildBedFrame2();
	BuildBed();
	BuildDrawer();
	BuildLamp();
	BuildDoor();
	BuildWindow();
	BuildTexturedCube();
	BuildTexturedPlane();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &cubeEBO);
	glDeleteVertexArrays(1, &planeVAO);
	glDeleteBuffers(1, &planeVBO);
	glDeleteBuffers(1, &planeEBO);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	int newKeyState = glfwGetKey(window, GLFW_KEY_SPACE);
	if (newKeyState == GLFW_RELEASE && oldKeyState == GLFW_PRESS) {
		toggleTextured = !toggleTextured;
		switchShaderProgram();
	}
	oldKeyState = newKeyState;

}

void Demo::Update(double deltaTime) {
}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->activeProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(3, 4, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	GLint viewLoc = glGetUniformLocation(this->activeProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// set lighting attributes
	GLint lightPosLoc = glGetUniformLocation(this->activeProgram, "lightPos");
	glUniform3f(lightPosLoc, 0, 4, 0);
	GLint viewPosLoc = glGetUniformLocation(this->activeProgram, "viewPos");
	glUniform3f(viewPosLoc, 0, 2, 3);
	GLint lightColorLoc = glGetUniformLocation(this->activeProgram, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	if (toggleTextured) {
		DrawTexturedCube();
		DrawTexturedPlane();
	}
	else {
		Drawgrass();
		//DrawWall();
		DrawHotelFloor();
		DrawCarpet();
		DrawBedFrame1();
		DrawBedFrame2();
		DrawBed();
		DrawDrawer();
		//DrawLamp();
		DrawDoor();
		DrawWindow();
		
	}

	glDisable(GL_DEPTH_TEST);
}

void Demo::switchShaderProgram() {
	this->activeProgram = toggleTextured ? this->shadowmapShader : this->shaderProgram;
	UseShader(this->activeProgram);
}

	//NO TEXTURE
	//BUILD SOMETHING ---
	//BUILD OBJ 1
void Demo::Buildgrass()
{
	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-30.0, 0.0, -30.0,  0.0f,  1.0f,  0.0f,
		 30.0, 0.0, -30.0,  0.0f,  1.0f,  0.0f,
		 30.0, 0.0,  50.0,  0.0f,  1.0f,  0.0f,
		-30.0, 0.0,  50.0,  0.0f,  1.0f,  0.0f,
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}
	//BUILD OBJ 2
void Demo::BuildHotelFloor()
{
	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		0.0, 0.001, 0.0,	 0.0f,  1.0f,  1.0f,
		0.0,  0.001, 3.20,	 0.0f,  1.0f,  1.0f,
		4.20,  0.001, 3.20,	 0.0f,  1.0f,  1.0f,
		4.20, 0.001, 0.0,	 0.0f,  1.0f,  1.0f,
	};

	GLuint indices[] = { 0, 1 ,2, 0, 2, 3 };

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}
	//BUILD OBJ 3
void Demo::BuildCarpet()
{
	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		0.6, 0.002, 0.9,   0.0f,  1.0f,  0.0f,
		2.4, 0.002, 0.9,   0.0f,  1.0f,  0.0f,
		2.4, 0.002, 3.20,  0.0f,  1.0f,  0.0f,
		0.6, 0.002, 3.20,  0.0f,  1.0f,  0.0f,
	};

	GLuint indices[] = { 0, 1, 2, 0, 3, 2 };

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);

	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}
	//BUILD OBJ 4
void Demo::BuildBedFrame1() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// bottom
		0.63, 0.003, 1.130, 0.0f,  1.0f,  0.0f, // 16
		2.3, 0.003, 1.13,	0.0f,  1.0f,  0.0f, // 17
		2.3, 0.003, 3.0,	0.0f,  1.0f,  0.0f, // 18
		0.63, 0.003, 3.0,	0.0f,  1.0f,  0.0f, // 19

		// top
		0.63, 0.4, 1.13,0.0f,  -1.0f,  0.0f, // 20
		2.3, 0.4, 1.13,	0.0f,  -1.0f,  0.0f, // 21
		2.3, 0.4, 3.0,	0.0f,  -1.0f,  0.0f, // 22
		0.63, 0.4, 3.0,	0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7 //BED SIDE 4
	};

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	//BUILD OBJ 5
void Demo::BuildBedFrame2() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// bottom
		0.63, 0.003, 3.0,	0.0f,  -1.0f,  0.0f, // 16
		2.3, 0.003, 3.0,	0.0f,  -1.0f,  0.0f, // 17
		2.3, 0.003, 3.20,	0.0f,  -1.0f,  0.0f, // 18
		0.63, 0.003, 3.20,	0.0f,  -1.0f,  0.0f, // 19

		// top
		0.63, 1, 3.0,	0.0f,  1.0f,  0.0f, // 20
		2.3, 1, 3.0,	0.0f,  1.0f,  0.0f, // 21
		2.3, 1, 3.20,	0.0f,  1.0f,  0.0f, // 22
		0.63, 1, 3.20,	0.0f,  1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7 //BED SIDE 4
	};

	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	//BUILD OBJ 6
void Demo::BuildBed() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// bottom
		0.7, 0.31, 1.2,	0.0f,  -1.0f,  0.0f, // 16
		2.2, 0.31, 1.2, 0.0f,  -1.0f,  0.0f, // 17
		2.2, 0.31, 3.0,	0.0f,  -1.0f,  0.0f, // 18
		0.7, 0.31, 3.0,	0.0f,  -1.0f,  0.0f, // 19

		// top
		0.7, 0.45, 1.2,	0.0f,  1.0f,  0.0f, // 20
		2.2, 0.45, 1.2, 0.0f,  1.0f,  0.0f, // 21
		2.2, 0.45, 3.0,	0.0f,  1.0f,  0.0f, // 22
		0.7, 0.45, 3.0,	0.0f,  1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		//8, 9, 10, 8, 10 ,11, 
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7 //BED SIDE 4
	};

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	//BUILD OBJ 7
void Demo::BuildWall() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords

	// Wall 1
		// bottom
		0, 0.001, -0.20,	0.0f,  -1.0f,  0.0f, // 0
		4.20, 0.001, -0.20, 0.0f,  -1.0f,  0.0f, // 1
		4.20, 0.001, 0,		0.0f,  -1.0f,  0.0f, // 2
		0, 0.001, 0, 0,		0.0f,  -1.0f,  0.0f, // 3
		// top
		0, 2.5, -0.20,		0.0f,  1.0f,  0.0f, // 4
		4.20, 2.5, -0.20,	0.0f,  1.0f,  0.0f, // 5
		4.20, 2.5, 0,		0.0f,  1.0f,  0.0f, // 6
		0, 2.5, 0,			0.0f,  1.0f,  0.0f, // 7

	// Wall 2
		// bottom
		0, 0.001, 3.20,		0.0f,  -1.0f,  0.0f, // 0
		4.20, 0.001, 3.20,	0.0f,  -1.0f,  0.0f, // 1
		4.20, 0.001, 3.45,	0.0f,  -1.0f,  0.0f, // 2
		0, 0.001, 3.45,		0.0f,  -1.0f,  0.0f, // 3
		// top
		0, 2.5, 3.20,		0.0f,  1.0f,  0.0f, // 4
		4.20, 2.5, 3.20,	0.0f,  1.0f,  0.0f, // 5
		4.20, 2.5, 3.45,	0.0f,  1.0f,  0.0f, // 6
		0, 2.5, 3.45,		0.0f,  1.0f,  0.0f, // 7

	// Wall 3
		// bottom
		3, 0.002, 0.90,		0.0f,  -1.0f,  0.0f, // 0
		4.20, 0.002, 0.90,	0.0f,  -1.0f,  0.0f, // 1
		4.20, 0.002, 1,		0.0f,  -1.0f,  0.0f, // 2
		3, 0.002, 1,		0.0f,  -1.0f,  0.0f, // 3
		// top
		3, 2.5, 0.90,		0.0f,  1.0f,  0.0f, // 4
		4.20, 2.5, 0.90,	0.0f,  1.0f,  0.0f, // 5
		4.20, 2.5, 1,		0.0f,  1.0f,  0.0f, // 6
		3, 2.5, 1,			0.0f,  1.0f,  0.0f, // 7

		// Wall 4
		// bottom
		4.1, 0.002, 1,		0.0f,  -1.0f,  0.0f, // 0
		4.2, 0.002, 1,		0.0f,  -1.0f,  0.0f, // 1
		4.2, 0.002, 3.20,	0.0f,  -1.0f,  0.0f, // 2
		4.1, 0.002, 3.20,	0.0f,  -1.0f,  0.0f, // 3
		// top
		4.1, 2.5, 1,		0.0f,  1.0f,  0.0f, // 4
		4.2, 2.5, 1,		0.0f,  1.0f,  0.0f, // 5
		4.2, 2.5, 3.20,		0.0f,  1.0f,  0.0f, // 6
		4.1, 2.5, 3.20,		0.0f,  1.0f,  0.0f, // 7

		// Wall 5
		// bottom
		0, 0.002, 0,		0.0f,  -1.0f,  0.0f, // 0
		0.2, 0.002, 0,		0.0f,  -1.0f,  0.0f, // 1
		0.2, 0.002, 3.20,	0.0f,  -1.0f,  0.0f, // 2
		0, 0.002, 3.20,		0.0f,  -1.0f,  0.0f, // 3
		// top
		0, 0.9, 0,			0.0f,  1.0f,  0.0f, // 4
		0.2, 0.9, 0,		0.0f,  1.0f,  0.0f, // 5
		0.2, 0.9, 3.20,		0.0f,  1.0f,  0.0f, // 6
		0, 0.9, 3.20,		0.0f,  1.0f,  0.0f, // 7

		// Wall 6
		// bottom
		3, 0.002, 1.7,		0.0f,  -1.0f,  0.0f, // 0
		3.1, 0.002, 1.7,	0.0f,  -1.0f,  0.0f, // 1
		3.1, 0.002, 3.20,	0.0f,  -1.0f,  0.0f, // 2
		3, 0.002, 3.20,		0.0f,  -1.0f,  0.0f, // 3
		// top
		3, 2.5, 1.7,		0.0f,  1.0f,  0.0f, // 4
		3.1, 2.5, 1.7,		0.0f,  1.0f,  0.0f, // 5
		3.1, 2.5, 3.20,		0.0f,  1.0f,  0.0f, // 6
		3, 2.5, 3.20,		0.0f,  1.0f,  0.0f, // 7

		// Wall 7
		// bottom
		0, 1.8, 0,			0.0f,  -1.0f,  0.0f, // 0
		0.2, 1.8, 0,		0.0f,  -1.0f,  0.0f, // 1
		0.2, 1.8, 3.20,		0.0f,  -1.0f,  0.0f, // 2
		0, 1.8, 3.20,		0.0f,  -1.0f,  0.0f, // 3
		// top
		0, 2.5, 0,			0.0f,  1.0f,  0.0f, // 4
		0.2, 2.5, 0,		0.0f,  1.0f,  0.0f, // 5
		0.2, 2.5, 3.20,		0.0f,  1.0f,  0.0f, // 6
		0, 2.5, 3.20,		0.0f,  1.0f,  0.0f, // 7

		// Wall 8
		// bottom
		4.0 , 2.0, 0,		0.0f,  -1.0f,  0.0f, // 0
		4.20, 2.0, 0,		0.0f,  -1.0f,  0.0f, // 1
		4.20, 2.0, 1,		0.0f,  -1.0f,  0.0f, // 2
		4.0, 2.0, 1,		0.0f,  -1.0f,  0.0f, // 3
		// top
		4.0 , 2.5, 0,		0.0f,  1.0f,  0.0f, // 4
		4.20, 2.5, 0,		0.0f,  1.0f,  0.0f, // 5
		4.20, 2.5, 1,		0.0f,  1.0f,  0.0f, // 6
		4.0, 2.5, 1,		0.0f,  1.0f,  0.0f, // 7

		// Wall 9
		// bottom
		3, 2, 1,			0.0f,  -1.0f,  0.0f, // 0
		3.1, 2, 1,			0.0f,  -1.0f,  0.0f, // 1
		3.1, 2, 1.7,		0.0f,  -1.0f,  0.0f, // 2
		3, 2, 1.7,			0.0f,  -1.0f,  0.0f, // 3
		// top
		3, 2.5, 1,			0.0f,  1.0f,  0.0f, // 4
		3.1, 2.5, 1,		0.0f,  1.0f,  0.0f, // 5
		3.1, 2.5, 1.7,		0.0f,  1.0f,  0.0f, // 6
		3, 2.5, 1.7,		0.0f,  1.0f,  0.0f, // 7
	};

	unsigned int indices[] = {
		//WALL 1
		0, 1, 2, 0, 2, 3, //BOTTOM
		4, 5, 6, 4, 6, 7, //TOP
		0, 1, 5, 0, 5, 4, //SIDE 1
		3, 0, 4, 3, 4, 7, //SIDE 2
		1, 2, 6, 1, 6, 5, //SIDE 3
		3, 2, 6, 3, 6, 7, //SIDE 4

		////WALL 2
		//8, 9, 10, 8, 10, 11,
		//12, 13, 14, 12, 14, 15,
		//8, 9, 13, 8, 13, 12,
		//9, 10, 14, 9, 14, 13,
		//10, 11, 15, 10, 15, 14,
		//11, 8, 12, 11, 12, 15,

		////Wall 3
		//16, 17, 18, 16, 18, 19,

		//20, 21, 22, 20, 22, 23,
		//19, 16, 20, 19, 20, 23,
		//16, 17, 21, 16, 21, 20,
		//17, 18, 22, 17, 22, 21,
		//18, 19, 23, 18, 23, 22,

		////Wall 4
		//24, 25, 26, 24, 26, 27,
		//28, 29, 30, 28, 30, 31,
		//25, 26, 30, 25, 30, 29,
		//27, 24, 28, 27, 28, 31,

		////Wall 5
		//32, 33, 34, 32, 34, 35,
		//36, 37, 38, 36, 38, 39,
		//33, 34, 38, 33, 38, 37,
		//35, 32, 36, 35, 36, 39,

		////Wall 6
		//40, 41, 42, 40, 42, 43,
		//44, 45, 46, 45, 46, 47,
		//40, 41, 45, 40, 45, 44,
		//41, 42, 46, 41, 46, 45,
		//43, 40, 44, 43, 44, 47,

		////Wall 7
		//48, 49, 50, 48, 50, 51,
		//52, 53, 54, 52, 54, 55,
		//49, 50, 54, 49, 54, 53,
		//48, 51, 55, 48, 55, 52,

		////Wall 8 //56 - 63
		//56, 57, 58, 56, 58, 59,
		//60, 61, 62, 60, 62, 63,
		//57, 58, 62, 57, 62, 61,
		//56, 59, 63, 56, 63, 60,

		////Wall 90 //64 - 71
		//64, 65, 66, 64, 66, 67,
		//68, 69, 70, 68, 70, 71,
		//65, 66, 70, 65, 70, 69,
		//64, 67, 71, 64, 71, 68,
	};

	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO7);

	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	//BUILD OBJ 8
void Demo::BuildDrawer() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		//Meja di sebelah kiri sebelah kamar mandi
		// bottom
		2.3, 0.003, 2.5,	0.0f,  -1.0f,  0.0f, // 0
		3,   0.003, 2.5,	0.0f,  -1.0f,  0.0f, // 1
		3,   0.003, 3.2,	0.0f,  -1.0f,  0.0f, // 2
		2.3, 0.003, 3.2,	0.0f,  -1.0f,  0.0f, // 3

		// top
		2.3, 0.5, 2.5,	0.0f,  1.0f,  0.0f, // 4
		3,   0.5, 2.5,	0.0f,  1.0f,  0.0f, // 5
		3,   0.5, 3.2,	0.0f,  1.0f,  0.0f, // 6
		2.3, 0.5, 3.2,	0.0f,  1.0f,  0.0f, // 7

		//Meja di sebelah kanan sebelah kasur
		// bottom
		0.2,      0.003, 2.5,	0.0f,  -1.0f,  0.0f, // 8
		0.63,   0.003,	 2.5,	0.0f,  -1.0f,  0.0f, // 9
		0.63,   0.003,	 3.2,	0.0f,  -1.0f,  0.0f, // 10
		0.2,      0.003, 3.2,	0.0f,  -1.0f,  0.0f, // 11

		// top
		0.2,      0.5,	 2.5,	 0.0f,  1.0f,  0.0f, // 12
		0.63,   0.5,	 2.5,	 0.0f,  1.0f,  0.0f, // 13
		0.63,   0.5,	3.2,	 0.0f,  1.0f,  0.0f, // 14
		0.2,      0.5,	 3.2,	 0.0f,  1.0f,  0.0f, // 15
	};

	unsigned int indices[] = {
			0, 1, 2, 0, 2, 3,  //bottom 1
			4, 5, 6, 4, 6 ,7,
			0, 1, 5, 0, 5, 4,
			3, 0, 4, 3, 4, 7,

			8, 9, 10, 8, 10, 11,//Bottom 2
			12, 13, 14, 12, 14, 15,
			8, 9, 13, 8, 13, 12,
			9, 10, 14, 9, 14, 13,
	};

	glGenVertexArrays(1, &VAO8);
	glGenBuffers(1, &VBO8);
	glGenBuffers(1, &EBO8);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO8);

	glBindBuffer(GL_ARRAY_BUFFER, VBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	//BUILD OBJ 9
void Demo::BuildLamp() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// bottom
		0.63,   2.25, 1,   0.0f,  -1.0f,  0.0f, // 16
		2.3,    2.25, 1,   0.0f,  -1.0f,  0.0f, // 17
		2.3,    2.25, 1.8, 0.0f,  -1.0f,  0.0f, // 18
		0.63,   2.25, 1.8, 0.0f,  -1.0f,  0.0f, // 19

		// top
		0.63,   2.3, 1,		1.0f,  0.0f, // 20
		2.3,    2.3, 1,		1.0f,  0.0f, // 21
		2.3,    2.3, 1.8,	1.0f,  0.0f, // 22
		0.63,   2.3, 1.8,	1.0f,  0.0f, // 23


		// bottom
		3.3,   2.25, 1.6,	0.0f,  -1.0f,  0.0f, // 16
		3.7,    2.25, 1.6,	0.0f,  -1.0f,  0.0f, // 17
		3.7,    2.25, 2.7,	0.0f,  -1.0f,  0.0f, // 18
		3.3,   2.25, 2.7,	0.0f,  -1.0f,  0.0f, // 19

		// top
		3.3,   2.3, 1.6,	0.0f,  1.0f,  0.0f, // 20
		3.7,    2.3, 1.6,	0.0f,  1.0f,  0.0f, // 21
		3.7,    2.3, 2.7,	0.0f,  1.0f,  0.0f, // 22
		3.3,   2.3, 2.7,	0.0f,  1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7, //BED SIDE 4

		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		8, 9, 13, 8, 13, 12,
		11, 10, 14, 11, 14, 15,
		10, 9, 13, 10, 13, 14,
		8, 11, 15, 8, 15, 12,
	};

	glGenVertexArrays(1, &VAO9);
	glGenBuffers(1, &VBO9);
	glGenBuffers(1, &EBO9);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO9);

	glBindBuffer(GL_ARRAY_BUFFER, VBO9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO9);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	//BUILD OBJ 10
void Demo::BuildDoor() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex 
		//Door 1
		// bottom
		3.3,   0.002,	0,		0.0f,  -1.0f,  0.0f, // 16
		4.20,    0.002, 0,		0.0f,  -1.0f,  0.0f, // 17
		4.20,    0.002, 0.05,	0.0f,  -1.0f,  0.0f, // 18
		3.3,   0.002,	0.05,	0.0f,  -1.0f,  0.0f, // 19

		// top
		3.3,   2, 0,		0.0f,  1.0f,  0.0f, // 20
		4.20,    2, 0,		0.0f,  1.0f,  0.0f, // 21
		4.20,    2, 0.05,	0.0f,  1.0f,  0.0f, // 22
		3.3,   2, 0.05,		0.0f,  1.0f,  0.0f, // 23

		//Door 2
		// bottom
		3.1001,   0.003, 1.4,	0.0f,  -1.0f,  0.0f, // 1
		3.05,    0.003, 1.4,	0.0f,  -1.0f,  0.0f, // 1
		3.05,    0.003, 2.3,	0.0f,  -1.0f,  0.0f, // 1
		3.1001,   0.003, 2.3,	0.0f,  -1.0f,  0.0f, // 1

		// top
		3.1001,   2, 1.4,		0.0f,  1.0f,  0.0f, // 20
		3.05,    2, 1.4,		0.0f,  1.0f,  0.0f, // 21
		3.05,    2, 2.3,		0.0f,  1.0f,  0.0f, // 22
		3.1001,   2, 2.3,		0.0f,  1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7, //BED SIDE 4

		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		8, 9, 13, 8, 13, 12,
		11, 10, 14, 11, 14, 15,
		10, 9, 13, 10, 13, 14,
		8, 11, 15, 8, 15, 12,

	};

	glGenVertexArrays(1, &VAO10);
	glGenBuffers(1, &VBO10);
	glGenBuffers(1, &EBO10);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO10);

	glBindBuffer(GL_ARRAY_BUFFER, VBO10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO10);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	//BUILD OBJ 11
void Demo::BuildWindow() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// bottom
		0.05, 0.9, 0,	 0.0f,  -1.0f,  0.0f, // 16
		0.05, 1.8, 0,	 0.0f,  -1.0f,  0.0f, // 17
		0.05, 1.8, 3.20, 0.0f,  -1.0f,  0.0f, // 18
		0.05, 0.9, 3.20, 0.0f,  -1.0f,  0.0f, // 19

	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3,
	};

	glGenVertexArrays(1, &VAO11);
	glGenBuffers(1, &VBO11);
	glGenBuffers(1, &EBO11);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO11);

	glBindBuffer(GL_ARRAY_BUFFER, VBO11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO11);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	
	//DRAW SOMETHING--
	//DRAW OBJ 1
void Demo::Drawgrass()
{
	UseShader(activeProgram);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (yellow plastic)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0f, 0.0f, 0.0f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.5f, 0.5f, 0.0f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.60f, 0.60f, 0.50f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 2
void Demo::DrawHotelFloor()
{
	UseShader(activeProgram);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (yellow plastic)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0f, 0.0f, 0.0f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.5f, 0.5f, 0.0f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.60f, 0.60f, 0.50f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 3
void Demo::DrawCarpet()
{
	UseShader(activeProgram);

	glBindVertexArray(VAO3); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (yellow plastic)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0f, 0.0f, 0.0f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.5f, 0.5f, 0.0f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.60f, 0.60f, 0.50f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 4
void Demo::DrawBedFrame1()
{
	UseShader(this->activeProgram);

	glBindVertexArray(VAO4); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (Emerald)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0215f, 0.1745f, 0.0215f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.07568f, 0.61424f, 0.07568f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.633f, 0.727811f, 0.633f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.6f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 5
void Demo::DrawBedFrame2()
{
	UseShader(this->activeProgram);

	glBindVertexArray(VAO5); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (Emerald)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0215f, 0.1745f, 0.0215f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.07568f, 0.61424f, 0.07568f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.633f, 0.727811f, 0.633f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.6f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 6
void Demo::DrawBed()
{
	UseShader(this->activeProgram);

	glBindVertexArray(VAO6); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (Emerald)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0215f, 0.1745f, 0.0215f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.07568f, 0.61424f, 0.07568f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.633f, 0.727811f, 0.633f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.6f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 7
void Demo::DrawWall()
{
	UseShader(this->activeProgram);

	glBindVertexArray(VAO7); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (Emerald)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0215f, 0.1745f, 0.0215f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.07568f, 0.61424f, 0.07568f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.633f, 0.727811f, 0.633f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.6f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 230, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 8
void Demo::DrawDrawer()
{
	UseShader(this->activeProgram);

	glBindVertexArray(VAO8); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (Emerald)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0215f, 0.1745f, 0.0215f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.07568f, 0.61424f, 0.07568f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.633f, 0.727811f, 0.633f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.6f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 50, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 9
void Demo::DrawLamp()
{
	UseShader(this->activeProgram);

	glBindVertexArray(VAO9); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (Emerald)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0215f, 0.1745f, 0.0215f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.07568f, 0.61424f, 0.07568f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.633f, 0.727811f, 0.633f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.6f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 10
void Demo::DrawDoor()
{
	UseShader(this->activeProgram);

	glBindVertexArray(VAO10); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (Emerald)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0215f, 0.1745f, 0.0215f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.07568f, 0.61424f, 0.07568f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.633f, 0.727811f, 0.633f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.6f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
	//DRAW OBJ 11
void Demo::DrawWindow()
{
	UseShader(this->activeProgram);

	glBindVertexArray(VAO11); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// set lighting materials attributes (Emerald)
	GLint ambientMatLoc = glGetUniformLocation(this->activeProgram, "material.ambient");
	glUniform3f(ambientMatLoc, 0.0215f, 0.1745f, 0.0215f);
	GLint diffuseMatLoc = glGetUniformLocation(this->activeProgram, "material.diffuse");
	glUniform3f(diffuseMatLoc, 0.07568f, 0.61424f, 0.07568f);
	GLint specularMatLoc = glGetUniformLocation(this->activeProgram, "material.specular");
	glUniform3f(specularMatLoc, 0.633f, 0.727811f, 0.633f);
	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.6f);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}



	//WITH TEXTURE
	//Build obj 1
void Demo::Buildgrass()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/grass.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/grass.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// grass outside
		-30.0, 0.0, -30.0,  0,  0, //0
		 30.0, 0.0, -30.0, 30,  0, //1
		 30.0, 0.0,  50.0, 30, 30, //2
		-30.0, 0.0,  50.0,  0, 30, //3	
	};

	GLuint indices[] = 
	{
		0, 1, 2, 0, 2, 3, // grass land
	
	};

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glGenBuffers(1, &cubeEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//build obj 2
void Demo::BuildHotelFloor()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture2);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/floortex.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/floortex_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		// hotel floor vert
		0.0, 0.001, 0.0,		0, 0,  // 0
		0.0,  0.001, 3.20,		 1, 0, //1
		4.20,  0.001, 3.20,		1, 1, //2
		4.20, 0.001, 0.0,		0, 1,   // 3
	};

	unsigned int indices[] = {
		//hotel floor indcies
		0, 1 ,2, 0, 2, 3
	};

	glGenVertexArrays(1, &cubeVAO2);
	glGenBuffers(1, &cubeVBO2);
	glGenBuffers(1, &cubeEBO2);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO2);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//build obj 3
void Demo::BuildCarpet()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture3);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/carpet.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/carpet_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		//Carpet Bottom
		0.6, 0.002, 0.9, 0, 0, //0
		2.4, 0.002, 0.9, 0, 1, //1
		2.4, 0.002, 3.20, 1, 1, //2
		0.6, 0.002, 3.20, 1, 0, //3
	};

	unsigned int indices[] = {
		//Carpet
		0, 1, 2, 0, 3, 2, //bottom
	};

	glGenVertexArrays(1, &cubeVAO3);
	glGenBuffers(1, &cubeVBO3);
	glGenBuffers(1, &cubeEBO3);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO3);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//build obj 4
void Demo::BuildBedFrame1()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture4);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/darkwood.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/darkwood_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		//BED BOTTOM
		0.63, 0.003, 1.13,		 0, 0, //0
		2.3, 0.003, 1.13,		1, 0, //1
		2.3, 0.003, 3.0,		 1, 1, //2
		0.63, 0.003, 3.0,		0, 1, //3

		//BED TOP
		0.63, 0.4, 1.13,	 1, 1, //4
		2.3, 0.4, 1.13,		0, 1, //5
		2.3, 0.4, 3.0,		 0, 0, //6
		0.63, 0.4, 3.0,		 1, 0, //7
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7 //BED SIDE 4
	};

	glGenVertexArrays(1, &cubeVAO4);
	glGenBuffers(1, &cubeVBO4);
	glGenBuffers(1, &cubeEBO4);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO4);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//build obj 5
void Demo::BuildBedFrame2()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture5);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/darkwood.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/darkwood_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		//BED BOTTOM
		0.63, 0.003, 3.0, 0, 0,
		2.3, 0.003, 3.0, 1, 0,
		2.3, 0.003, 3.20, 1, 1,
		0.63, 0.003, 3.20, 0, 1,

		//BED TOP
		0.63, 1, 3.0,	1, 1,
		2.3, 1, 3.0,	0, 1,
		2.3, 1, 3.20,	0, 0,
		0.63, 1, 3.20,	1, 0,
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7 //BED SIDE 4
	};

	glGenVertexArrays(1, &cubeVAO5);
	glGenBuffers(1, &cubeVBO5);
	glGenBuffers(1, &cubeEBO5);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO5);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//build obj 6
void Demo::BuildBed()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture6);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/bed.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/bed_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		//BED BOTTOM
		0.7, 0.31, 1.2, 0, 0, //4 
		2.2, 0.31, 1.2, 1, 0, //5
		2.2, 0.31, 3.0, 1, 1, //6
		0.7, 0.31, 3.0, 0, 1, //7

		//BED TOP
		0.7, 0.45, 1.2, 1, 1, //4 
		2.2, 0.45, 1.2, 0, 1, //5
		2.2, 0.45, 3.0, 0, 0, //6
		0.7, 0.45, 3.0, 1, 0 //7

	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		//8, 9, 10, 8, 10 ,11, 
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7 //BED SIDE 4
	};

	glGenVertexArrays(1, &cubeVAO6);
	glGenBuffers(1, &cubeVBO6);
	glGenBuffers(1, &cubeEBO6);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO6);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//build obj 7
void Demo::BuildWall()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture7);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/darkwood.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/darkwood_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		//Wall 1
		0, 0.001, -0.20,	0, 0, //0
		4.20, 0.001, -0.20, 3, 0, //1
		4.20, 0.001, 0,		3, 3, //2
		0, 0.001, 0, 0,		3, 0  //3

		0, 2.5, -0.20,		3, 3, //4
		4.20, 2.5, -0.20,	0, 3, //5
		4.20, 2.5, 0,		0, 0, //6
		0, 2.5, 0,			3, 0, //7
		
		//Wall 2
		0, 0.001, 3.20,		0, 0, //8
		4.20, 0.001, 3.20,	3, 0, //9
		4.20, 0.001, 3.45,	3, 3, //10
		0, 0.001, 3.45,		0, 3, //11

		0, 2.5, 3.20,		3, 3, //12
		4.20, 2.5, 3.20,	0, 3, //13
		4.20, 2.5, 3.45,	0, 0, //14
		0, 2.5, 3.45,		3, 0, //15

		//Wall 3 
		3, 0.002, 0.90,		0, 0, //16
		4.20, 0.002, 0.90,	3, 0, //17
		4.20, 0.002, 1,		3, 3, //18
		3, 0.002, 1,		0, 3, //19

		3, 2.5, 0.90,		3, 3, //20
		4.20, 2.5, 0.90,	0, 3, //21
		4.20, 2.5, 1,		0, 0, //22
		3, 2.5, 1,			3, 0, //23

		//Wall 4
		4.1, 0.002, 1,		0, 0, //24
		4.2, 0.002, 1,		3, 0, //25
		4.2, 0.002, 3.20,	3, 3, //26
		4.1, 0.002, 3.20,	0, 3, //27

		4.1, 2.5, 1,		3, 3, //28
		4.2, 2.5, 1,		0, 3, //29
		4.2, 2.5, 3.20,		0, 0, //30
		4.1, 2.5, 3.20,		3, 0, //31

		//Wall 5
		0, 0.002, 0,		0, 0, //32
		0.2, 0.002, 0,		3, 0, //33
		0.2, 0.002, 3.20,	3, 3, //34
		0, 0.002, 3.20,		0, 3, //35

		0, 0.9, 0,			3, 3, //36
		0.2, 0.9, 0,		0, 3, //37
		0.2, 0.9, 3.20,		0, 0, //38
		0, 0.9, 3.20,		3, 0, //39

		//Wall 6
		3, 0.002, 1.7,		0, 0, //40
		3.1, 0.002, 1.7,	3, 0, //41
		3.1, 0.002, 3.20,	3, 3, //42
		3, 0.002, 3.20,		0, 3, //43

		3, 2.5, 1.7,		3, 3, //44
		3.1, 2.5, 1.7,		0, 3, //45
		3.1, 2.5, 3.20,		0, 0, //46
		3, 2.5, 3.20,		3, 0, //47

		//Wall 7
		0, 1.8, 0,			0, 0, //48
		0.2, 1.8, 0,		3, 0, //49
		0.2, 1.8, 3.20,		3, 3, //50
		0, 1.8, 3.20,		0, 3, //51

		0, 2.5, 0,			3, 3, //52
		0.2, 2.5, 0,		0, 3, //53
		0.2, 2.5, 3.20,		0, 0, //54
		0, 2.5, 3.20,		3, 0, //55

		//Wall 8
		4.0 , 2.0, 0,		0, 0, //56
		4.20, 2.0, 0,		3, 0, //57
		4.20, 2.0, 1,		3, 3, //58
		4.0, 2.0, 1,		0, 3, //59

		4.0 , 2.5, 0,		3, 3, //60
		4.20, 2.5, 0,		0, 3, //61
		4.20, 2.5, 1,		0, 0, //62
		4.0, 2.5, 1,		3, 0, //63

		//Wall 9
		3, 2, 1,			0, 0, //64
		3.1, 2, 1,			3, 0, //65
		3.1, 2, 1.7,		3, 3, //66
		3, 2, 1.7,			0, 3, //67

		3, 2.5, 1,			3, 3, //68
		3.1, 2.5, 1,		0, 3, //69
		3.1, 2.5, 1.7,		0, 0, //70
		3, 2.5, 1.7,		3, 0, //71

	};

	unsigned int indices[] = {
		//WALL 1
		0, 1, 2, 0, 2, 3, //BOTTOM
		4, 5, 6, 4, 6, 7, //TOP
		0, 1, 5, 0, 5, 4, //SIDE 1
		3, 0, 4, 3, 4, 7, //SIDE 2
		1, 2, 6, 1, 6, 5, //SIDE 3
		3, 2, 6, 3, 6, 7, //SIDE 4

		//WALL 2
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		8, 9, 13, 8, 13, 12,
		9, 10, 14, 9, 14, 13,
		10, 11, 15, 10, 15, 14,
		11, 8, 12, 11, 12, 15,

		//Wall 3
		16, 17, 18, 16, 18, 19,

		20, 21, 22, 20, 22, 23,
		19, 16, 20, 19, 20, 23,
		16, 17, 21, 16, 21, 20,
		17, 18, 22, 17, 22, 21,
		18, 19, 23, 18, 23, 22, 
		
		//Wall 4
		24, 25, 26, 24, 26, 27, 
		28, 29, 30, 28, 30, 31,
		25, 26, 30, 25, 30, 29,
		27, 24, 28, 27, 28, 31,

		//Wall 5
		32, 33, 34, 32, 34, 35,
		36, 37, 38, 36, 38, 39,
		33, 34, 38, 33, 38, 37,
		35, 32, 36, 35, 36, 39,

		//Wall 6
		40, 41, 42, 40, 42, 43,
		44, 45, 46, 45, 46, 47,
		40, 41, 45, 40, 45, 44,
		41, 42, 46, 41, 46, 45,
		43, 40, 44, 43, 44, 47,

		//Wall 7
		48, 49, 50, 48, 50, 51,
		52, 53, 54, 52, 54, 55,
		49, 50, 54, 49, 54, 53,
		48, 51, 55, 48, 55, 52,

		//Wall 8 //56 - 63
		56, 57, 58, 56, 58, 59,
		60, 61, 62, 60, 62, 63,
		57, 58, 62, 57, 62, 61,
		56, 59, 63, 56, 63, 60,

		//Wall 90 //64 - 71
		64, 65, 66, 64, 66, 67,
		68, 69, 70, 68, 70, 71,
		65, 66, 70, 65, 70, 69,
		64, 67, 71, 64, 71, 68,
	};

	glGenVertexArrays(1, &cubeVAO7);
	glGenBuffers(1, &cubeVBO7);
	glGenBuffers(1, &cubeEBO7);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO7);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//build obj 8
void Demo::BuildDrawer()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture8);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/drawer.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/drawer_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		//meja di sebelah kiri kasur hotel yang besar
		2.3, 0.003, 2.5, 0, 0,   //0
		3,   0.003, 2.5, 1, 0,   //1
		3,   0.003, 3.2, 1, 0.5,   //2
		2.3, 0.003, 3.2, 0, 0.5,   //3

		2.3, 0.5, 2.5, 0, 0,   //4
		3,   0.5, 2.5, 1, 0,   //5
		3,   0.5, 3.2, 1, 0.5,   //6
		2.3, 0.5, 3.2, 0, 0.5,   //7

		//meja di sebelah kanan kasur hotel yang besar
		0.2,      0.003, 2.5,0,0,   //8
		0.63,   0.003,	 2.5,1,0,   //9
		0.63,   0.003,	 3.2,1,0.5,   //10
		0.2,      0.003, 3.2,0,0.5,   //11

		0.2,      0.5,	 2.5,	0,0,   //12
		0.63,   0.5,	 2.5,	1,0,   //13
		0.63,   0.5,	3.2,	1,0.5,   //14
		0.2,      0.5,	 3.2,	0,0.5,   //15

		//face drawer 1
		2.3, 0.003, 2.5, 0, 0.5,   //16
		3,   0.003, 2.5, 0.5, 0.5,   //17
		3,   0.5, 2.5,	 1, 1,   //18
		2.3, 0.5, 2.5,	 0, 1,   //19

		//face drawer 2
		0.2,      0.003, 2.5, 0, 0.5,   //20
		0.63,   0.003, 2.5,	  0.5, 0.5,   //21
		0.63,   0.5, 2.5,	  1, 1,   //22
		0.2,      0.5, 2.5, 0, 1,   //23
	};

	unsigned int indices[] = {
		//Carpet
			0, 1, 2, 0, 2, 3,  //bottom 1
			4, 5, 6, 4, 6 ,7,
			//0, 1, 5, 0, 5, 4,
			3, 0, 4, 3, 4, 7,

			8, 9, 10, 8, 10, 11,//Bottom 2
			12, 13, 14, 12, 14, 15,
			//8, 9, 13, 8, 13, 12,
			9, 10, 14, 9, 14, 13,

			16, 18, 17, 16, 19, 18, //face1
			20, 22, 21, 20, 23, 22,
	};

	glGenVertexArrays(1, &cubeVAO8);
	glGenBuffers(1, &cubeVBO8);
	glGenBuffers(1, &cubeEBO8);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO8);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO8);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//build obj 9
void Demo::BuildLamp()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture9);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/body.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/body_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		//lamp
		0.63,   2.25, 1,   0, 0,    //0
		2.3,    2.25, 1,   1, 0,   //1
		2.3,    2.25, 1.8, 1, 1, //2
		0.63,   2.25, 1.8, 0, 1, //3

		0.63,   2.3, 1,		1, 1,    //4
		2.3,    2.3, 1,		0, 1,   //5
		2.3,    2.3, 1.8,	0, 0, //6
		0.63,   2.3, 1.8,	1, 0, //7

		3.3,   2.25, 1.6,	0, 0,    //8
		3.7,    2.25, 1.6,	1, 0,   //9
		3.7,    2.25, 2.7,	1, 1, //10
		3.3,   2.25, 2.7,	0, 1, //11

		3.3,   2.3, 1.6,	1, 1,    //12
		3.7,    2.3, 1.6,	0, 1,   //13
		3.7,    2.3, 2.7,	0, 0, //14
		3.3,   2.3, 2.7,	1, 0, //15
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7, //BED SIDE 4

		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		8, 9, 13, 8, 13, 12,
		11, 10, 14, 11, 14, 15,
		10, 9, 13, 10, 13, 14,
		8, 11, 15, 8, 15, 12,
	};

	glGenVertexArrays(1, &cubeVAO9);
	glGenBuffers(1, &cubeVBO9);
	glGenBuffers(1, &cubeEBO9);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO9);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO9);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//build obj 10
void Demo::BuildDoor()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture10);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/darkwood.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/darkwood_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		3.3,   0.002,	0,		0, 0,    //0
		4.20,    0.002, 0,		1, 0,   //1
		4.20,    0.002, 0.05,	1, 1, //2
		3.3,   0.002,	0.05,	0, 1, //3

		3.3,   2, 0,		1, 1,    //0
		4.20,    2, 0,		0, 1,   //1
		4.20,    2, 0.05,	0, 0, //2
		3.3,   2, 0.05,		1, 0, //3

		3.1001,   0.003, 1.4,	1, 1,    //8
		3.05,    0.003, 1.4,	0, 1,   //9
		3.05,    0.003, 2.3,	0, 0, //10
		3.1001,   0.003, 2.3,	1, 0, //11

		3.1001,   2, 1.4,		0, 0,    //8
		3.05,    2, 1.4,		1, 0,   //9
		3.05,    2, 2.3,		1, 1, //10
		3.1001,   2, 2.3,		0, 1, //11
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3, //BED BOTTOM
		4, 5, 6, 4, 6, 7, //BED TOP
		0, 1, 5, 0, 5, 4, //BED SIDE 1
		3, 0, 4, 3, 4, 7, //BED SIDE 2
		1, 2, 6, 1, 6, 5, //BED SIDE 3
		3, 2, 6, 3, 6, 7, //BED SIDE 4

		8, 9, 10, 8, 10, 11, 
		12, 13, 14, 12, 14, 15,
		8, 9, 13, 8, 13, 12,
		11, 10, 14, 11, 14, 15,
		10, 9, 13, 10, 13, 14,
		8, 11, 15, 8, 15, 12,
	};

	glGenVertexArrays(1, &cubeVAO10);
	glGenBuffers(1, &cubeVBO10);
	glGenBuffers(1, &cubeEBO10);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO10);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVB10);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEB10);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//buil obj 11
void Demo::BuildWindow()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &cube_texture11);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("texture/body.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("texture/body_specular.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// Build geometry
	float vertices[] = {
		// format position, tex coords
		0.05, 0.9, 0,	 0, 0,
		0.05, 1.8, 0,	 1, 0,
		0.05, 1.8, 3.20, 1, 1,
		0.05, 0.9, 3.20, 0, 1,
	};

	unsigned int indices[] = {
		0, 1, 2, 0, 2, 3,
	};

	glGenVertexArrays(1, &cubeVAO11);
	glGenBuffers(1, &cubeVBO11);
	glGenBuffers(1, &cubeEBO11);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(cubeVAO11);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO11);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO11);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::BuildTexturedPlane()
{
	// Load and create a texture 
	glGenTextures(1, &plane_texture);
	glBindTexture(GL_TEXTURE_2D, plane_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("marble_diffusemap.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture2);
	glBindTexture(GL_TEXTURE_2D, stexture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("marble_specularmap.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5, -50.0,  0,  0, 0.0f,  1.0f,  0.0f,
		50.0, -0.5, -50.0, 50,  0, 0.0f,  1.0f,  0.0f,
		50.0, -0.5,  50.0, 50, 50, 0.0f,  1.0f,  0.0f,
		-50.0, -0.5,  50.0,  0, 50, 0.0f,  1.0f,  0.0f,


	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glGenBuffers(1, &planeEBO);

	glBindVertexArray(planeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

//draw tex 1
void Demo::Drawgrass()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 2
void Demo::DrawHotelFloor()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 3
void Demo::DrawCarpet()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO3); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 4
void Demo::DrawBedFrame1()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO4); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 5
void Demo::DrawBedFrame2()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO5); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 6
void Demo::DrawBed()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO6); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 7
void Demo::DrawWall()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO7); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 8
void Demo::DrawDrawer()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO8); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 9
void Demo::DrawLamp()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO9); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 10
void Demo::DrawDoor()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO10); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//draw tex 11
void Demo::DrawWindow()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cube_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 10.0f);

	glBindVertexArray(cubeVAO11); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::DrawTexturedPlane()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, plane_texture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, stexture2);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 3);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(planeVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Lighting Materials and Lighting Maps: Press [SPACE] to toggle textured cube", 800, 600, false, false);
}