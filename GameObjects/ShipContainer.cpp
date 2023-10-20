#include "../stdafx.h"
#include "ShipContainer.h"

void ShipContainer::UpdateLogic()
{
	for(const auto& ship : ships_)
	{
		ship->UpdateLogic();
	}
}
void ShipContainer::UpdateRender()
{
	for(const auto& ship : ships_)
	{
		ship->UpdateRender();
	}
}

void ShipContainer::AddShip(std::unique_ptr<Ship> ship)
{
	ships_.push_back(std::move(ship));
	for(const auto& ship : ships_)
	{
		ship->UpdateRender();
	}
}
