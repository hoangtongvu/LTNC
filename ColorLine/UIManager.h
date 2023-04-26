#pragma once
#include "GameManager.h"
#include "Button.h"
#include "TextFunc.h"
#include "ColorLine.h"
#include "CustomTexture.h"
#include "MenuButtons.h"



class UIManager
{
public:
	Button restartButton;
	Button returnMenuButton;

	MenuButtons menuButtons;

	Button nextLevelButton;

	//CustomTexture gameplayBgTexture;
	CustomTexture mainMenuTexture;
	UIManager();
	~UIManager();

private:

};


extern UIManager uiManager;