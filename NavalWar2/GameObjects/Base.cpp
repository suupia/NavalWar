#include "../stdafx.h"
#include "Base.h"
#include "Lane.h"
#include <algorithm>

Base::Base(GameManager& gm, const Font& font, Faction faction, double maxHp)
	: gm_(gm)
	, font_(font)
	, faction_(faction)
	, maxHp_(maxHp)
	, hp_(maxHp)
{
	renderId_ = gm_.registerRender([this]() { this->UpdateRender(); });
}

Base::~Base()
{
	gm_.unregisterRender(renderId_);
}

void Base::UpdateRender() const
{
	const double top = Lane::WaterlineY() - 180.0;
	const double x = (faction_ == Faction::Player) ? 0.0 : (Scene::Width() - Lane::BaseWidth);
	const RectF body{ x, top, Lane::BaseWidth, 180.0 };
	body.draw(faction_ == Faction::Player ? ColorF{ 0.18, 0.42, 0.82 } : ColorF{ 0.72, 0.22, 0.2 });
	body.drawFrame(4, Palette::White);

	const double ratio = (maxHp_ <= 0.0) ? 0.0 : std::clamp(hp_ / maxHp_, 0.0, 1.0);
	const RectF bar{ x + 12, top - 20, Lane::BaseWidth - 24, 12 };
	bar.draw(ColorF{ 0.15 });
	RectF{ bar.pos, bar.w * ratio, bar.h }.draw(Palette::Limegreen);

	const String label = (faction_ == Faction::Player) ? U"味方拠点" : U"敵拠点";
	font_(label).draw(22, x + 16, top + 16, Palette::White);
	font_(U"HP {:.0f}"_fmt(hp_)).draw(22, x + 16, top + 48, Palette::White);
}

double Base::FrontX() const
{
	return (faction_ == Faction::Player) ? Lane::PlayerFrontX() : Lane::EnemyFrontX();
}

void Base::Damage(double amount)
{
	if (amount <= 0.0)
	{
		return;
	}
	hp_ = std::max(0.0, hp_ - amount);
}
