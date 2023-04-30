#include "WinLoseWindow.h"


WinLoseWindow::WinLoseWindow(string _message, Button& button) :
	nextActButton(0, 0, 0, 0, "", ""),
	message(pixelFont_Med)
{
	message.SetContent(_message);
	nextActButton = button;
}

void WinLoseWindow::Render()
{
	CustomWindow::Render();
	int tW, tH;
	tW = message.Transform.w;
	tH = message.Transform.h;
	int headSpacing = 50;
	message.SetPosition(Transform.x + (Transform.w - tW) / 2, Transform.y + headSpacing);
	message.Render();
	nextActButton.RenderButton(pixelFont_Small);
}

WinLoseWindow::~WinLoseWindow()
{
}