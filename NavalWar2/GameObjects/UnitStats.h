#pragma once

/// プレイヤーは左から右、敵は右から左へ進む。
enum class Faction
{
	Player,
	Enemy,
};

/// 艦の性能。コストとクールダウンは出撃ボタンが使う。
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
