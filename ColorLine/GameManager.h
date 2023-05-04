#pragma once

#include "Header.h"
//#include "CustomTexture.h"
//#include "Button.h"


extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_Event event;

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


extern int level;

extern bool gameStarted;



extern string assetDir;
extern string spriteDir;
extern string fontDir;

extern string audioDir;
extern string musicDir;
extern string sfxDir;




extern const int fps;
extern float deltaTime;

extern int highestPointedLayer;

extern Mix_Music* bgMusic;
extern Mix_Chunk* onPointedButtonSFX;
extern Mix_Chunk* onClickButtonSFX;
extern Mix_Chunk* onClickColorLineSFX;

extern TTF_Font* pixelFont_Small;
extern TTF_Font* pixelFont_Med;
extern TTF_Font* pixelFont_Big;

extern bool gameClose;

extern string saveFileName;


void ResetMouseClick();

void SDL_Render();

void SetBgBlack();

float LerpFloat(float a, float b, float t);

