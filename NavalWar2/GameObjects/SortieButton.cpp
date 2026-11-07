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
	const bool cooling = cooldown_ > 0.0;
	const bool ready = !cooling && affordable;
	const bool hover = rect_.mouseOver();
	const bool pressed = ready && rect_.leftPressed();

	ColorF fill{ 0.93, 0.96, 0.99 };
	ColorF frame{ 0.16, 0.34, 0.52 };
	if (!ready)
	{
		fill = ColorF{ 0.62, 0.67, 0.72 };
		frame = ColorF{ 0.35, 0.40, 0.46 };
	}
	else if (pressed)
	{
		fill = ColorF{ 0.78, 0.86, 0.93 };
	}
	else if (hover)
	{
		fill = ColorF{ 0.80, 0.91, 1.0 };
		frame = ColorF{ 0.05, 0.48, 0.86 };
	}

	const Vec2 shift = pressed ? Vec2{ 0.0, 2.0 } : Vec2{ 0.0, 0.0 };
	RoundRect{ rect_.pos + Vec2{ 0.0, 4.0 }, rect_.size, 12 }.draw(ColorF{ 0.05, 0.10, 0.16, 0.25 });
	const RoundRect card{ rect_.pos + shift, rect_.size, 12 };
	card.draw(fill);
	card.drawFrame(0.0, hover && ready ? 4.0 : 2.5, frame);

	constexpr double iconSize = 52.0;
	const double iconScale = (icon_.width() > 0) ? (iconSize / icon_.width()) : 1.0;
	const double iconW = icon_.width() * iconScale;
	icon_.scaled(iconScale).mirrored().draw(
		rect_.center().x - iconW / 2.0 + shift.x,
		rect_.y + 10.0 + shift.y);

	const ColorF text = ready ? ColorF{ 0.08, 0.14, 0.22 } : ColorF{ 0.24, 0.27, 0.31 };
	font_(stats_.name).drawAt(18, rect_.center() + shift + Vec2{ 0.0, 16.0 }, text);
	font_(U"cost:{}"_fmt(stats_.cost)).drawAt(15, rect_.center() + shift + Vec2{ 0.0, 38.0 }, text);

	if (cooling && stats_.cooldown > 0.0)
	{
		const double ratio = std::clamp(1.0 - cooldown_ / stats_.cooldown, 0.0, 1.0);
		RectF{ rect_.x + 12.0, rect_.y + rect_.h - 14.0, (rect_.w - 24.0) * ratio, 5.0 }.rounded(2).draw(ColorF{ 0.86, 0.46, 0.16 });
		font_(U"{:.1f}"_fmt(cooldown_)).drawAt(15, rect_.center() + shift + Vec2{ 0.0, 56.0 }, Palette::Darkred);
	}
	else if (!affordable)
	{
		font_(U"不足").drawAt(15, rect_.center() + shift + Vec2{ 0.0, 56.0 }, Palette::Darkred);
	}
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
