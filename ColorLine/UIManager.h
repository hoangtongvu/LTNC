#pragma once
#include "GameManager.h"
#include "Button.h"
#include "ColorLine.h"
#include "CustomTexture.h"
#include "MenuButtons.h"
#include "GameLogo.h"



class UIManager
{
public:
	UIManager();
	~UIManager();

	static UIManager* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new UIManager();
		}
		return instance;
	}

	Button restartButton;
	Button returnMenuButton;

	MenuButtons menuButtons;

	Button nextLevelButton;

	CustomTexture mainMenuTexture;
	GameLogo logo;


private:

	static UIManager* instance;
};

