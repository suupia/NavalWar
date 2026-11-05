#pragma once

/// プレイヤーは左から右、敵は右から左へ進む。
enum class Faction
{
	Player,
	Enemy,
};

/// 艦の性能。攻撃の数値は戦闘を入れる段階で使う。
struct UnitStats
{
	String name;
	String emoji;
	int cost;
	double cooldown;
	double maxHp;
	double attack;
	double range;
	double attackInterval;
	double speed;
};

/// ボタンがまだ 1 種類だけのときの艦性能。
inline UnitStats DefaultShipStats()
{
	return UnitStats{
		U"艦",
		U"🚢",
		5,
		0.0,
		120.0,
		15.0,
		160.0,
		1.0,
		100.0,
	};
}
