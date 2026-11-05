#pragma once

/// ロジック更新と描画を持つゲームオブジェクトの基底。
class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void UpdateLogic() = 0;
	virtual void UpdateRender() = 0;
};
