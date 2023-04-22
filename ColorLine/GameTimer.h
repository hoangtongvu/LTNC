#pragma once
#include "GameManager.h"
#include "TextFunc.h"
#include "CustomWindow.h"


class GameTimer: 
	public CustomWindow
{
public:
	string timeValue;


	GameTimer();
	void SetTime(float time);
	void Render();
	~GameTimer();

private:
	
};



