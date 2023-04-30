#pragma once
#include "GameManager.h"
#include "CustomWindow.h"
#include "CustomText.h"


class GameTimer: 
	public CustomWindow
{
public:


	GameTimer();
	void SetTime(float time);
	void Render();
	~GameTimer();

private:
	string timeValue;
	CustomText text;
	
};



