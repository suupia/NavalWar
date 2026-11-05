#pragma once
#include "UnitStats.h"
#include <vector>

/// 敵の出現 1 回。interval 秒後に typeIndex の艦を出す。
struct EnemySpawn
{
	double interval;
	int typeIndex;
};

/// 出撃ボタンに並ぶ味方艦。
inline const std::vector<UnitStats>& PlayerUnitTypes()
{
	static const std::vector<UnitStats> types{
		{ U"魚雷艇", U"🚤", 45, 1.5, 80, 10, 130, 0.60, 165 },
		{ U"駆逐艦", U"⛵", 100, 3.0, 200, 20, 180, 0.95, 105 },
		{ U"巡洋艦", U"🚢", 190, 5.0, 380, 36, 220, 1.25, 70 },
		{ U"戦艦", U"⛴️", 360, 8.5, 860, 72, 240, 1.85, 38 },
		{ U"空母", U"🛳️", 420, 11.0, 480, 50, 430, 2.20, 44 },
		{ U"潜水艦", U"🦈", 160, 4.0, 110, 48, 155, 1.40, 135 },
		{ U"護衛艦", U"🛟", 130, 3.5, 600, 8, 115, 1.15, 48 },
	};
	return types;
}

/// 時間差で出現する敵艦。
inline const std::vector<UnitStats>& EnemyUnitTypes()
{
	static const std::vector<UnitStats> types{
		{ U"魚雷艇", U"🚤", 0, 0.0, 60, 11, 120, 0.65, 115 },
		{ U"駆逐艦", U"⛵", 0, 0.0, 170, 18, 165, 1.00, 78 },
		{ U"巡洋艦", U"🚢", 0, 0.0, 340, 30, 200, 1.35, 52 },
		{ U"戦艦", U"⛴️", 0, 0.0, 740, 58, 220, 2.00, 30 },
	};
	return types;
}

/// 繰り返す敵の出現順。
inline const std::vector<EnemySpawn>& EnemySchedule()
{
	static const std::vector<EnemySpawn> schedule{
		{ 4.0, 0 },
		{ 3.5, 0 },
		{ 5.0, 1 },
		{ 3.5, 0 },
		{ 6.5, 1 },
		{ 9.0, 2 },
		{ 3.5, 0 },
		{ 5.5, 1 },
		{ 14.0, 3 },
	};
	return schedule;
}
