#include "FarCore.h"
#include "EntityComponentSystem/Systems/MeshProcessorSystem.h"
#include <sstream>

namespace far{

   
    void FarCore::_load(){

		loadShaders("src/Resources/Shaders/pass.vert", "src/Resources/Shaders/pass.frag");
		glUseProgram(shaderProgram);
		//audio = new ikAudio();
		//audio->playSound(FAR_INTERNAL_SOUNDS("Tension.mp3"));
		
    }
    void FarCore::update(){
		glfwPollEvents();
        startFrameTime = glfwGetTime();
		deltaTime = startFrameTime - lastFrameTime;
		lastFrameTime = startFrameTime;
		elapsedTime += deltaTime;
		if(elapsedTime >= 1.0){
			elapsedTime = 0;
			_fps = _frames/(deltaTime);
			_frames = 0;
		}
		_frames++;
		std::stringstream ss;
		ss << _windowRef->getName() << " - " << _fps << " FPS";
		glfwSetWindowTitle(_windowRef->getWindow(), ss.str().c_str());
		_mps.update(deltaTime);
		_ms.move(_entityManager->getAssociatedEntities<TransformComponent>()[0], glm::vec3(0.f, 0.1f, 0.f));
		_ms.update(deltaTime);
    }

    void FarCore::render(){

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glClearColor(0.2, 0.2, 0.4, 1.0);
		glUseProgram(shaderProgram);
		//static int loc = glGetUniformLocation(shaderProgram, "u_texture");
		//glUniform1f(loc, 0);
		//glBindVertexArray(arrayID);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		frames++;
		_batchRenderer.begin();
    	_batchRenderer.submit(_entityManager);
		_batchRenderer.end();
		_batchRenderer.flush();
		glfwSwapBuffers(_windowRef->getWindow());

    }

    void FarCore::unload(){

        glfwDestroyWindow(_windowRef->getWindow());
	    glfwTerminate();
    }

	void FarCore::init(){
		_entityManager = std::make_shared<far::EntityManager>();
		initForPep();
		_frames = 0;
		_mps = far::MeshProcessorSystem(_entityManager);
		_ms = far::MovementSystem(_entityManager);
		StartupSystems::_initGLFW();
		_windowRef = new Window(1080, 720, "Far Game Engine", false);
		StartupSystems::_initGlad();
		_batchRenderer = far::BatchRenderer2D();
		_batchRenderer.init();
		this->_load();
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