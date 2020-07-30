#include "FarCore.h"



namespace far{

   
    void FarCore::load(){
		initForPep();
        //StartupSystems::initSubSystems();
        StartupSystems::_initGLFW();
        _windowRef = new Window(1080, 720, "Far Game Engine", false);
        StartupSystems::_initGlad();
        init();
        //glViewport(0, 0, 640, 480); //oopsxd





		



    }
    void FarCore::update(){
		glfwPollEvents();
        startFrameTime = glfwGetTime();
		deltaTime = startFrameTime - lastFrameTime;
		lastFrameTime = startFrameTime;
		elapsedTime += deltaTime;
		if(elapsedTime >= 1.0){
			elapsedTime = 0;
			frames = 0;
		}

    }

    void FarCore::render(){
        glClearColor(0.2, 0.1, 0.2, 1.0);
		glUseProgram(shaderProgram);
		int loc = glGetUniformLocation(shaderProgram, "time");
		glUniform1f(loc, glfwGetTime());
		glBindVertexArray(arrayID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(_windowRef->getWindow());
		frames++;

    }

    void FarCore::unload(){

        glfwDestroyWindow(_windowRef->getWindow());
	    glfwTerminate();
    }



 void FarCore::init(){
    int index = 0;

	loadShaders("src/Resources/Shaders/pass.vert", "src/Resources/Shaders/RayMarching.frag");
	glUseProgram(shaderProgram);

	float sz = 1.0f;
	float vertices[7 * 6] = {
		-sz, -sz, 0.0f, 	1.0f, 1.0f, 1.0f, 1.0f, // bottom left
		-sz,  sz, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f, // top left
		 sz, -sz, 0.0f, 	1.0f, 1.0f, 1.0f, 1.0f, // bottom right

		 sz,  sz, 0.0f, 	0.0f, 1.0f, 1.0f, 1.0f, //top right
		-sz,  sz, 0.0f,	0.0f, 1.0f, 1.0f, 1.0f,
		 sz, -sz, 0.0f, 	0.0f, 1.0f, 1.0f, 1.0f	 };
	
	glGenVertexArrays(1, &arrayID);
	glBindVertexArray(arrayID);
	
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)0);///xyz
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    }
void FarCore::loadShaders(const char* vertexFile, const char* fragmentFile){
	unsigned int vertexShader, fragmentShader;

	std::string vertSrc, fragSrc;
	far::FileLoaderFactory::loadTextFromFile(vertexFile, vertSrc);
	far::FileLoaderFactory::loadTextFromFile(fragmentFile, fragSrc);
	const char* vert = vertSrc.c_str();
	const char* frag = fragSrc.c_str();
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

}