#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <Files/TextLoader.h>
#include <string>
#include <iostream>


unsigned int shaderProgram = 0;
void initShader(const char* vertexFile, const char* fragmentFile){
	unsigned int vertexShader, fragmentShader;

	std::string vertSrc, fragSrc;
	far::loadTextFromFile(vertexFile, vertSrc);
	std::cout << "Start:" << vertSrc << "\n";
	far::loadTextFromFile(fragmentFile, fragSrc);
	const char* vert = vertSrc.c_str();
	const char* frag = fragSrc.c_str();
	printf("Sup");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vert, NULL);
	glCompileShader(vertexShader);
	{
		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if(!success){
    		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\t %s", infoLog );
		}
	}
	

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &frag, NULL);
	glCompileShader(fragmentShader);

	{
		int  success;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if(!success){
    		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    		printf("ERROR::SHADER::FRAG::COMPILATION_FAILED\t %s", infoLog );
		}
	}

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	{
		int  success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if(!success) {
    		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    		printf("ERROR::SHADER::COMP::COMPILATION_FAILED\t %s", infoLog );
		}
	}

}

int main(){
	std::cout << "test \n";
	if(!glfwInit()) printf("Failed to init glfw");


   	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//version 4.6 Core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Far", NULL, NULL);
	glfwMakeContextCurrent(window);
	if(!window){
		printf("Failed to load window");
	}
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Something went wrong!\n");
	}
	glViewport(0, 0, 640, 480);

	
	int index = 0;

	initShader("src/Resources/Shaders/pass.vert", "src/Resources/Shaders/RayMarching.frag");
	glUseProgram(shaderProgram);

	float sz = 0.75f;
	float vertices[7 * 6] = {
		-sz, -sz, 0.0f, 	1.0f, 1.0f, 1.0f, 1.0f, // bottom left
		-sz,  sz, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f, // top left
		 sz, -sz, 0.0f, 	1.0f, 1.0f, 1.0f, 1.0f, // bottom right

		 sz,  sz, 0.0f, 	0.0f, 1.0f, 1.0f, 1.0f, //top right
		-sz,  sz, 0.0f,	0.0f, 1.0f, 1.0f, 1.0f,
		 sz, -sz, 0.0f, 	0.0f, 1.0f, 1.0f, 1.0f	 };
	
	unsigned int bufferID, arrayID;
	glGenVertexArrays(1, &arrayID);
	glBindVertexArray(arrayID);
	
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)0);///xyz
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	int el = 0;
	//!glfwWindowShouldClose(window)
	int frames = 0;
	int prevFrames = 0;
	double startFrameTime = glfwGetTime();
	double lastFrameTime = glfwGetTime();
	double deltaTime = lastFrameTime - startFrameTime;
	double elapsedTime = deltaTime;
	while(!glfwWindowShouldClose(window)) {
		startFrameTime = glfwGetTime();
		deltaTime = startFrameTime - lastFrameTime;
		lastFrameTime = startFrameTime;
		elapsedTime += deltaTime;
		if(elapsedTime >= 1.0){
			elapsedTime = 0;
			frames = 0;
		}
		
		glClearColor(0.2, 0.1, 0.2, 1.0);
		glUseProgram(shaderProgram);
		glBindVertexArray(arrayID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwPollEvents();
		glfwSwapBuffers(window);
		frames++;
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();

    return 4;
}







	


	