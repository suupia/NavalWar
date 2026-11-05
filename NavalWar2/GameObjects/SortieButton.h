#pragma once
#include "Currency.h"
#include "../GameManager.h"
#include "GameObject.h"
#include "ShipContainer.h"
#include "UnitStats.h"

/// 通貨とクールダウンを消費して艦を 1 隻出撃させるボタン。
class SortieButton : public GameObject
{
private:
	GameManager& gm_;
	RectF rect_;
	const Font& font_;
	ShipContainer& shipContainer_;
	Currency& currency_;
	UnitStats stats_;
	Texture icon_;
	double cooldown_;
	int logicId_;
	int renderId_;

public:
	SortieButton(GameManager& gm, ShipContainer& shipContainer, Currency& currency, RectF rect, const Font& font, const UnitStats& stats);
	~SortieButton() override;

	SortieButton(const SortieButton&) = delete;
	SortieButton& operator=(const SortieButton&) = delete;

	void UpdateLogic() override;
	void UpdateRender() override;
	void Click();
	void ResetCooldown();
};
