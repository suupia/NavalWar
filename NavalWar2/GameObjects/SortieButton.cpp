#include "../stdafx.h"
#include "SortieButton.h"
#include "../Font/FontSize.h"
#include "UnitStats.h"

void SortieButton::UpdateLogic()
{
	if (rect_.leftClicked())
	{
		Print << U"Button Logic index{}"_fmt(index_);
	}
}
void SortieButton::UpdateRender()
{
	rect_.draw();
	const int cost = DefaultShipStats().cost;
	font_(U"index:{}"_fmt(index_)).draw(FontSize::GetFontSize(0), rect_.x , rect_.y , Palette::Black);
	font_(U"cost:{}"_fmt(cost)).draw(FontSize::GetFontSize(0), rect_.x , rect_.y + 30 , Palette::Black);

}
void SortieButton::Click()
{
	if(rect_.leftClicked())
	{
		Print << U"Clicked index{}"_fmt(index_) ;
		const UnitStats stats = DefaultShipStats();
		if(currency_.GetAmount() < stats.cost)
		{
			Print << U"Not enough money";
			return;
		}
		shipContainer_.AddShip(Faction::Player, stats);
		currency_.AddAmount(-stats.cost);
	}
}
