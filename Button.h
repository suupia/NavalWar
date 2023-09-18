#pragma once
#include "GameManager.h"
#include "Ship.h"

class Button
{
private:
	GameManager& gm_;
	RectF rect_;
	int index_;
	std::vector<std::unique_ptr<Ship>> ships_;
public:
	Button(GameManager& gm, RectF rect, int index): gm_(gm), rect_(rect), index_(index)
	{

	}
	void Click();
};
