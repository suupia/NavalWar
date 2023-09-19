#pragma once
#include "../GameManager.h"
#include "GameObject.h"

class Currency
{
private:
	GameManager& gm_;
	const Font& font_;
	double amount_;
	double amountPerSecond_;
	int logicId_;
	int renderId_;

public:
	Currency(GameManager& gm, const Font& font, double amount, double amountPerSecond)
		: gm_(gm), font_(font), amount_(amount), amountPerSecond_(amountPerSecond)
	{
		// Register functions and save their IDs
		logicId_ = gm_.registerLogic([&]() { this->UpdateLogic(); });
		renderId_ = gm_.registerRender([&]() { this->UpdateRender(); });
	}

	~Currency()
	{
		// Unregister the callbacks in the destructor
		gm_.unregisterLogic(logicId_);
		gm_.unregisterRender(renderId_);
	}

	void UpdateLogic();
	void UpdateRender();
};
