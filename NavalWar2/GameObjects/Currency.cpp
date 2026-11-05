#include "../stdafx.h"
#include "Currency.h"

void Currency::UpdateLogic()
{
	amount_ += amountPerSecond_ * Scene::DeltaTime();
}
void Currency::UpdateRender()
{
	font_(U"{:.0f}  +{:.0f}/s"_fmt(amount_, amountPerSecond_)).draw(28, 24, 16, Palette::Black);
}

void Currency::Reset(double amount, double amountPerSecond)
{
	amount_ = amount;
	amountPerSecond_ = amountPerSecond;
}
