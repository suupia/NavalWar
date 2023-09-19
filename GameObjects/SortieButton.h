#pragma once
#include "../GameManager.h"
#include "GameObject.h"
#include "Ship.h"

class SortieButton : GameObject
{
private:
	GameManager& gm_;
	RectF rect_;
	const Font& font_;
	int index_;
	std::vector<std::unique_ptr<Ship>> ships_;
	int logicId_;
	int renderId_;

public:
	SortieButton(GameManager& gm, RectF rect, const Font& font, int index)
		: gm_(gm), rect_(rect), index_(index), font_(font)
	{
		// Register functions and save their IDs
		logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
		renderId_ = gm_.registerRender([this]() { this->UpdateRender(); });
	}

	~SortieButton()
	{
		// Unregister the callbacks in the destructor
		Print << U"Destruct SortieButton";
		gm_.unregisterLogic(logicId_);
		gm_.unregisterRender(renderId_);
	}

	void UpdateLogic();
	void UpdateRender();
	void Click();
};
