#include "stdafx.h"
#include "GameManager.h"

namespace {

int registerCallback(std::vector<std::function<void()>>& callbacks, const std::function<void()>& func) {
	callbacks.emplace_back(func);
	return static_cast<int>(callbacks.size()) - 1;
}

void unregisterCallback(std::vector<std::function<void()>>& callbacks, int id) {
	if (id < 0 || static_cast<size_t>(id) >= callbacks.size()) {
		return;
	}
	callbacks[id] = nullptr;
}

void updateCallbacks(const std::vector<std::function<void()>>& callbacks) {
	for (const auto& func : callbacks) {
		if (func) {
			func();
		}
	}
}

}

int GameManager::registerLogic(const std::function<void()>& func) {
	return registerCallback(logicFunctions, func);
}

int GameManager::registerRender(const std::function<void()>& func) {
	return registerCallback(renderFunctions, func);
}

void GameManager::unregisterLogic(int id) {
	unregisterCallback(logicFunctions, id);
}

void GameManager::unregisterRender(int id) {
	unregisterCallback(renderFunctions, id);
}

void GameManager::updateLogic() {
	updateCallbacks(logicFunctions);
}

void GameManager::updateRender() {
	updateCallbacks(renderFunctions);
}
