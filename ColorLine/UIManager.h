#pragma once
#include "GameManager.h"
#include "Button.h"
#include "TextFunc.h"
#include "ColorLine.h"
#include "CustomTexture.h"


//extern Button restartButton;
//extern Button returnMenuButton;
//
//extern Button startGameButton;
//extern Button exitGameButton;
//
//extern Button nextLevelButton;
//
//extern CustomTexture gameplayBgTexture;
//extern CustomTexture mainMenuTexture;




class UIManager
{
public:
	Button restartButton;
	Button returnMenuButton;

	Button startGameButton;
	Button exitGameButton;

	Button nextLevelButton;

	CustomTexture gameplayBgTexture;
	CustomTexture mainMenuTexture;
	UIManager();
	~UIManager();

private:

};


extern UIManager uiManager;