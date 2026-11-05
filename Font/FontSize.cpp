#include "../stdafx.h"
#include "FontSize.h"

// Change this value when you had changed resolution
int FontSize::GetFontSize(int key)
{
	switch (key)
	{
		case 0:
			return 20;
		case 1:
			return 30;
		case 2:
			return 40;
		default:
			Print << U"Error: FontSize::GetFontSize key is not 0, 1 or 2";
			return 20;
	}
}
