CXX = g++
CXXFLAGS = -Wall -w -g

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

INC_INTERNAL = -I $(SRC_DIR)
INC=-I $(SRC_DIR)/ -I $(GLAD_INC) -I $(GLFW_INC)
LIBS = -L $(GLFW_LIB)
LINKS = -lglfw3 -lglu32 -lopengl32 -lgdi32

all: main

main: $(ENTRY_POINT) TextLoader.o
	$(CXX) $(CXXFLAGS) $(LIBS) $(INC) -o $(OUT_DIR)/$(LAUNCHER_NAME) $(OUT_DIR)/TextLoader.o $(ENTRY_POINT) $(GLAD_SRC)/glad.c $(LINKS)



TextLoader.o: $(SRC_DIR)/Files/TextLoader.cpp
	$(CXX) $(CXXFLAGS) $(INC_INTERNAL) -c $(SRC_DIR)/Files/TextLoader.cpp -o $(OUT_DIR)/TextLoader.o

run: $(OUT_DIR)/$(LAUNCHER_NAME).exe
	./$(OUT_DIR)/$(LAUNCHER_NAME).exe






clean:
	cd $(OUT_DIR)
	rm -f Far.exe