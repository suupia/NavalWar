#include "../stdafx.h"
#include "SortieButton.h"
#include "Ship.h"
#include "../Font/FontSize.h"

void SortieButton::UpdateLogic()
 {
	if(rect_.leftClicked())
	{
		Print << U"Button Logic index{}"_fmt(index_);
		//Ship(gm_, Vec2{0, 3.0/5.0 * Scene::Height()});
		// ships_.push_back(std::make_unique<Ship>(gm_, Vec2{0, 2.0/5.0 * Scene::Height()}));  // 単体だとバグる。Clickにもあるとなぜが動く
		// std::make_unique<Ship>(gm_, Vec2{0, 2.0/5.0 * Scene::Height()}); // バグる
		// Ship(gm_, Vec2{0, 2.0/5.0 * Scene::Height()}); // バグる
		// 生存期間が問題っぽい。たぶん、デストラクタが呼ばれて何かが消えているのだと思う。
	}
 }
void SortieButton::UpdateRender()
{
	rect_.draw();
	font_(U"index:{}"_fmt(index_)).draw(FontSize::GetFontSize(0), rect_.x , rect_.y , Palette::Black);
	font_(U"cost:{}"_fmt(100)).draw(FontSize::GetFontSize(0), rect_.x , rect_.y + 30 , Palette::Black);

}
void SortieButton::Click()
{
	// Print << U"Button Logic index{}"_fmt(index_);
	if(rect_.leftClicked())
	{
		Print << U"Clicked index{}"_fmt(index_) ;
		// ships_.push_back(std::make_unique<Ship>(gm_, Vec2{0, 3.0/5.0 * Scene::Height()}));
		shipContainer_.AddShip(std::make_unique<Ship>(gm_, Vec2{0, 3.0/5.0 * Scene::Height()}));
		//std::make_unique<Ship>(gm_, Vec2{0, 3.0/5.0 * Scene::Height()});
	}
}
