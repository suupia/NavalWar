#include "../stdafx.h"
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
void Button::UpdateLogic()
 {
	// Print << U"Button Logic index{}"_fmt(index_);
 }
void Button::UpdateRender()
{
	font_(index_).draw(30, rect_.x , rect_.y , Palette::Black);
	// Print << U"Drawing button with index: " << index_;
}
