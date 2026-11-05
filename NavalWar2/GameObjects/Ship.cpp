#include "../stdafx.h"
#include "Ship.h"
#include "Lane.h"
#include <algorithm>

Ship::Ship(Faction faction, const UnitStats& stats, double x, double y)
	: faction_(faction)
	, stats_(stats)
	, texture_(Emoji{ stats.emoji })
	, pos_(x, y)
	, hp_(stats.maxHp)
{
}

void Ship::UpdateLogic()
{
	const double direction = (faction_ == Faction::Player) ? 1.0 : -1.0;
	pos_.x += direction * stats_.speed * Scene::DeltaTime();
}

void Ship::UpdateRender()
{
	const ColorF hull = (faction_ == Faction::Player)
		? ColorF{ 0.25, 0.55, 0.95 }
		: ColorF{ 0.9, 0.32, 0.25 };
	Circle{ pos_.x, pos_.y - 30, 18 }.draw(hull);
	texture_.draw(Arg::bottomCenter(pos_));

	const double ratio = (stats_.maxHp <= 0.0) ? 0.0 : std::clamp(hp_ / stats_.maxHp, 0.0, 1.0);
	constexpr double barWidth = 48.0;
	const double iconHeight = std::max<double>(texture_.height(), 64.0);
	const Vec2 barPos{ pos_.x - barWidth / 2.0, pos_.y - iconHeight - 10.0 };
	RectF{ barPos, barWidth, 6 }.draw(ColorF{ 0.15 });
	RectF{ barPos, barWidth * ratio, 6 }.draw(
		faction_ == Faction::Player ? Palette::Deepskyblue : Palette::Orange);
}

double Ship::FrontX() const
{
	const double half = Lane::UnitWidth / 2.0;
	return (faction_ == Faction::Player) ? (pos_.x + half) : (pos_.x - half);
}

void Ship::ClampToFront(double limit)
{
	if (faction_ == Faction::Player)
	{
		const double over = FrontX() - limit;
		if (over > 0.0)
		{
			pos_.x -= over;
		}
	}
	else
	{
		const double over = limit - FrontX();
		if (over > 0.0)
		{
			pos_.x += over;
		}
	}
}
