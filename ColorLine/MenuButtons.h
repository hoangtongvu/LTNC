#pragma once
#include "GameManager.h"
#include "Button.h"


class MenuButtons
{
public:
	Button newGameButton;
	Button continueGameButton;
	Button exitGameButton;


	MenuButtons();
	void Render();
	int CountEnabledButtons();
	void SetPosition();
	~MenuButtons();

private:

};

