#pragma once
#include "../GameManager.h"
#include "GameObject.h"

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
		// 関数の登録時に返されるIDを保存する
		logicId_ = gm_.registerLogic([&]() { this->UpdateLogic(); });
		renderId_ = gm_.registerRender([&]() { this->UpdateRender(); });
	}

	~Ship()
	{
		Print << U"Destruct Ship";
		gm_.unregisterLogic(logicId_);
		gm_.unregisterRender(renderId_);
	}

	void UpdateLogic();
	void UpdateRender();
};
