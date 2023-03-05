#pragma once



SDL_Renderer* renderer;


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


const int gameplayScreen_X = 150;
const int gameplayScreen_Y = 0;
const int gameplayScreen_Width = 1280 - 150;
const int gameplayScreen_Height = 720;


int mouseX = 0;
int mouseY = 0;

bool isClicked = false;

int colorLineAmount = 10;
int highestLayer = 0;
int remainingLine = 0;

int maxTimeSecond = 5;
double timeRemainingCounter = maxTimeSecond;
bool stopCounting = false;

int level = 0;
