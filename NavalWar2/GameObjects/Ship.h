#pragma once
#include "../GameManager.h"
#include "GameObject.h"

/// 右へ進む艦。生成時に GameManager へ更新処理を登録する。
class Ship : public GameObject
{
private:
	GameManager& gm_;
	Texture texture_;
	Vec2 pos_;
	int speed_;
	int cost_;
	int logicId_;
	int renderId_;

public:
	Ship(GameManager& gm, const Vec2& pos)
	   : gm_(gm), texture_(U"🚢"_emoji), pos_(pos), speed_(100), cost_(10)
	{
		logicId_ = gm_.registerLogic([&]() { this->UpdateLogic(); });
		renderId_ = gm_.registerRender([&]() { this->UpdateRender(); });
	}

	~Ship() override
	{
		Print << U"Destruct Ship";
		gm_.unregisterLogic(logicId_);
		gm_.unregisterRender(renderId_);
	}

	void UpdateLogic() override;
	void UpdateRender() override;
};
