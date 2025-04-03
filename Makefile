TARGET = game

CXX = g++
CXXFLAGS = -std=c++23 -Wall -Iinclude -I../my-lib/include
LDFLAGS = -lSDL2 -lSDL2_image

SRC = $(shell find src -type f -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)