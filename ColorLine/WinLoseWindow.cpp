#include "WinLoseWindow.h"


WinLoseWindow::WinLoseWindow(string _message, Button &button):
	nextActButton(0, 0, 0, 0, "", "")
{
	message = _message;
	nextActButton = button;
}

void WinLoseWindow::Render()
{
	CustomWindow::Render();
	int tW, tH;
	GetTextWidthHeight(pixelFont_Med, message, tW, tH);
	int headSpacing = 50;
	Text(pixelFont_Med, { 255, 255, 255 }, message, Transform.x + (Transform.w - tW) / 2, Transform.y + headSpacing);
	nextActButton.RenderButton(pixelFont_Small);
}

WinLoseWindow::~WinLoseWindow()
{
}