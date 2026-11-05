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
	, attackTimer_(0.0)
	, flash_(0.0)
{
}

void Ship::UpdateLogic()
{
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

	if (flash_ > 0.0)
	{
		Circle{ FrontX(), pos_.y - 36.0, 8 }.draw(Palette::Yellow);
		flash_ = std::max(0.0, flash_ - Scene::DeltaTime());
	}
}

double Ship::FrontX() const
{
	const double half = Lane::UnitWidth / 2.0;
	return (faction_ == Faction::Player) ? (pos_.x + half) : (pos_.x - half);
}

double Ship::GapToFront(double frontX) const
{
	return (faction_ == Faction::Player) ? (frontX - FrontX()) : (FrontX() - frontX);
}

void Ship::MoveForward(double distance)
{
	if (distance <= 0.0)
	{
		return;
	}
	pos_.x += (faction_ == Faction::Player) ? distance : -distance;
}

bool Ship::TryFire(double dt)
{
	attackTimer_ -= dt;
	if (attackTimer_ > 0.0)
	{
		return false;
	}
	attackTimer_ += stats_.attackInterval;
	if (attackTimer_ < 0.0)
	{
		attackTimer_ = stats_.attackInterval;
	}
	flash_ = 0.12;
	return true;
}

void Ship::Damage(double amount)
{
	if (amount <= 0.0)
	{
		return;
	}
	hp_ = std::max(0.0, hp_ - amount);
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
