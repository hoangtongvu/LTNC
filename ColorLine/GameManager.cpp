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

int colorLineAmount_Base = 35;//35
int colorLineAmount = 50;
int highestLayer = 0;
int remainingLine = 0;

int maxTimeSecond_Base = 35;
int maxTimeSecond = 35;
double timeRemainingCounter = maxTimeSecond;
bool stopCounting = false;


bool leveledUp = false;
int level = 0;

bool gameStarted = false;



//int simpleColorList[12][3] = {
//        {178, 51, 53},
//        {255, 116, 53},
//        {255, 203, 53},
//        {255, 249, 53},
//        {0, 117, 58},
//        {22, 221, 53},
//        {0, 82, 165},
//        {0, 121, 231},
//        {0, 169, 252},
//        {104, 30, 126},
//        {125, 60, 181},
//        {189, 122, 256}
//};



string assetDir = "Assets/";
string spriteDir = assetDir + "Sprites/";
string fontDir = assetDir + "Fonts/";

string audioDir = assetDir + "Audios/";
string musicDir = audioDir + "Musics/";
string sfxDir = audioDir + "SFXs/";




const int fps = 144;
float deltaTime = 1 / (float)fps;


int highestPointedLayer = 0;