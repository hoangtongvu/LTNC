#include "UIManager.h"


UIManager uiManager;


int startButtonW = 200;
int startButtonH = 60;
int menuButtonSpacing = 50;

int nextLevelButtonW = 140;
int nextLevelButtonH = 60;

UIManager::UIManager():
	//gameplayBgTexture("ColorLine Game UI.png", 0, 0),
	mainMenuTexture("menuBg.png", 0, 0),
	restartButton(14, 14, 52, 52, "RESTART", ""),
	returnMenuButton(78, 14, 52, 52, "HOME", ""),
	startGameButton((SCREEN_WIDTH - startButtonW) / 2, (SCREEN_HEIGHT - startButtonH) / 2, startButtonW, startButtonH, "START", ""),
	exitGameButton((SCREEN_WIDTH - startButtonW) / 2, (SCREEN_HEIGHT - startButtonH) / 2 + startButtonH + menuButtonSpacing, startButtonW, startButtonH, "EXIT", ""),
	nextLevelButton(gameplayScreen_X + (gameplayScreen_Width - nextLevelButtonW) / 2, 40 + gameplayScreen_Y + (gameplayScreen_Height - nextLevelButtonH) / 2, nextLevelButtonW, nextLevelButtonH, "NEXT LEVEL", "")

{
	

}

UIManager::~UIManager()
{
}
