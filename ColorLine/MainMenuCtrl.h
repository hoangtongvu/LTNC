#pragma once
#include "GameManager.h"

#include "UIManager.h"
#include "SDL_Func.h"
//#include "CharC_Logo.h"
//#include "GameLogo.h"

#include "Game.h"

class MainMenuCtrl
{
public:
	MainMenuCtrl();
	~MainMenuCtrl();

	static MainMenuCtrl* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new MainMenuCtrl();
		}
		return instance;
	}
	void Update();


private:

	//GameLogo logo;
	void EventHolder();

	void RenderMainMenuTexture();

	void DetectButtonClick();

	void RenderButtons();

	void SetButtonPosition();

	void RenderLogo();

	static MainMenuCtrl* instance;
};



