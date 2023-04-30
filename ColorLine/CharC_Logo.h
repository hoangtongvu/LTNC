#pragma once
#include "GameManager.h"
#include "ColorLine.h"

class CharC_Logo
{
public:
	SDL_Rect Transform;

	//vector <ColorLine> logoListColorLine;
	ColorLine logoListColorLine[3];


	void SetTransform();
	void Render();

	CharC_Logo();
	~CharC_Logo();

private:

};


