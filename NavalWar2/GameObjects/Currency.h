#pragma once
#include "../GameManager.h"
#include "GameObject.h"

/// 時間経過で増え、出撃時に消費される所持金。
class Currency
{
private:
	GameManager& gm_;
	const Font& font_;
	double amount_;
	double amountPerSecond_;
	int logicId_;
	int renderId_;

public:
	Currency(GameManager& gm, const Font& font, double amount, double amountPerSecond)
		: gm_(gm), font_(font), amount_(amount), amountPerSecond_(amountPerSecond)
	{
		logicId_ = gm_.registerLogic([&]() { this->UpdateLogic(); });
		renderId_ = gm_.registerRender([&]() { this->UpdateRender(); });
	}

	~Currency()
	{
		gm_.unregisterLogic(logicId_);
		gm_.unregisterRender(renderId_);
	}

	void UpdateLogic();
	void UpdateRender();
	double GetAmount() const { return amount_; }
	double GetAmountPerSecond() const { return amountPerSecond_; }
	double SetAmount(double amount) { return amount_ = amount; }
	void AddAmount(double amount) { amount_ += amount; }
	void AddAmountPerSecond(double amount) { amountPerSecond_ += amount; }
	void Reset(double amount, double amountPerSecond);
};
