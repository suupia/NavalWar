#include "../stdafx.h"
#include "IncomeButton.h"
#include "BattleBalance.h"

IncomeButton::IncomeButton(GameManager& gm, Currency& currency, RectF rect, const Font& font)
	: gm_(gm)
	, rect_(rect)
	, font_(font)
	, currency_(currency)
	, level_(0)
{
	logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
	renderId_ = gm_.registerRender([this]() { this->UpdateRender(); });
}

IncomeButton::~IncomeButton()
{
	gm_.unregisterLogic(logicId_);
	gm_.unregisterRender(renderId_);
}

int IncomeButton::NextCost() const
{
	int cost = BattleBalance::IncomeUpgradeBaseCost;
	for (int i = 0; i < level_; ++i)
	{
		cost = cost * 3 / 2;
	}
	return cost;
}

void IncomeButton::UpdateLogic()
{
}

void IncomeButton::UpdateRender()
{
	const bool maxed = level_ >= BattleBalance::IncomeUpgradeMaxLevel;
	const int cost = maxed ? 0 : NextCost();
	const bool ready = !maxed && currency_.GetAmount() >= cost;
	rect_.draw(ready ? ColorF{ 0.72, 0.88, 0.55 } : ColorF{ 0.55, 0.58, 0.62 });
	font_(U"増産").draw(22, rect_.x + 12, rect_.y + 12, Palette::Black);
	if (maxed)
	{
		font_(U"MAX").draw(22, rect_.x + 12, rect_.y + 44, Palette::Black);
	}
	else
	{
		font_(U"cost:{}"_fmt(cost)).draw(22, rect_.x + 12, rect_.y + 44, Palette::Black);
	}
	font_(U"+{:.0f}/s  Lv{}"_fmt(BattleBalance::IncomeUpgradeBonus, level_)).draw(22, rect_.x + 12, rect_.y + 76, Palette::Black);
}

void IncomeButton::Click()
{
	if (!rect_.leftClicked())
	{
		return;
	}
	if (level_ >= BattleBalance::IncomeUpgradeMaxLevel)
	{
		return;
	}
	const int cost = NextCost();
	if (currency_.GetAmount() < cost)
	{
		return;
	}
	currency_.AddAmount(-cost);
	currency_.AddAmountPerSecond(BattleBalance::IncomeUpgradeBonus);
	++level_;
}

void IncomeButton::Reset()
{
	level_ = 0;
}
