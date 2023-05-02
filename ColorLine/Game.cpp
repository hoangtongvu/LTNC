#include "Game.h"

Game* Game::instance = NULL;

vector<ColorLine> listColorLine;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
    initSDL(window, renderer);
    TTF_Init();
}

void Game::LoadComponents()
{
	LoadSaveFile();
	LoadFonts();
	LoadTextures();
	LoadUI_Elements();
	LoadSounds();
	
}


void Game::LoadFonts()
{
	int fontSize = 20;
	pixelFont_Small = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize);
	pixelFont_Med = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize * 2);
	pixelFont_Big = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize * 5);
}

void Game::LoadSounds()
{
	bgMusic = Mix_LoadMUS((musicDir + "road-in-the-forest-115035.mp3").c_str());
	if (bgMusic == NULL)
	{
		cout << Mix_GetError();
	}
	onClickButtonSFX = Mix_LoadWAV((sfxDir + "Retro Beeep 20 - ClickedButton.wav").c_str());
	onPointedButtonSFX = Mix_LoadWAV((sfxDir + "Retro Beeep 06 - PointedButton.wav").c_str());
	onClickColorLineSFX = Mix_LoadWAV((sfxDir + "Retro Blop 18.wav").c_str());
}

void Game::LoadTextures()
{
	//uiManager.mainMenuTexture.LoadTexture(-1, -1);
	UIManager::GetInstance()->mainMenuTexture.LoadTexture(-1, -1);
}

void Game::LoadUI_Elements()
{

}

void Game::LoadSaveFile()
{
	gameSave.Load(saveFileName);
}

void Game::RestartGame()
{
    long long int newAmount = (long)round((long)level * level * 0.15 * 12) + colorLineAmount_Base;
    InitListColorLine(newAmount);
    maxTimeSecond = maxTimeSecond_Base + (int)round(level * level * 0.13 * 12);
    timeRemainingCounter = maxTimeSecond;
    stopCounting = false;
}

void Game::InitListColorLine(int newAmount)
{
    for (int i = 0; i < listColorLine.size(); i++)
    {
        listColorLine[i].OnDestroy();
    }
    listColorLine.clear();
    colorLineAmount = newAmount;
    srand(time(NULL));
    for (int i = 0; i < newAmount; i++)
    {
        int dir = rand() % 2;
        if (i % 2 == 0)
        {
            dir = 0;
        }
        else
        {
            dir = 1;
        }
        
        int randColorR = rand() % 205 + 30;
        int randColorG = rand() % 205 + 30;
        int randColorB = rand() % 205 + 30;


        ColorLine tempColorLine;
        tempColorLine.SetDir(dir);
        if (dir == 1)
        {
            tempColorLine.baseBorder.x = gameplayScreen_X + rand() % (gameplayScreen_Width - tempColorLine.baseBorder.w + 1);
            tempColorLine.baseBorder.y = gameplayScreen_Y;
        }
        else
        {
            tempColorLine.baseBorder.y = gameplayScreen_Y + rand() % (gameplayScreen_Height - tempColorLine.baseBorder.h + 1);
            tempColorLine.baseBorder.x = gameplayScreen_X;
        }
        tempColorLine.SetTransform();
        tempColorLine.SetBaseColor(randColorR, randColorG, randColorB);
        listColorLine.emplace_back(tempColorLine);
    }


    listColorLine[0].layer = 0;
    int layerCount = 1;

    for (int i = 1; i < newAmount; i++)
    {
        if (listColorLine[i].dir == listColorLine[i].dir)
        {
            if (listColorLine[i].dir == 1 &&
                (listColorLine[i].baseBorder.x + listColorLine[i].baseBorder.w <= listColorLine[i - 1].baseBorder.x ||
                    listColorLine[i - 1].baseBorder.x + listColorLine[i - 1].baseBorder.w <= listColorLine[i].baseBorder.x))//vertical
            {
                listColorLine[i].layer = listColorLine[i - 1].layer;
            }
            else if (listColorLine[i].dir == 0 &&
                (listColorLine[i].baseBorder.y + listColorLine[i].baseBorder.h <= listColorLine[i - 1].baseBorder.y ||
                    listColorLine[i - 1].baseBorder.y + listColorLine[i - 1].baseBorder.h <= listColorLine[i].baseBorder.y))//horizontal
            {
                listColorLine[i].layer = listColorLine[i - 1].layer;
            }
            else
            {
                listColorLine[i].layer = layerCount;
                layerCount++;
            }


        }
        else
        {
            listColorLine[i].layer = layerCount;
            layerCount++;
        }
    }


    highestLayer = layerCount - 1;

}

void Game::Update()
{
    while (!gameClose)
    {
        srand(time(NULL));
        MainMenuCtrl::GetInstance()->Update();
        if (gameClose)
        {
            break;
        }

        GameplayCtrl::GetInstance()->Update();

    }

}
