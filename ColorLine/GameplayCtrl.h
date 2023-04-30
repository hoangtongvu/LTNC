#pragma once
#include "GameManager.h"

#include "UIManager.h"
#include "ColorLine.h"
#include "Button.h"
#include "TEST_CLASS.h"
#include "CustomTexture.h"
#include "SDL_Func.h"
#include "GameTimer.h"
#include "WinLoseWindow.h"
#include "LabelAndTextWindow.h"
#include "GameSave.h"

#include "Game.h"


#pragma region Blend and Color Texture

//SDL_Surface* playerSurface;
//playerSurface = IMG_Load("whitePixel.png");
//SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, playerSurface);
//SDL_FreeSurface(playerSurface);
//SDL_Rect dest;
//dest.w = 200;
//dest.h = 200;
//dest.x = 0;
//dest.y = 0;
//
//
//SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);//This sets the texture in blendmode
//
//SDL_SetTextureColorMod(tex, 125, 255, 0);
//SDL_SetTextureAlphaMod(tex, 150); //sets the alpha into the texture
//
//SDL_RenderCopy(renderer, tex, NULL, &dest); //Redraws the image with a fresh, new alpha ~


#pragma endregion

class GameplayCtrl
{
public:
	GameplayCtrl();
	~GameplayCtrl();

	void Update();

private:
	string winMessage = "YOU WIN";
	string loseMessage = "YOU LOSE";

	void WinLoseSystem();
	void WinGame();
	void LoseGame();
	void ContinueNextLevel();
	void ResizeListColorLine();
	void CountRemainingLine();
	void CountTimeLeft();
	void GetHighestPointedLayer();
	void GameplayEventHolder();
	void RenderGameplayTextLine();
	void DetectButtonClick();
	void RenderAndDetectMouseClickColorLine();
	void RenderFadingLine();
	void TEST_RenderGameplayOverLay();
};





extern GameplayCtrl gameplayCtrl;