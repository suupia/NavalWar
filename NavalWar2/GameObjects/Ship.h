#pragma once
#include "GameObject.h"
#include "UnitStats.h"

/// レーンを進む艦。射程に入ると止まり、攻撃する。
class Ship : public GameObject
{
private:
	Faction faction_;
	UnitStats stats_;
	Texture texture_;
	Vec2 pos_;
	double hp_;
	double attackTimer_;
	double flash_;

public:
	Ship(Faction faction, const UnitStats& stats, double x, double y);

	void UpdateLogic() override;
	void UpdateRender() override;

	Faction GetFaction() const { return faction_; }
	double GetHp() const { return hp_; }
	double GetRange() const { return stats_.range; }
	double GetSpeed() const { return stats_.speed; }
	double GetAttack() const { return stats_.attack; }
	bool IsAlive() const { return hp_ > 0.0; }
	double FrontX() const;
	double GapToFront(double frontX) const;
	void MoveForward(double distance);
	void ClampToFront(double limit);
	bool TryFire(double dt);
	void Damage(double amount);
};
