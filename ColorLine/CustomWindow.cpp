#include "CustomWindow.h"


CustomWindow::CustomWindow()
{
	Transform = { 0, 0, 0, 0 };
	r = 255;
	g = 255;
	b = 255;
	borderColor = { 0, 0, 0 };
}


void CustomWindow::Render()
{
	RenderBackground();
	RenderBorder();
}


void CustomWindow::RenderBackground()
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &Transform);
}


void CustomWindow::RenderBorder()
{
	SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, 255);
	SDL_RenderDrawRect(renderer, &Transform);

}




CustomWindow::~CustomWindow()
{
}