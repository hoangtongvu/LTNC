#pragma once
#include "GameManager.h"

#include "UIManager.h"
#include "SDL_Func.h"
#include "BloomEffect.h"

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

};







extern MainMenuCtrl mainMenuCtrl;