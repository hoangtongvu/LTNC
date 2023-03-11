#include "GameManager.h"



SDL_Renderer* renderer;
SDL_Window* window;
const string WINDOW_TITLE = "MUSE DASH";

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//ColorLine* test = new ColorLine[10];


const int gameplayScreen_X = 171;
const int gameplayScreen_Y = 20;
const int gameplayScreen_Width = 1088;
const int gameplayScreen_Height = 679;


int mouseX = 0;
int mouseY = 0;

bool isClicked = false;

int colorLineAmount = 100;
int highestLayer = 0;
int remainingLine = 0;

int maxTimeSecond = 1500;
double timeRemainingCounter = maxTimeSecond;
bool stopCounting = false;


bool leveledUp = false;
int level = 0;

bool gameStarted = false;







string assetDir = "Assets/";
string spriteDir = assetDir + "Sprites/";
string fontDir = assetDir + "Fonts/";





