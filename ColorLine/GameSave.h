#pragma once
#include "GameManager.h"

class GameSave
{
public:
	GameSave();
	~GameSave();
	void Load(string fileName);
	void Write(string fileName);


private:

};

extern GameSave gameSave;