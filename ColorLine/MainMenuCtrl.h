#pragma once
#include "GameManager.h"

#include "UIManager.h"
#include "SDL_Func.h"
#include "CharC_Logo.h"

#include "Game.h"

class MainMenuCtrl
{
public:
	MainMenuCtrl();
	~MainMenuCtrl();
	void Update();


private:

	void EventHolder();

	void RenderMainMenuTexture();

	void DetectButtonClick();

	void RenderButtons();

	void SetButtonPosition();

	void RenderLogo();

};







extern MainMenuCtrl mainMenuCtrl;