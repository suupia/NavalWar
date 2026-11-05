#include "GameManager.h"

// コールバックの登録時にユニークなIDを返す
int32 GameManager::registerLogic(const std::function<void()>& func) {
	logicFunctions.emplace_back(func);
	return static_cast<int32>(logicFunctions.size()) - 1; // IDはインデックスとする
}

int32 GameManager::registerRender(const std::function<void()>& func) {
	renderFunctions.emplace_back(func);
	return static_cast<int32>(renderFunctions.size()) - 1; // IDはインデックスとする
}

// IDを使用して、特定のコールバックを削除する
void GameManager::unregisterLogic(int32 id) {
	logicFunctions[id] = nullptr; // 関数を無効にする
}

void GameManager::unregisterRender(int32 id) {
	renderFunctions[id] = nullptr; // 関数を無効にする
}

void GameManager::updateLogic() {
	for (const auto& func : logicFunctions) {
		if (func) {
			func();
		}
	}
}

void GameManager::updateRender() {
	for (const auto& func : renderFunctions) {
		if (func) {
			func();
		}
	}
}
