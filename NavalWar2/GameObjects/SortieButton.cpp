#include "../stdafx.h"
#include "SortieButton.h"
#include <algorithm>

SortieButton::SortieButton(GameManager& gm, ShipContainer& shipContainer, Currency& currency, RectF rect, const Font& font, const UnitStats& stats)
	: gm_(gm)
	, rect_(rect)
	, font_(font)
	, shipContainer_(shipContainer)
	, currency_(currency)
	, stats_(stats)
	, icon_(Emoji{ stats.emoji })
	, cooldown_(0.0)
{
	logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
	renderId_ = gm_.registerRender([this]() { this->UpdateRender(); });
}

SortieButton::~SortieButton()
{
	gm_.unregisterLogic(logicId_);
	gm_.unregisterRender(renderId_);
}

void SortieButton::UpdateLogic()
{
	if (cooldown_ > 0.0)
	{
		cooldown_ = std::max(0.0, cooldown_ - Scene::DeltaTime());
	}
}

void SortieButton::UpdateRender()
{
	const bool affordable = currency_.GetAmount() >= stats_.cost;
	const bool ready = cooldown_ <= 0.0 && affordable;
	rect_.draw(ready ? ColorF{ 0.95 } : ColorF{ 0.55, 0.58, 0.62 });
	font_(stats_.name).draw(22, rect_.x + 12, rect_.y + 12, Palette::Black);
	font_(U"cost:{}"_fmt(stats_.cost)).draw(22, rect_.x + 12, rect_.y + 44, Palette::Black);
	if (cooldown_ > 0.0)
	{
		font_(U"cd:{:.1f}"_fmt(cooldown_)).draw(22, rect_.x + 12, rect_.y + 76, Palette::Darkred);
	}
	else if (!affordable)
	{
		font_(U"不足").draw(22, rect_.x + 12, rect_.y + 76, Palette::Darkred);
	}
	const double iconScale = (icon_.width() > 0) ? (56.0 / icon_.width()) : 1.0;
	icon_.scaled(iconScale).draw(rect_.x + rect_.w - 68, rect_.y + 12);
}

void SortieButton::Click()
{
	if (!rect_.leftClicked() || cooldown_ > 0.0 || currency_.GetAmount() < stats_.cost)
	{
		return;
	}
	currency_.AddAmount(-stats_.cost);
	cooldown_ = stats_.cooldown;
	shipContainer_.AddShip(Faction::Player, stats_);
}

void SortieButton::ResetCooldown()
{
	cooldown_ = 0.0;
}
