#pragma once

/// 戦場の寸法。上側 3/5 の下端が航路で、拠点は左右の端に置く。
namespace Lane
{
	inline constexpr double BattleHeightRatio = 3.0 / 5.0;
	inline constexpr double BaseWidth = 150.0;
	inline constexpr double UnitWidth = 72.0;

	inline double WaterlineY()
	{
		return BattleHeightRatio * Scene::Height();
	}

	inline double PlayerFrontX()
	{
		return BaseWidth;
	}

	inline double EnemyFrontX()
	{
		return Scene::Width() - BaseWidth;
	}
}
