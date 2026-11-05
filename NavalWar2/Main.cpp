# include <Siv3D.hpp> // Siv3D v0.6.16

#include "GameManager.h"
#include "GameObjects/Base.h"
#include "GameObjects/BattleBalance.h"
#include "GameObjects/Currency.h"
#include "GameObjects/EnemySpawner.h"
#include "GameObjects/IncomeButton.h"
#include "GameObjects/ShipContainer.h"
#include "GameObjects/SortieButton.h"
#include "GameObjects/UnitCatalog.h"

void Main()
{
	constexpr int windowWidth = 1920;
	constexpr int windowHeight = 1080;
	constexpr double shipAreaRatio = 3.0 / 5.0;
	constexpr double buttonAreaRatio = 2.0 / 5.0;
	constexpr int columnCount = 4;
	constexpr int rowCount = 2;
	constexpr double buttonFill = 8.0 / 10.0;

	if constexpr (windowWidth * 9 != windowHeight * 16)
	{
		throw Error(U"You should set the resolution to 16:9");
	}
	Window::Resize(windowWidth, windowHeight);
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetBackground(Palette::Lightblue);

	GameManager gm;
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
	Currency currency(gm, font, BattleBalance::StartingMoney, BattleBalance::IncomePerSecond);
	Base playerBase(gm, font, Faction::Player, BattleBalance::PlayerBaseHp);
	Base enemyBase(gm, font, Faction::Enemy, BattleBalance::EnemyBaseHp);
	ShipContainer shipContainer(
		gm,
		RectF{ 0, 0, Scene::Width(), shipAreaRatio * Scene::Height() },
		font,
		0,
		playerBase,
		enemyBase);
	EnemySpawner enemySpawner(gm, shipContainer);

	const double cellWidth = shipAreaRatio * Scene::Width() / columnCount;
	const double cellHeight = buttonAreaRatio * Scene::Height() / rowCount;
	const double buttonWidth = buttonFill * cellWidth;
	const double buttonHeight = buttonFill * cellHeight;
	const double marginX = (2.0 / 10.0) * cellWidth / 2.0;
	const double marginY = (2.0 / 10.0) * cellHeight / 2.0;
	const double buttonsTop = shipAreaRatio * Scene::Height();
	const std::vector<UnitStats>& unitTypes = PlayerUnitTypes();

	std::vector<std::unique_ptr<SortieButton>> buttons;
	std::unique_ptr<IncomeButton> income;
	int slot = 0;
	for (int row = 0; row < rowCount; ++row)
	{
		for (int column = 0; column < columnCount; ++column)
		{
			const RectF rect{
				(marginX + buttonWidth + marginX) * column,
				buttonsTop + marginY + (marginY + buttonHeight + marginY) * row,
				buttonWidth,
				buttonHeight };
			if (slot < static_cast<int>(unitTypes.size()))
			{
				buttons.push_back(std::make_unique<SortieButton>(
					gm, shipContainer, currency, rect, font, unitTypes[slot]));
			}
			else if (!income)
			{
				income = std::make_unique<IncomeButton>(gm, currency, rect, font);
			}
			++slot;
		}
	}

	while (System::Update())
	{
		RectF{ 0, buttonsTop, Scene::Width(), buttonAreaRatio * Scene::Height() }.draw(Palette::Lightslategray);

		for (auto& button : buttons)
		{
			button->Click();
		}
		if (income)
		{
			income->Click();
		}

		gm.updateLogic();
		gm.updateRender();
	}
}
