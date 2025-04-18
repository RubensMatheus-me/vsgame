TARGET = game

CXX = g++
CXXFLAGS = -std=c++23 -Wall -D_REENTRANT -Iinclude -I../my-lib/include -I/usr/include/SDL2
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

SRC = $(shell find src -type f -name "*.cpp") main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)