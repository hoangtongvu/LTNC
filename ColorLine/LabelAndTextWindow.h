#pragma once
#include "GameManager.h"
#include "CustomWindow.h"
#include "CustomText.h"


class LabelAndTextWindow :
	public CustomWindow
{
public:
	CustomText label;
	CustomText text;


	LabelAndTextWindow();
	void Render();
	~LabelAndTextWindow();

private:

};

