#pragma once
#include <functional>
#include <vector>

/// @brief ゲーム全体のロジック更新および描画関数の管理を行うクラス
class GameManager {
private:
	std::vector<std::function<void()>> logicFunctions;   // List of functions for updating game logic
	std::vector<std::function<void()>> renderFunctions;  // List of functions for rendering graphics

public:
	/// @brief ロジック更新コールバックを登録します
	/// @param func 毎フレーム実行されるロジック更新関数
	/// @return 登録されたコールバックの識別用ID
	int32 registerLogic(const std::function<void()>& func);

	/// @brief 描画コールバックを登録します
	/// @param func 毎フレーム実行される描画関数
	/// @return 登録されたコールバックの識別用ID
	int32 registerRender(const std::function<void()>& func);

	/// @brief 登録されたロジック更新コールバックを解除します
	/// @param id 登録時に返された識別用ID
	void unregisterLogic(int32 id);

	/// @brief 登録された描画コールバックを解除します
	/// @param id 登録時に返された識別用ID
	void unregisterRender(int32 id);

	/// @brief 登録されているすべての有効なロジック更新処理を実行します
	void updateLogic();

	/// @brief 登録されているすべての有効な描画処理を実行します
	void updateRender();
};
