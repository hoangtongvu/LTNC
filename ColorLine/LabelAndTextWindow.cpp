#include "LabelAndTextWindow.h"



LabelAndTextWindow::LabelAndTextWindow()
{
	label = "";
	text = "";
	r = 0; g = 0; b = 0;
	borderColor = { 255, 255, 255 };
}



void LabelAndTextWindow::Render()
{
	CustomWindow::RenderBackground();
	SDL_Rect labelRect = { Transform.x, Transform.y, Transform.w, Transform.h / 2 };
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderFillRect(renderer, &labelRect);
	CustomWindow::RenderBorder();


	SDL_Color textColor = { 255, 255, 255 };
	int Text_W, Text_H;
	GetTextWidthHeight(pixelFont_Small, label, Text_W, Text_H);
	Text(pixelFont_Small, textColor, label, Transform.x + (Transform.w - Text_W) / 2, Transform.y + (Transform.h / 2 - Text_H) / 2);
	
	GetTextWidthHeight(pixelFont_Small, text, Text_W, Text_H);
	Text(pixelFont_Small, textColor, text, Transform.x + (Transform.w - Text_W) / 2, Transform.y + Transform.h / 2 + (Transform.h / 2 - Text_H) / 2);

}

LabelAndTextWindow::~LabelAndTextWindow()
{

}