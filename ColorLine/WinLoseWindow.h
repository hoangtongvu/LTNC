#pragma once
#include "GameManager.h"
#include "CustomWindow.h"
#include "Button.h"
#include "CustomText.h"


class WinLoseWindow:
	public CustomWindow
{
public:
	CustomText message;
	Button nextActButton;
	WinLoseWindow(string _message, Button &button);
	void Render();
	~WinLoseWindow();

private:

};


