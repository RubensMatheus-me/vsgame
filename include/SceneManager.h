#pragma once
#include <stack>
#include "Scene.h"
#include "TickRate.h"
#include <memory>

class SceneManager {
public:
	int width;
	int height;

    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }

	~SceneManager();

    void pushScene(Scene* scene);
    void popScene();
    void changeScene(Scene* scene);
    void handleInput(SDL_Event& event);
    void update();
    void render();
    void cleanUp();
	void createWindow();
	void destroyWindow();

	bool getIsRunning() const {return this->isRunning;}
	void setIsRunning(const bool newIsRunning) {this->isRunning = newIsRunning;}
	void createWindow(const char *title, int xPos, int yPos, int width, int height, bool fullscreen);
	void toggleFullscreen();

	int getWidth() {return this->width;}
	int getHeight() {return this->height;}
	std::unique_ptr<TickRate> &getTickRate() { return this->tickRate; }

	SDL_Renderer *getRenderer() { return this->renderer; }
		
	void setWidth(const int newWidth) {this->width = newWidth;}
	void setHeight(const int newHeight) {this->height = newHeight;}

	Scene* getCurrentScene();
	

private:
    SceneManager() = default;
	bool fullScreen;
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
	bool isRunning;
    std::stack<Scene*> sceneStack;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::unique_ptr<TickRate> tickRate = std::make_unique<TickRate>();
};
