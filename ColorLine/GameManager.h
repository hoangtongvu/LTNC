#pragma once

#include "Header.h"
#include "CustomTexture.h"



extern SDL_Renderer* renderer;
extern SDL_Window* window;

extern const string WINDOW_TITLE;


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


extern const int gameplayScreen_X;
extern const int gameplayScreen_Y;
extern const int gameplayScreen_Width;
extern const int gameplayScreen_Height;


extern int mouseX;
extern int mouseY;

extern bool isClicked;

extern int colorLineAmount;
extern int colorLineAmount_Base;
extern int highestLayer;
extern int remainingLine;

extern int maxTimeSecond_Base;
extern int maxTimeSecond;
extern double timeRemainingCounter;
extern bool stopCounting;


extern bool leveledUp;
extern int level;

extern bool gameStarted;



extern string assetDir;
extern string spriteDir;
extern string fontDir;

extern string audioDir;
extern string musicDir;
extern string sfxDir;

extern int simpleColorList[][3];



extern const int fps;
extern float deltaTime;

extern int highestPointedLayer;

extern Mix_Music* bgMusic;
extern Mix_Chunk* onClickButtonSFX;

extern TTF_Font* pixelFont_Small;
extern TTF_Font* pixelFont_Med;

//extern CustomTexture gameplayBgTexture;

