#pragma once
#include "Currency.h"
#include "../GameManager.h"
#include "GameObject.h"
#include "Ship.h"
#include "ShipContainer.h"

class SortieButton : GameObject
{
private:
	GameManager& gm_;
	RectF rect_;
	const Font& font_;
	int index_;
	ShipContainer& shipContainer_;
	Currency& currency_;
	int logicId_;
	int renderId_;

public:
	SortieButton(GameManager& gm,ShipContainer& ship_container,Currency& currency,  RectF rect, const Font& font, int index)
		: gm_(gm),shipContainer_(ship_container),currency_(currency), rect_(rect), index_(index), font_(font)
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
