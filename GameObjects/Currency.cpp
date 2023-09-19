#include "../stdafx.h"
#include "Currency.h"

void Currency::UpdateLogic()
{
	amount_ += amountPerSecond_ * Scene::DeltaTime();
}
void  Currency::UpdateRender()
{
	font_(U"{:.1f}"_fmt(amount_)).draw(30, 3.0 / 5.0 * Scene::Width() , 3.0 / 5.0 * Scene::Height(), Palette::Black);

}
