#pragma once

#include "GameManager.h"
#include "CharC_Logo.h"
#include "CustomText.h"
#include "Vector3.h"


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
	float colorChangeSpeed;
	Vector3 currentColor[8];
	Vector3 targetColor[8];
};

