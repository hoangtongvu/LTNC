#pragma once
#include "GameManager.h"
#include "ColorLine.h"
#include "Vector3.h"

class CharC_Logo
{
public:
	SDL_Rect Transform;

	vector <ColorLine> logoListColorLine;


	void SetTransform();
	void Render();


	CharC_Logo();
	~CharC_Logo();

private:

	float colorChangeTimer;
	float maxTimeColorChange;
	float colorChangeSpeed;

	Vector3 currentColor[3];
	Vector3 targetColor[3];
};


