#include "GameTimer.h"



GameTimer::GameTimer()
{
	timeValue = "";
	r = 0; g = 0; b = 0;
	borderColor = { 255, 255, 255 };
}

void GameTimer::SetTime(float time)
{
	int roundedTime = (int)(round(time));
	timeValue = to_string(roundedTime);
}

void GameTimer::Render()
{
	CustomWindow::Render();

	int timeText_W, timeText_H;
	GetTextWidthHeight(pixelFont_Small, timeValue, timeText_W, timeText_H);

	Text(pixelFont_Small, { 255, 255, 255 }, timeValue, Transform.x + ( Transform.w - timeText_W) / 2, Transform.y + (Transform.h - timeText_H) / 2);
}

GameTimer::~GameTimer()
{
}