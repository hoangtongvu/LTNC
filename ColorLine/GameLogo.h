#pragma once

#include "GameManager.h"
#include "CharC_Logo.h"
#include "CustomText.h"


class GameLogo
{
public:
	GameLogo();
	~GameLogo();

	void Render();
private:
	CharC_Logo charC;
	string text;
	vector <CustomText> customText;
	float colorChangeTimer;
	float maxTimeColorChange;
};

