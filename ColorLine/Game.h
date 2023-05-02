#pragma once

#include "GameManager.h"
#include "GameplayCtrl.h"
#include "MainMenuCtrl.h"

extern vector<ColorLine> listColorLine;


class Game
{
public:

	Game();
	~Game();

	static Game* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new Game();
		}
		return instance;
	}

	void Init();

	void LoadComponents();

	void RestartGame();//

	void InitListColorLine(int newAmount);//

	void Update();

private:
	void LoadFonts();
	void LoadSounds();
	void LoadTextures();
	void LoadUI_Elements();
	void LoadSaveFile();

	static Game* instance;
};
