#pragma once
#include <memory>
#include <vector>
#include "Base.h"
#include "Ship.h"

/// 味方と敵の艦を一度だけ進め、射程内なら攻撃させる。
class ShipContainer
{
private:
	GameManager& gm_;
	RectF rect_;
	const Font& font_;
	int index_;
	Base& playerBase_;
	Base& enemyBase_;
	int logicId_;
	int renderId_;
	std::vector<std::unique_ptr<Ship>> ships_;

public:
	ShipContainer(GameManager& gm, RectF rect, const Font& font, int index, Base& playerBase, Base& enemyBase);
	~ShipContainer();

	ShipContainer(const ShipContainer&) = delete;
	ShipContainer& operator=(const ShipContainer&) = delete;

	void UpdateLogic();
	void UpdateRender();
	void AddShip(Faction faction, const UnitStats& stats);
};
