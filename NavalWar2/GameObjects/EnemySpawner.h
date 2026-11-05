#pragma once
#include "../GameManager.h"

class ShipContainer;

/// スケジュールに沿って敵艦を敵拠点の前から出す。
class EnemySpawner
{
private:
	GameManager& gm_;
	ShipContainer& ships_;
	double timer_;
	size_t step_;
	int logicId_;

public:
	EnemySpawner(GameManager& gm, ShipContainer& ships);
	~EnemySpawner();

	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner& operator=(const EnemySpawner&) = delete;

	void UpdateLogic();
	void Reset();
};
