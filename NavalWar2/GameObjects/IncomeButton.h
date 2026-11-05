#pragma once
#include "../GameManager.h"
#include "Currency.h"
#include "GameObject.h"

/// 所持金の増加速度を上げるボタン。
class IncomeButton : public GameObject
{
private:
	GameManager& gm_;
	RectF rect_;
	const Font& font_;
	Currency& currency_;
	int level_;
	int logicId_;
	int renderId_;

	int NextCost() const;

public:
	IncomeButton(GameManager& gm, Currency& currency, RectF rect, const Font& font);
	~IncomeButton() override;

	IncomeButton(const IncomeButton&) = delete;
	IncomeButton& operator=(const IncomeButton&) = delete;

	void UpdateLogic() override;
	void UpdateRender() override;
	void Click();
	void Reset();
};
