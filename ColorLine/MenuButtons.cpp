#include "MenuButtons.h"

int minY = 350;
int maxY = SCREEN_HEIGHT - 30;
int borderWidth = 300;

int menuButtonW = 250;
int menuButtonH = 60;
int menuButtonSpacing = 50;



MenuButtons::MenuButtons() :
	newGameButton(
		(SCREEN_WIDTH - menuButtonW) / 2,
		(SCREEN_HEIGHT - menuButtonH) / 2,
		menuButtonW,
		menuButtonH,
		"NEW GAME", ""),
	continueGameButton(
		(SCREEN_WIDTH - menuButtonW) / 2,
		(SCREEN_HEIGHT - menuButtonH) / 2,
		menuButtonW,
		menuButtonH,
		"CONTINUE", ""),
	exitGameButton(
		(SCREEN_WIDTH - menuButtonW) / 2,
		(SCREEN_HEIGHT - menuButtonH) / 2 + menuButtonH + menuButtonSpacing,
		menuButtonW,
		menuButtonH,
		"EXIT", "")

{
	continueGameButton.isEnabled = false;
}


void MenuButtons::Render()
{
	int thickness = 5;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect Border = { (SCREEN_WIDTH - borderWidth) / 2, minY, borderWidth, maxY - minY };
	SDL_RenderDrawRect(renderer, &Border);
	Border = { Border.x + thickness, Border.y + thickness, Border.w - 2 * thickness, Border.h - 2 * thickness };
	SDL_RenderDrawRect(renderer, &Border);


	newGameButton.RenderButton(pixelFont_Med);
	continueGameButton.RenderButton(pixelFont_Med);
	exitGameButton.RenderButton(pixelFont_Med);
}


int MenuButtons::CountEnabledButtons()
{
	int buttonEnabledCount = 0;
	if (newGameButton.isEnabled)
	{
		buttonEnabledCount++;
	}
	if (continueGameButton.isEnabled)
	{
		buttonEnabledCount++;
	}
	if (exitGameButton.isEnabled)
	{
		buttonEnabledCount++;
	}
	return buttonEnabledCount;
}

void MenuButtons::SetPosition()
{
	if (level == 0)
	{
		continueGameButton.isEnabled = false;
	}
	else
	{
		continueGameButton.isEnabled = true;
	}


	int buttonEnabledCount = CountEnabledButtons();
	int spaceBetween = ((maxY - minY) - (buttonEnabledCount * menuButtonH)) / (buttonEnabledCount + 1);
	//cout << spaceBetween << endl;

	int currentY = minY;
	if (newGameButton.isEnabled)
	{

		currentY += spaceBetween;
		SDL_Rect tempPos = newGameButton.baseButton;
		tempPos.y = currentY;
		newGameButton.baseButton = tempPos;
	}
	if (continueGameButton.isEnabled)
	{

		currentY += spaceBetween + menuButtonH;
		SDL_Rect tempPos = continueGameButton.baseButton;
		tempPos.y = currentY;
		continueGameButton.baseButton = tempPos;
	}
	if (exitGameButton.isEnabled)
	{

		currentY += spaceBetween + menuButtonH;
		SDL_Rect tempPos = exitGameButton.baseButton;
		tempPos.y = currentY;
		exitGameButton.baseButton = tempPos;
	}

}

MenuButtons::~MenuButtons()
{
}

