#pragma once
class GameManager {
private:
	std::vector<std::function<void()>> logicFunctions;   // List of functions for updating game logic
	std::vector<std::function<void()>> renderFunctions;  // List of functions for rendering graphics

public:
	int registerLogic(const std::function<void()>& func);
	int registerRender(const std::function<void()>& func);
	void unregisterLogic(int id);
	void unregisterRender(int id);
	void updateLogic();
	void updateRender();

};
