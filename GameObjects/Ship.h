#pragma once
#include "../GameManager.h"
#include "GameObject.h"

class Ship : GameObject
{
private:
	GameManager& gm_;
	Texture texture_;
	Vec2 pos_;
	int speed_;
	int cost_;

public:
	Ship(GameManager& gm, const Vec2& pos)
	   : gm_(gm), texture_(U"🚢"_emoji), pos_(pos), speed_(100), cost_(10)
	{
		gm_.registerLogic([&]() { this->UpdateLogic(); });
		gm_.registerRender([&]() { this->UpdateRender(); });
	}
	void UpdateLogic();
	void UpdateRender();
};
