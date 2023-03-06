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

int colorLineAmount = 50;
int highestLayer = 0;
int remainingLine = 0;

int maxTimeSecond = 40;
double timeRemainingCounter = maxTimeSecond;
bool stopCounting = false;

int level = 0;

bool gameStarted = false;



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

