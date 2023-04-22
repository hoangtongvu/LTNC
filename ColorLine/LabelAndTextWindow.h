#pragma once
#include "GameManager.h"
#include "TextFunc.h"
#include "CustomWindow.h"


class LabelAndTextWindow :
	public CustomWindow
{
public:
	string label;
	string text;


	LabelAndTextWindow();
	void Render();
	~LabelAndTextWindow();

private:

};

