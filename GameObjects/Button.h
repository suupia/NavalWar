#pragma once
#include "../GameManager.h"
#include "GameObject.h"
#include "Ship.h"

class Button : GameObject
{
private:
	GameManager& gm_;
	RectF rect_;
	const Font& font_;
	int index_;
	std::vector<std::unique_ptr<Ship>> ships_;

public:
	Button(GameManager& gm, RectF rect, const Font& font, int index)
		: gm_(gm), rect_(rect), index_(index), font_(font)
	{
		// Print << U"Button index{}"_fmt(index_);
		gm_.registerLogic([this]() { this->UpdateLogic(); });
		gm_.registerRender([this]() { this->UpdateRender(); });
	}

	void UpdateLogic();
	void UpdateRender();
	void Click();
};
