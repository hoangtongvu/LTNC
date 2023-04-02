#include "Game.h"




Game::Game()
{
}

Game::~Game()
{
}


void Game::LoadComponents()
{
	
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
	bgMusic = Mix_LoadMUS((musicDir + "Lonesome Traveller.wav").c_str());
	onClickButtonSFX = Mix_LoadWAV((sfxDir + "Retro Blop 18.wav").c_str());
}

void Game::LoadTextures()
{
	gameplayBgTexture.LoadTexture(-1, -1);
}


void Game::LoadUI_Elements()
{

}