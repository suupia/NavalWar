#pragma once

/// 開幕の所持金、拠点 HP、所持金の増加量。
namespace BattleBalance
{
	inline constexpr double StartingMoney = 180.0;
	inline constexpr double IncomePerSecond = 18.0;
	inline constexpr double PlayerBaseHp = 3000.0;
	inline constexpr double EnemyBaseHp = 5000.0;
	inline constexpr double IncomeUpgradeBonus = 6.0;
	inline constexpr int IncomeUpgradeBaseCost = 100;
	inline constexpr int IncomeUpgradeMaxLevel = 8;
}
