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

        _batchRenderer = far::BatchRenderer2D();
		_batchRenderer.init();

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
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glClearColor(0.2, 0.2, 0.4, 1.0);
		glUseProgram(shaderProgram);
		//static int loc = glGetUniformLocation(shaderProgram, "u_texture");
		//glUniform1f(loc, 0);
		//glBindVertexArray(arrayID);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(_windowRef->getWindow());
		frames++;
		_batchRenderer.begin();
    	_batchRenderer.submit(_entityManager);
		_batchRenderer.end();
		_batchRenderer.flush();

    }

    void FarCore::unload(){

        glfwDestroyWindow(_windowRef->getWindow());
	    glfwTerminate();
    }



	void FarCore::init(){
		int index = 0;

		loadShaders("src/Resources/Shaders/pass.vert", "src/Resources/Shaders/pass.frag");
		glUseProgram(shaderProgram);

		float sz = 3.0f / 4.0f;
		float vertices[9 * 6] = {
			-sz, -sz, 0.0f, 	1.0f, 0.0f, 1.0f, 1.0f, 		0.0f,0.0f, // bottom left
			-sz,  sz, 0.0f,		1.0f, 0.0f, 1.0f, 1.0f, 		0.0f,1.0f, // top left
			sz, -sz, 0.0f, 		1.0f, 0.0f, 1.0f, 1.0f, 		1.0f,0.0f,// bottom right
			
			sz,  sz, 0.0f, 		1.0f, 0.0f, 1.0f, 1.0f, 		1.0f,1.0f,//top right
			-sz,  sz, 0.0f,		1.0f, 0.0f, 1.0f, 1.0f, 		0.0f,1.0f,// top left
			sz, -sz, 0.0f, 		1.0f, 0.0f, 1.0f, 1.0f, 		1.0f,0.0f};// bottom right };

		glGenVertexArrays(1, &arrayID);
		glBindVertexArray(arrayID);
		
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)0);///xyz
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (const void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);


		int width, height, nrChannels, option;
		option = 3;
		unsigned char* data = FileLoaderFactory::loadImage(FAR_INTERNAL_TEXTURE("wall.jpg"), &width, &height, &nrChannels, 0);
		unsigned int texture;
		glGenTextures(1, &texture);  
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data){
			FAR_DEBUG("Creating image with (" << width << ", " << height << ") dims at " << option - 0x1907 << "+ 3bit properties and " <<nrChannels << "column channels" );
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + (option - 3), width, height, 0, GL_RGB + (option - 3), GL_UNSIGNED_BYTE, data);
		    glGenerateMipmap(GL_TEXTURE_2D);
		
		}
		else{
		    FAR_ERROR("Failed to load texture");;
		}
		glBindTextureUnit(1, texture);
		FileLoaderFactory::free(data);

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