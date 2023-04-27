#include "Game.h"

Game game;

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
	LoadTextures();
	LoadUI_Elements();
	LoadSounds();
	LoadFonts();
	
}


void Game::LoadFonts()
{
	int fontSize = 20;
	pixelFont_Small = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize);
	pixelFont_Med = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize * 2);
}

void Game::LoadSounds()
{
	bgMusic = Mix_LoadMUS((musicDir + "road-in-the-forest-115035.mp3").c_str());
	if (bgMusic == NULL)
	{
		cout << Mix_GetError();
	}
	onClickButtonSFX = Mix_LoadWAV((sfxDir + "Retro Blop 18.wav").c_str());
}

void Game::LoadTextures()
{
	uiManager.mainMenuTexture.LoadTexture(-1, -1);
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
        int randomColor = rand() % 12;
        int randColorR = rand() % 205 + 30;
        int randColorG = rand() % 205 + 30;
        int randColorB = rand() % 205 + 30;


        ColorLine tempColorLine;
        tempColorLine.SetDir(dir);
        //tempColorLine.SetBaseColor(simpleColorList[randomColor][0] + randColorRange, simpleColorList[randomColor][1] + randColorRange, simpleColorList[randomColor][2] + randColorRange, 1);
        tempColorLine.SetBaseColor(randColorR, randColorG, randColorB, 1);
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
        mainMenuCtrl.Update();
        if (gameClose)
        {
            break;
        }

        gameplayCtrl.Update();

    }

}
