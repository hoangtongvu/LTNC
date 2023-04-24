#include "Game.h"

Game game;


Game::Game()
{
}

Game::~Game()
{
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