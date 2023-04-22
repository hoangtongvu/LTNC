#include "GameManager.h"



SDL_Renderer* renderer;
SDL_Window* window;
SDL_Event event;
const string WINDOW_TITLE = "MUSE DASH";

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


const int gameplayScreen_X = 171;
const int gameplayScreen_Y = 20;
const int gameplayScreen_Width = 1088;
const int gameplayScreen_Height = 679;


int mouseX = 0;
int mouseY = 0;

bool isClicked = false;

int colorLineAmount_Base = 35;//35
int colorLineAmount = 50;
int highestLayer = 0;
int remainingLine = 0;

int maxTimeSecond_Base = 35;//35
int maxTimeSecond = 35;//35
double timeRemainingCounter = maxTimeSecond;
bool stopCounting = false;


bool leveledUp = false;
int level = 0;

bool gameStarted = false;




string assetDir = "Assets/";
string spriteDir = assetDir + "Sprites/";
string fontDir = assetDir + "Fonts/";

string audioDir = assetDir + "Audios/";
string musicDir = audioDir + "Musics/";
string sfxDir = audioDir + "SFXs/";



const int fps = 144;
float deltaTime = 1 / (float)fps;


int highestPointedLayer = 0;

Mix_Music* bgMusic = NULL;
Mix_Chunk* onClickButtonSFX = NULL;

TTF_Font* pixelFont_Small = NULL;
TTF_Font* pixelFont_Med = NULL;


bool gameClose = false;



void ResetMouseClick()
{
	isClicked = false;
}

void SDL_Render()
{
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
    SDL_Delay(1000 / fps);
}



