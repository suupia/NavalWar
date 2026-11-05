#pragma once
#include "GameObject.h"
#include "UnitStats.h"

/// レーンを進む艦。自身ではコールバックを登録せず、ShipContainer が一度だけ更新する。
class Ship : public GameObject
{
private:
	Faction faction_;
	UnitStats stats_;
	Texture texture_;
	Vec2 pos_;
	double hp_;

public:
	Ship(Faction faction, const UnitStats& stats, double x, double y);

	void UpdateLogic() override;
	void UpdateRender() override;

	Faction GetFaction() const { return faction_; }
	double GetHp() const { return hp_; }
	double FrontX() const;
	void ClampToFront(double limit);
};
