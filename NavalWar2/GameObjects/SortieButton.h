#pragma once
#include "Currency.h"
#include "../GameManager.h"
#include "GameObject.h"
#include "Ship.h"
#include "ShipContainer.h"

/// 通貨を消費して艦を 1 隻出撃させるボタン。
class SortieButton : public GameObject
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
	SortieButton(GameManager& gm, ShipContainer& ship_container, Currency& currency, RectF rect, const Font& font, int index)
		: gm_(gm), rect_(rect), font_(font), index_(index), shipContainer_(ship_container), currency_(currency)
	{
		logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
		renderId_ = gm_.registerRender([this]() { this->UpdateRender(); });
	}

	~SortieButton() override
	{
		Print << U"Destruct SortieButton";
		gm_.unregisterLogic(logicId_);
		gm_.unregisterRender(renderId_);
	}

	void UpdateLogic() override;
	void UpdateRender() override;
	void Click();
};
