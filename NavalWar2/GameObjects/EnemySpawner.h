#pragma once
#include "../GameManager.h"
#include "UnitStats.h"

class ShipContainer;

/// 一定間隔で敵艦を敵拠点の前から出す。
class EnemySpawner
{
private:
	GameManager& gm_;
	ShipContainer& ships_;
	UnitStats stats_;
	double interval_;
	double timer_;
	int logicId_;

public:
	EnemySpawner(GameManager& gm, ShipContainer& ships, const UnitStats& stats, double interval);
	~EnemySpawner();

	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner& operator=(const EnemySpawner&) = delete;

	void UpdateLogic();
};
