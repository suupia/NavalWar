#include "../stdafx.h"
#include "FontSize.h"

// Change this value when you had changed resolution
 int FontSize::GetFontSize(int key)
{
	switch (key)
	{
		case 0:
			return 20;
			break;
		case 1:
			return 30;
			break;
		case 2:
			return 40;
			break;
		default:
			return 20;
			Print << U"Error: FontSize::GetFontSize(int key) key is not 0, 1 or 2";
			break;
	}
}
