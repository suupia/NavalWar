#include "../stdafx.h"
#include "EnemySpawner.h"
#include "ShipContainer.h"

EnemySpawner::EnemySpawner(GameManager& gm, ShipContainer& ships, const UnitStats& stats, double interval)
	: gm_(gm)
	, ships_(ships)
	, stats_(stats)
	, interval_(interval)
	, timer_(0.0)
{
	logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
}

EnemySpawner::~EnemySpawner()
{
	gm_.unregisterLogic(logicId_);
}

void EnemySpawner::UpdateLogic()
{
	timer_ += Scene::DeltaTime();
	if (timer_ < interval_)
	{
		return;
	}
	timer_ = 0.0;
	ships_.AddShip(Faction::Enemy, stats_);
}
