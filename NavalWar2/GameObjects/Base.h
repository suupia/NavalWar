#pragma once
#include "../GameManager.h"
#include "UnitStats.h"

/// 画面端の拠点。HP を持ち、射程内の艦から攻撃を受ける。
class Base
{
private:
	GameManager& gm_;
	const Font& font_;
	Faction faction_;
	double maxHp_;
	double hp_;
	int renderId_;

public:
	Base(GameManager& gm, const Font& font, Faction faction, double maxHp);
	~Base();

	Base(const Base&) = delete;
	Base& operator=(const Base&) = delete;

	void UpdateRender() const;
	Faction GetFaction() const { return faction_; }
	double GetHp() const { return hp_; }
	double GetMaxHp() const { return maxHp_; }
	double FrontX() const;
	void Damage(double amount);
	void Reset();
};
