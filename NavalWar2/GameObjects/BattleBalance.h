#pragma once

/// 開幕の所持金、拠点 HP、所持金の増加量。
namespace BattleBalance
{
	inline constexpr double StartingMoney = 150.0;
	inline constexpr double IncomePerSecond = 16.0;
	inline constexpr double PlayerBaseHp = 2800.0;
	inline constexpr double EnemyBaseHp = 4800.0;
	inline constexpr double IncomeUpgradeBonus = 6.0;
	inline constexpr int IncomeUpgradeBaseCost = 100;
	inline constexpr int IncomeUpgradeMaxLevel = 8;
}
