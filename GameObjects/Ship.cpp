#include "../stdafx.h"
#include "Ship.h"

void Ship::UpdateLogic()
{
	pos_.x += speed_ * Scene::DeltaTime();
}

void Ship::UpdateRender()
{
	texture_.draw(Arg::bottomCenter(pos_));
}
