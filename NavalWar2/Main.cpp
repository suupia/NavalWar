# include <Siv3D.hpp> // Siv3D v0.6.16

#include "GameManager.h"
#include "GameObjects/SortieButton.h"
#include "GameObjects/Currency.h"
#include "GameObjects/ShipContainer.h"

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
	Currency currency(gm, font, 0, 1.0);
	ShipContainer shipContainer(gm, RectF{ 0, 0, Scene::Width(), shipAreaRatio * Scene::Height() }, font, 0);

	const double cellWidth = shipAreaRatio * Scene::Width() / columnCount;
	const double cellHeight = buttonAreaRatio * Scene::Height() / rowCount;
	const double buttonWidth = buttonFill * cellWidth;
	const double buttonHeight = buttonFill * cellHeight;
	const double marginX = (2.0 / 10.0) * cellWidth / 2.0;
	const double marginY = (2.0 / 10.0) * cellHeight / 2.0;
	const double buttonsTop = shipAreaRatio * Scene::Height();

	std::vector<std::unique_ptr<SortieButton>> buttons;
	for (int row = 0; row < rowCount; ++row)
	{
		for (int column = 0; column < columnCount; ++column)
		{
			const RectF rect{
				(marginX + buttonWidth + marginX) * column,
				buttonsTop + marginY + (marginY + buttonHeight + marginY) * row,
				buttonWidth,
				buttonHeight };
			buttons.push_back(std::make_unique<SortieButton>(
				gm, shipContainer, currency, rect, font, column + row * columnCount));
		}
	}

	while (System::Update())
	{
		RectF{ 0, buttonsTop, Scene::Width(), buttonAreaRatio * Scene::Height() }.draw(Palette::Lightslategray);

		for (auto& button : buttons)
		{
			button->Click();
		}

		gm.updateLogic();
		gm.updateRender();
	}
}
