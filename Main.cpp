# include <Siv3D.hpp> // OpenSiv3D v0.6.11


#include "GameObjects/Ship.h"
#include "GameManager.h"
#include "GameObjects/Button.h"
#include "GameObjects/Currency.h"


void Main()
{
	constexpr  int windowWidth = 1920;
	constexpr  int windowHeight = 1080;
	if(windowWidth * 9 != windowHeight * 16)
	{
		throw Error(U"You should set the resolution to 16:9");
	}
	Window::Resize(windowWidth, windowHeight);
	Window::SetStyle(WindowStyle::Sizable);

	Scene::SetBackground(Palette::Lightblue);

	GameManager gm;

	// Font
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// Currency
	Currency currency(gm, font, 0, 1.0);

	// place buttons
	std::vector<std::unique_ptr<Button>> buttons;
	int columNum = 4;
	int rowNum = 2;
	double width =3.0 / 5.0 * Scene::Width()  / columNum;
	double widthBody = 8.0 /10.0 * width;
	double widthMargin = 2.0 / 10.0 * width / 2.0;
	double height = 2.0 / 5.0 * Scene::Height()  / rowNum;
	double heightBody = 8.0 /10.0 * height;
	double heightMargin = 2.0 / 10.0 * height /2.0;
	int offsetx = 0;
	int offsety = 3.0/5.0 * Scene::Height();
	for(int i = 0; i< rowNum; i++)
	{
		for(int j = 0; j< columNum; j++)
		{
			auto rect = RectF{offsetx + (widthMargin + widthBody + widthMargin) * j,   offsety+ heightMargin + (heightMargin+ heightBody + heightMargin) * i, widthBody, heightBody};
			buttons.push_back(std::make_unique<Button>(gm,rect,font, j + i * columNum));
		}
	}

	while (System::Update())
	{
		// 長方形を描く
		RectF{ 0,  3.0 /5.0 * Scene::Height(), Scene::Width(), 2.0 /5.0 * Scene::Height() }.draw(Palette::Lightslategray);

		for(auto& button : buttons)
		{
			button ->Click();
		}

		gm.updateLogic();
		gm.updateRender();

	}
}

