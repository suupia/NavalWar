#pragma once
#include <memory>
#include "Ship.h"

/// 画面上部の領域に艦を保持し、まとめて更新・描画する。
class ShipContainer
{
private:
	GameManager& gm_;
	RectF rect_;
	const Font& font_;
	int index_;
	int logicId_;
	int renderId_;
	std::vector<std::unique_ptr<Ship>> ships_;

public:
	ShipContainer(GameManager& gm, RectF rect, const Font& font, int index)
		: gm_(gm), rect_(rect), font_(font), index_(index)
	{
		logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
		renderId_ = gm_.registerRender([this]() { this->UpdateRender(); });
	}

	~ShipContainer()
	{
		Print << U"Destruct ShipContainer";
		gm_.unregisterLogic(logicId_);
		gm_.unregisterRender(renderId_);
	}

	void UpdateLogic();
	void UpdateRender();
	void AddShip(std::unique_ptr<Ship> ship);

};
