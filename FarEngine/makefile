CXX = g++ 
CXXFLAGS = -std=c++17 -Wall -w -g

OUT_DIR = bin
LAUNCHER_NAME = Far
SRC_DIR = src
ENTRY_POINT = $(SRC_DIR)/main.cpp

GLAD_ROOT = outsourced/glad/
GLAD_INC = $(GLAD_ROOT)include
GLAD_SRC = $(GLAD_ROOT)src

GLFW_ROOT = outsourced/glfw-3.3.2/MinGWmingw32/
GLFW_INC = $(GLFW_ROOT)include
GLFW_LIB = $(GLFW_ROOT)lib
GLFW_SRC = $(GLFW_ROOT)../src


SPDLOG_ROOT = outsourced/spdlog/
SPDLOG_INC = $(SPDLOG_ROOT)include
SPDLOG_SRC = $(SPDLOG_ROOT)src

GLM_ROOT = outsourced/glm/

INC_INTERNAL = -I $(SRC_DIR) 
INC=-I $(SRC_DIR)/ -I $(GLAD_INC) -I $(GLFW_INC) -I $(GLM_ROOT)
LIBS = -L $(GLFW_LIB)
LINKS = -lglfw3 -lglu32 -lopengl32 -lgdi32



OBJECTS = $(OUT_DIR)/TextLoader.o $(OUT_DIR)/StartupSystems.o $(OUT_DIR)/Window.o\
 $(OUT_DIR)/FarCore.o  $(OUT_DIR)/EntityManager.o $(OUT_DIR)/HashImplementation.o\
 $(OUT_DIR)/BatchRenderer2D.o  $(OUT_DIR)/InputManager.o
all: main

main: $(ENTRY_POINT) FarCore.o
	$(CXX) $(CXXFLAGS) $(LIBS) $(INC) -o $(OUT_DIR)/$(LAUNCHER_NAME) $(OBJECTS) $(ENTRY_POINT) $(GLAD_SRC)/glad.c $(LINKS)


ALL_SETTINGS = $(CXX) $(CXXFLAGS) $(LIBS) $(INC) $(INC_INTERNAL)
FarCore.o: $(SRC_DIR)/FarCore.cpp StartupSystems.o TextLoader.o Window.o EntityManager.o HashImplementation.o BatchRenderer2D.o InputManager.o
	$(ALL_SETTINGS) -c $(SRC_DIR)/FarCore.cpp -o $(OUT_DIR)/FarCore.o

StartupSystems.o: $(SRC_DIR)/Startup/StartupSystems.cpp
	$(ALL_SETTINGS) -c $(SRC_DIR)/Startup/StartupSystems.cpp -o $(OUT_DIR)/StartupSystems.o

TextLoader.o: $(SRC_DIR)/Tools/Files/TextLoader.cpp
	$(ALL_SETTINGS) -c $(SRC_DIR)/Tools/Files/TextLoader.cpp -o $(OUT_DIR)/TextLoader.o

Window.o: $(SRC_DIR)/Rendering/Window.cpp
	$(ALL_SETTINGS) -c $(SRC_DIR)/Rendering/Window.cpp -o $(OUT_DIR)/Window.o

Logger.o: $(SRC_DIR)/Tools/Logging/Logger.cpp
	$(ALL_SETTINGS) -c $(SRC_DIR)/Tools/Logging/Logger.cpp -o $(OUT_DIR)/Logger.o

EntityManager.o: $(SRC_DIR)/EntityComponentSystem/EntityManager.cpp
	$(ALL_SETTINGS) -c $(SRC_DIR)/EntityComponentSystem/EntityManager.cpp -o $(OUT_DIR)/EntityManager.o

HashImplementation.o: $(SRC_DIR)/EntityComponentSystem/Components/HashImplementation.cpp
	$(ALL_SETTINGS) -c $(SRC_DIR)/EntityComponentSystem/Components/HashImplementation.cpp -o $(OUT_DIR)/HashImplementation.o

BatchRenderer2D.o: $(SRC_DIR)/Rendering/Renderers/BatchRenderer2D.cpp
	$(ALL_SETTINGS) -c $(SRC_DIR)/Rendering/Renderers/BatchRenderer2D.cpp -o $(OUT_DIR)/BatchRenderer2D.o

InputManager.o: $(SRC_DIR)/Tools/Input/InputManager.cpp
	$(ALL_SETTINGS) -c $(SRC_DIR)/Tools/Input/InputManager.cpp -o $(OUT_DIR)/InputManager.o

Logger.o: $(SRC_DIR)/Tools/Logging/Logger.cpp
	$(ALL_SETTINGS) -c $(SRC_DIR)/Tools/Logging/Logger.cpp -o $(OUT_DIR)/Logger.o


run: $(OUT_DIR)/$(LAUNCHER_NAME).exe
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe



fetch:
	git fetch --all
	git reset --hard origin/master


clean:
	del /f $(OUT_DIR)/$(LAUNCHER_NAME).exe