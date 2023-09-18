#include "GameManager.h"

// Register a function for updating game logic
void GameManager::registerLogic(const std::function<void()>& func) {
	logicFunctions.push_back(func);
}

// Register a function for rendering graphics
void GameManager::registerRender(const std::function<void()>& func) {
	renderFunctions.push_back(func);
}

// Execute all the registered functions for updating game logic
void GameManager::updateLogic() {
	for (const auto& func : logicFunctions) {
		if (func) {
			func();
		} else {
			Print << U"A logic function is invalid!" ;
		}
	}
}

// Execute all the registered functions for rendering graphics
void GameManager::updateRender() {
	for (const auto& func : renderFunctions) {
		if (func) {
			func();
		} else {
			Print << U"A render function is invalid!";
		}
	}
}
