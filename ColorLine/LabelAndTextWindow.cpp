#include "LabelAndTextWindow.h"



LabelAndTextWindow::LabelAndTextWindow():
	label(pixelFont_Small),
	text(pixelFont_Small)
{
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


	int Text_W, Text_H;
	
	Text_W = label.Transform.w;
	Text_H = label.Transform.h;
	label.SetPosition(Transform.x + (Transform.w - Text_W) / 2, Transform.y + (Transform.h / 2 - Text_H) / 2);
	label.Render();
	

	Text_W = text.Transform.w;
	Text_H = text.Transform.h;
	text.SetPosition(Transform.x + (Transform.w - Text_W) / 2, Transform.y + Transform.h / 2 + (Transform.h / 2 - Text_H) / 2);
	text.Render();
	

}

LabelAndTextWindow::~LabelAndTextWindow()
{

}