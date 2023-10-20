#include "../stdafx.h"
#include "ShipContainer.h"

void ShipContainer::UpdateLogic()
{
	for(const auto ship : ships_)
	{
		ship->UpdateLogic();
	}
}
void ShipContainer::UpdateRender()
{
	for(const auto ship : ships_)
	{
		ship->UpdateRender();
	}
}
