#pragma once
#include "GameplayCtrl.h"


void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);
void logSDLError(std::ostream& os, const std::string& msg, bool fatal);


void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();
