#include "button.h"
#include "main.h"
#include "sound.h"
#include "input.h"

static int g_ButtonSE = 0;

bool CheckIsOnButton(BUTTON* button)
{
	g_ButtonSE = LoadSound("data/SE/Button.wav");
	if (GetMousePosX() < button->pos.x + button->size.x / 2 &&
		GetMousePosX() > button->pos.x - button->size.x / 2 &&
		GetMousePosY() < button->pos.y + button->size.y / 2 &&
		GetMousePosY() > button->pos.y - button->size.y / 2)
	{
		if (IsMouseLeftTriggered())
		{
			PlaySound(g_ButtonSE, 0);
		}
		return true;
	}
	else
	{
		return false;
	}
}
