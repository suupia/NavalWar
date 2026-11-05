#pragma once
#include <functional>
#include <vector>

/// ロジックと描画のコールバックを ID で登録し、毎フレーム実行する。
class GameManager {
private:
	std::vector<std::function<void()>> logicFunctions;   // List of functions for updating game logic
	std::vector<std::function<void()>> renderFunctions;  // List of functions for rendering graphics

public:
	int32 registerLogic(const std::function<void()>& func);
	int32 registerRender(const std::function<void()>& func);
	void unregisterLogic(int32 id);
	void unregisterRender(int32 id);
	void updateLogic();
	void updateRender();
};
