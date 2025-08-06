TARGET = game

-include .config.mk

# Caminho padrão da biblioteca (relativo ao projeto)
MY_LIB_PATH ?= ../../libs/my-lib/include


CXX = g++
CXXFLAGS = -std=c++23 -Wall -D_REENTRANT -Iinclude -I$(MY_LIB_PATH) -I/usr/include/SDL2 -I../../libs/include
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRC = $(shell find src -type f -name "*.cpp") main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)