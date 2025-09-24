#include "SceneManager.h"

SceneManager::~SceneManager() {
	cleanUp();
}

void SceneManager::pushScene(Scene* scene) {
	if (!sceneStack.empty()) {
		sceneStack.top()->cleanUp();
	}
	sceneStack.push(scene);
	scene->init();
}

void SceneManager::popScene() {
	if (!sceneStack.empty()) {
		sceneStack.top()->cleanUp();
		sceneStack.pop();
	}
}

void SceneManager::changeScene(Scene* scene) {
	cleanUp();
	pushScene(scene);
}

void SceneManager::handleInput(SDL_Event& event) {
	if (!sceneStack.empty()) {
		sceneStack.top()->handleInput(event);
	}
}

void SceneManager::update(float dt) {
	if (!sceneStack.empty()) {
		sceneStack.top()->update(dt);
	}
}

void SceneManager::render() {
	if (!sceneStack.empty()) {
		sceneStack.top()->render();
	}
}

void SceneManager::cleanUp() {
	while (!sceneStack.empty()) {
		sceneStack.top()->cleanUp();
		delete sceneStack.top();
		sceneStack.pop();
	}
}

Scene* SceneManager::getCurrentScene() {
    if (!sceneStack.empty()) {
        return sceneStack.top();
    }
    return nullptr;
}