#include "../stdafx.h"
#include "ShipContainer.h"
#include "Lane.h"
#include <algorithm>
#include <limits>

ShipContainer::ShipContainer(GameManager& gm, RectF rect, const Font& font, int index, Base& playerBase, Base& enemyBase)
	: gm_(gm)
	, rect_(rect)
	, font_(font)
	, index_(index)
	, playerBase_(playerBase)
	, enemyBase_(enemyBase)
{
	logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
	renderId_ = gm_.registerRender([this]() { this->UpdateRender(); });
}

ShipContainer::~ShipContainer()
{
	Print << U"Destruct ShipContainer";
	gm_.unregisterLogic(logicId_);
	gm_.unregisterRender(renderId_);
}

void ShipContainer::UpdateLogic()
{
	const double dt = Scene::DeltaTime();
	const size_t count = ships_.size();
	std::vector<double> pending(count, 0.0);
	double playerBaseDamage = 0.0;
	double enemyBaseDamage = 0.0;

	for (size_t i = 0; i < count; ++i)
	{
		Ship& ship = *ships_[i];
		if (!ship.IsAlive())
		{
			continue;
		}

		double bestGap = std::numeric_limits<double>::infinity();
		size_t target = count;
		for (size_t j = 0; j < count; ++j)
		{
			if (i == j || !ships_[j]->IsAlive() || ships_[j]->GetFaction() == ship.GetFaction())
			{
				continue;
			}
			const double gap = ship.GapToFront(ships_[j]->FrontX());
			if (gap < -1.0 || gap >= bestGap)
			{
				continue;
			}
			bestGap = gap;
			target = j;
		}

		const Base& opposingBase = (ship.GetFaction() == Faction::Player) ? enemyBase_ : playerBase_;
		const double baseGap = ship.GapToFront(opposingBase.FrontX());
		const bool attackBase = baseGap < bestGap;
		if (attackBase)
		{
			bestGap = baseGap;
		}

		if (bestGap <= ship.GetRange())
		{
			if (ship.TryFire(dt))
			{
				if (attackBase)
				{
					if (ship.GetFaction() == Faction::Player)
					{
						enemyBaseDamage += ship.GetAttack();
					}
					else
					{
						playerBaseDamage += ship.GetAttack();
					}
				}
				else if (target < count)
				{
					pending[target] += ship.GetAttack();
				}
			}
		}
		else
		{
			const double step = std::min(ship.GetSpeed() * dt, bestGap - ship.GetRange());
			ship.MoveForward(step);
		}

		const double limit = (ship.GetFaction() == Faction::Player)
			? enemyBase_.FrontX()
			: playerBase_.FrontX();
		ship.ClampToFront(limit);
	}

	for (size_t i = 0; i < count; ++i)
	{
		ships_[i]->Damage(pending[i]);
	}
	playerBase_.Damage(playerBaseDamage);
	enemyBase_.Damage(enemyBaseDamage);

	std::erase_if(ships_, [](const std::unique_ptr<Ship>& ship) { return !ship->IsAlive(); });
}

void ShipContainer::UpdateRender()
{
	const double y = Lane::WaterlineY();
	RectF{ rect_.x, y - 40.0, rect_.w, 40.0 }.draw(ColorF{ 0.08, 0.22, 0.4, 0.45 });
	for (const auto& ship : ships_)
	{
		ship->UpdateRender();
	}
}

void ShipContainer::AddShip(Faction faction, const UnitStats& stats)
{
	const double y = Lane::WaterlineY();
	const double half = Lane::UnitWidth / 2.0;
	const double x = (faction == Faction::Player)
		? (playerBase_.FrontX() + half)
		: (enemyBase_.FrontX() - half);
	ships_.push_back(std::make_unique<Ship>(faction, stats, x, y));
}
