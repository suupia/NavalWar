# include <Siv3D.hpp> // OpenSiv3D v0.6.11

#include "Ship.h"
#include "Button.h"


void Main()
{
	Window::Resize(1920, 1080);
	Window::SetStyle(WindowStyle::Sizable);

	Scene::SetBackground(Palette::Lightblue);

	GameManager gm;

	// place buttons
	Array<Button> buttons;
	int columNum = 4;
	int rowNum = 2;
	double width =(3.0 / 5.0 * Scene::Width()  / columNum );
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
			buttons.push_back(Button(gm,RectF{offsetx + (widthMargin + widthBody + widthMargin) * j,   offsety+ heightMargin + (heightMargin+ heightBody + heightMargin) * i, widthBody, heightBody}, j + i * columNum));
		}
	}



	Ship ship(gm,Vec2{0,3.0/5.0 * Scene::Height()});

	while (System::Update())
	{
		// 長方形を描く
		RectF{ 0,  3.0 /5.0 * Scene::Height(), Scene::Width(), 2.0 /5.0 * Scene::Height() }.draw(Palette::Lightslategray);

		for(auto& button : buttons)
		{
			button.Click();
		}

		gm.updateLogic();
		gm.updateRender();



	}
}

