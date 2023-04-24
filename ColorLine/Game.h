#pragma once

#include "GameManager.h"
#include "GameplayCtrl.h"


class Game
{
public:
	Game();
	~Game();
	void LoadComponents();

	void LoadFonts();

	void LoadSounds();

	void LoadTextures();

	void LoadUI_Elements();

	void LoadSaveFile();
private:

};

extern Game game;