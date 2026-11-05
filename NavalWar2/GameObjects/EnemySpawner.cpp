#include "../stdafx.h"
#include "EnemySpawner.h"
#include "ShipContainer.h"
#include "UnitCatalog.h"
#include <algorithm>

EnemySpawner::EnemySpawner(GameManager& gm, ShipContainer& ships)
	: gm_(gm)
	, ships_(ships)
	, timer_(0.0)
	, step_(0)
{
	logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
}

EnemySpawner::~EnemySpawner()
{
	gm_.unregisterLogic(logicId_);
}

void EnemySpawner::UpdateLogic()
{
	const std::vector<EnemySpawn>& schedule = EnemySchedule();
	const std::vector<UnitStats>& types = EnemyUnitTypes();
	if (schedule.empty() || types.empty())
	{
		return;
	}

	timer_ += Scene::DeltaTime();
	const EnemySpawn& spawn = schedule[step_ % schedule.size()];
	if (timer_ < spawn.interval)
	{
		return;
	}

	timer_ = 0.0;
	const int last = static_cast<int>(types.size()) - 1;
	const int typeIndex = std::clamp(spawn.typeIndex, 0, last);
	ships_.AddShip(Faction::Enemy, types[static_cast<size_t>(typeIndex)]);
	step_ = (step_ + 1) % schedule.size();
}

void EnemySpawner::Reset()
{
	timer_ = 0.0;
	step_ = 0;
}
