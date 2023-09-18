class GameManager {
private:
	std::vector<std::function<void()>> logicFunctions;   // List of functions for updating game logic
	std::vector<std::function<void()>> renderFunctions;  // List of functions for rendering graphics

	public:
	void registerLogic(const std::function<void()>& func);
	void registerRender(const std::function<void()>& func);
	void updateLogic();
	void updateRender();

};
