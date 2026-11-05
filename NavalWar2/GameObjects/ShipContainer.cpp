#include "../stdafx.h"
#include "ShipContainer.h"
#include "Lane.h"

ShipContainer::ShipContainer(GameManager& gm, RectF rect, const Font& font, int index, Base& playerBase, Base& enemyBase)
	: gm_(gm)
	, rect_(rect)
	, font_(font)
	, index_(index)
	, playerBase_(playerBase)
	, enemyBase_(enemyBase)
{
	logicId_ = gm_.registerLogic([this]() { this->UpdateLogic(); });
	renderId_ = gm_.registerRender([this]() { this->UpdateRender(); });
}

ShipContainer::~ShipContainer()
{
	Print << U"Destruct ShipContainer";
	gm_.unregisterLogic(logicId_);
	gm_.unregisterRender(renderId_);
}

void ShipContainer::UpdateLogic()
{
	for (const auto& ship : ships_)
	{
		ship->UpdateLogic();
		const double limit = (ship->GetFaction() == Faction::Player)
			? enemyBase_.FrontX()
			: playerBase_.FrontX();
		ship->ClampToFront(limit);
	}
}

void ShipContainer::UpdateRender()
{
	const double y = Lane::WaterlineY();
	RectF{ rect_.x, y - 40.0, rect_.w, 40.0 }.draw(ColorF{ 0.08, 0.22, 0.4, 0.45 });
	for (const auto& ship : ships_)
	{
		ship->UpdateRender();
	}
}

void ShipContainer::AddShip(Faction faction, const UnitStats& stats)
{
	const double y = Lane::WaterlineY();
	const double half = Lane::UnitWidth / 2.0;
	const double x = (faction == Faction::Player)
		? (playerBase_.FrontX() + half)
		: (enemyBase_.FrontX() - half);
	ships_.push_back(std::make_unique<Ship>(faction, stats, x, y));
}
