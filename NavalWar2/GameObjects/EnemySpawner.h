#pragma once
#include "../GameManager.h"

class Match;
class ShipContainer;

/// スケジュールに沿って敵艦を敵拠点の前から出す。
class EnemySpawner
{
private:
	GameManager& gm_;
	ShipContainer& ships_;
	Match& match_;
	double timer_;
	size_t step_;
	int logicId_;

public:
	EnemySpawner(GameManager& gm, ShipContainer& ships, Match& match);
	~EnemySpawner();

	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner& operator=(const EnemySpawner&) = delete;

	void UpdateLogic();
	void Reset();
};
