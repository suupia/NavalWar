#pragma once
#include "../GameManager.h"
#include "GameObject.h"

class Currency
{
private:
	GameManager& gm_;
	const Font& font_;
	double amount_;
	double amouontPerSecond_;
public:
	Currency(GameManager& gm, const Font& font, double amouont, double amouontPerSecond)
		: gm_(gm), font_(font), amount_(amouont), amouontPerSecond_(amouontPerSecond)
	{
		gm_.registerLogic([&]() { this->UpdateLogic(); });
		gm_.registerRender([&]() { this->UpdateRender(); });
	}
	void UpdateLogic();
	void UpdateRender();
};
