#pragma once
#include "../GameManager.h"
#include "UnitStats.h"

/// 画面端の拠点。HP を表示し、艦は前面より先へ進まない。
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
};
