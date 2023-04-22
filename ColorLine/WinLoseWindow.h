#pragma once
#include "GameManager.h"
#include "CustomWindow.h"
#include "TextFunc.h"
#include "Button.h"


class WinLoseWindow:
	public CustomWindow
{
public:
	string message;
	Button nextActButton;
	WinLoseWindow(string _message, Button &button);
	void Render();
	~WinLoseWindow();

private:

};


