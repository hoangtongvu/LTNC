#include "Game.h"




Game::Game()
{
}

Game::~Game()
{
}


void Game::LoadComponents()
{
	LoadSounds();
	LoadFonts();
	//gameplayBgTexture = new CustomTexture("ColorLine Game UI.png", 0, 0, -1, -1);
}


void Game::LoadFonts()
{
	int fontSize = 20;
	pixelFont_Small = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize);
	pixelFont_Med = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize * 2);
}

void Game::LoadSounds()
{
	bgMusic = Mix_LoadMUS((musicDir + "Lonesome Traveller.wav").c_str());
	onClickButtonSFX = Mix_LoadWAV((sfxDir + "Retro Blop 18.wav").c_str());
}