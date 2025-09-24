#pragma once
#include <stack>
#include "Scene.h"

class SceneManager {
public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }

	~SceneManager();

    void pushScene(Scene* scene);
    void popScene();
    void changeScene(Scene* scene);
    void handleInput(SDL_Event& event);
    void update(float dt);
    void render();
    void cleanUp();

	Scene* getCurrentScene();

private:
    SceneManager() = default;

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    std::stack<Scene*> sceneStack;
};
