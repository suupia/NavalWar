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
	const bool hover = rect_.mouseOver();
	const bool pressed = ready && rect_.leftPressed();

	ColorF fill{ 0.78, 0.90, 0.64 };
	ColorF frame{ 0.22, 0.42, 0.24 };
	if (!ready)
	{
		fill = ColorF{ 0.62, 0.67, 0.62 };
		frame = ColorF{ 0.36, 0.42, 0.36 };
	}
	else if (pressed)
	{
		fill = ColorF{ 0.62, 0.78, 0.50 };
	}
	else if (hover)
	{
		fill = ColorF{ 0.90, 0.98, 0.72 };
		frame = ColorF{ 0.10, 0.48, 0.22 };
	}

	const Vec2 shift = pressed ? Vec2{ 0.0, 2.0 } : Vec2{ 0.0, 0.0 };
	RoundRect{ rect_.pos + Vec2{ 0.0, 4.0 }, rect_.size, 12 }.draw(ColorF{ 0.05, 0.10, 0.16, 0.25 });
	const RoundRect card{ rect_.pos + shift, rect_.size, 12 };
	card.draw(fill);
	card.drawFrame(0.0, hover && ready ? 4.0 : 2.5, frame);

	const ColorF coin = ready ? ColorF{ Palette::Gold } : ColorF{ 0.55, 0.50, 0.32 };
	Circle{ rect_.center().x + shift.x, rect_.y + 36.0 + shift.y, 16 }.draw(coin);
	Circle{ rect_.center().x + shift.x, rect_.y + 36.0 + shift.y, 16 }.drawFrame(2.0, Palette::White);

	const ColorF text{ 0.10, 0.18, 0.12 };
	font_(U"増産").drawAt(18, rect_.center() + shift + Vec2{ 0.0, 16.0 }, text);
	if (maxed)
	{
		font_(U"MAX").drawAt(15, rect_.center() + shift + Vec2{ 0.0, 38.0 }, text);
	}
	else
	{
		font_(U"cost:{}"_fmt(cost)).drawAt(15, rect_.center() + shift + Vec2{ 0.0, 38.0 }, text);
	}
	font_(U"+{:.0f}/s Lv{}"_fmt(BattleBalance::IncomeUpgradeBonus, level_)).drawAt(14, rect_.center() + shift + Vec2{ 0.0, 56.0 }, text);
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
