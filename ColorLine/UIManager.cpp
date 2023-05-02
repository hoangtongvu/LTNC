#include "UIManager.h"


UIManager* UIManager::instance = NULL;



int nextLevelButtonW = 140;
int nextLevelButtonH = 60;

UIManager::UIManager() :
	//gameplayBgTexture("ColorLine Game UI.png", 0, 0),
	mainMenuTexture("menuBg.png"),
	restartButton(14, 14, 52, 52, "RESTART", ""),
	returnMenuButton(78, 14, 52, 52, "HOME", ""),
	nextLevelButton(gameplayScreen_X + (
		gameplayScreen_Width - nextLevelButtonW) / 2,
		40 + gameplayScreen_Y + (gameplayScreen_Height - nextLevelButtonH) / 2,
		nextLevelButtonW, nextLevelButtonH,
		"NEXT LEVEL",
		"")

{
	

}

UIManager::~UIManager()
{
	//delete instance;
}
