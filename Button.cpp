#include "stdafx.h"
#include "Button.h"
#include "Ship.h"

void Button::Click()
{
	rect_.draw();
	if(rect_.leftClicked())
	{
		Print << U"Clicked index{}"_fmt(index_) ;
		// Ship ship(gm_, Vec2{0,3.0/5.0 * Scene::Height()});
		ships_.push_back(std::make_unique<Ship>(gm_, Vec2{0, 3.0/5.0 * Scene::Height()}));
	}
}
