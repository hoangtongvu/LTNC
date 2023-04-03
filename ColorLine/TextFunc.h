#pragma once
#include "GameManager.h"
//#include "GameplayCtrl.h"


void StringAndIntText(TTF_Font* font, SDL_Color color, string s, int num, int x, int y);
void IntText(TTF_Font* font, SDL_Color color, int num, int x, int y);
void StringText(TTF_Font* font, SDL_Color color, string s, int x, int y);
void GetTextWidthHeight(TTF_Font* font, string s, int& w, int& h);



