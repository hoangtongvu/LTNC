#include "GameLogo.h"



GameLogo::GameLogo() 
	//customText(pixelFont_Big)
{
	text = "olorLine";
	charC.SetTransform();

	colorChangeTimer = 0;
	maxTimeColorChange = 0.1;
	
	int length = text.length();
	for (size_t i = 0; i < length; i++)
	{
		string s = "";
		s += text[i];
		CustomText tempText(pixelFont_Big);
		tempText.SetContent(s);
		customText.emplace_back(tempText);
	}
}

GameLogo::~GameLogo()
{
}


void GameLogo::Render()
{
	colorChangeTimer += deltaTime;
	//cout << colorChangeTimer << endl;
	charC.Render();
	SDL_Rect tempPos = charC.Transform;


	int currentX = 20 + tempPos.x + tempPos.w;
	int h = 75; //customText[0].Transform.h;

	//cout << colorChangeTimer << endl;

	int length = text.length();

	if (colorChangeTimer >= maxTimeColorChange)
	{
		for (int i = 0; i < length; i++)
		{
			CustomText tempText = customText[i];	
			Uint8 randColorR = rand() % 225 + 30;
			Uint8 randColorG = rand() % 225 + 30;
			Uint8 randColorB = rand() % 225 + 30;
			customText[i].color = { randColorR , randColorG, randColorB };
			customText[i].SetContent(tempText.content);
			colorChangeTimer = 0;

		}

	}

	for (int i = 0; i < length; i++)
	{
		if (i == 0)
		{
			customText[i].SetPosition(currentX, tempPos.y + tempPos.h - h);
		}
		else
		{
			currentX += customText[i - 1].Transform.w;
			customText[i].SetPosition(currentX, tempPos.y + tempPos.h - h);
		}


		customText[i].Render();



	}





}