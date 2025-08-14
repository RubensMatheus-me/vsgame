#pragma once
#include <stack>
#include "Scene.h"

class SceneManager {
	public:
		SceneManager();
		~SceneManager();

		void pushScene(Scene* scene);
		void popScene();
		void changeScene(Scene* scene);
		void handleInput(SDL_Event& event);
		void update(float dt);
		void render();
		void cleanUp();

	private:
		std::stack<Scene*> sceneStack;
};