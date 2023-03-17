#pragma once
#include "GameManager.h"

#include "TextFunc.h"
#include "ColorLine.h"
#include "Button.h"
#include "CustomTexture.h"
#include "SDL_Func.h"


//SDL_Renderer* renderer;
//
//
//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 720;
//
//
//const int gameplayScreen_X = 175;
//const int gameplayScreen_Y = 24;
//const int gameplayScreen_Width = 1080;
//const int gameplayScreen_Height = 671;
//
//
//int mouseX = 0;
//int mouseY = 0;
//
//bool isClicked = false;
//
//int colorLineAmount = 1000;
//int highestLayer = 0;
//int remainingLine = 0;
//
//int maxTimeSecond = 9999;
//double timeRemainingCounter = maxTimeSecond;
//bool stopCounting = false;
//
//int level = 0;
//
//bool gameStarted = false;
//
//string assetDir = "Assets/";
//string spriteDir = assetDir + "Sprites/";



extern vector<ColorLine> listColorLine;







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


void WinLoseSystem(TTF_Font* medFont, TTF_Font* smallFont);
void WinGame(TTF_Font* medFont, TTF_Font* smallFont);
void LoseGame(TTF_Font* medFont, TTF_Font* smallFont);


void ContinueNextLevel(TTF_Font* smallFont);

void ResizeListColorLine();



void CountRemainingLine();

void RestartGame();

void InitListColorLine(int newAmount);

void Gameplay_Update(TTF_Font* medFont, TTF_Font* smallFont);
