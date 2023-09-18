#pragma once
#include "GameManager.h"

class Ship
{
private:
	GameManager& gm_;
	Texture texture_;
	Vec2 pos_;
	int speed_;

public:
	Ship(GameManager& gm, const Vec2& pos)
	   : gm_(gm), texture_(U"🚢"_emoji), pos_(pos), speed_(100)
	{
		gm_.registerLogic([&]() { this->UpdateLogic(); });
		gm_.registerRender([&]() { this->UpdateRender(); });
	}
	void UpdateLogic();
	void UpdateRender();
};
