#include "GameTimer.h"



GameTimer::GameTimer() :
	text(pixelFont_Small)
{
	timeValue = "";
	r = 0; g = 0; b = 0;
	borderColor = { 255, 255, 255 };
}

void GameTimer::SetTime(float time)
{
	int roundedTime = (int)(round(time));
	timeValue = to_string(roundedTime);
	text.SetContent(timeValue);
}

void GameTimer::Render()
{
	CustomWindow::Render();

	int timeText_W, timeText_H;

	timeText_W = text.Transform.w;
	timeText_H = text.Transform.h;

	text.SetPosition(Transform.x + (Transform.w - timeText_W) / 2, Transform.y + (Transform.h - timeText_H) / 2);
	text.Render();
}

GameTimer::~GameTimer()
{
}