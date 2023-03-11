#include "GameplayCtrl.h"





#pragma region FunctionInitialize


void CountRemainingLine();

void RestartGame(int simpleColorList[][3], int newAmount);
void InitListColorLine(int simpleColorList[][3], int newAmount);

#pragma endregion



#pragma region VariableInitialize


const int fps = 144;

SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL;
SDL_Event g_even;


#pragma endregion





int main(int argc, char* argv[])
{
    initSDL(window, renderer);
    TTF_Init();
    
    
    float deltaTime = 1 / (float)fps;


    int fontSize = 20;
    TTF_Font* pixelFont_Small = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize);
    TTF_Font* pixelFont_Med = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize * 2);


    // Set font color to black
    SDL_Color color = { 0, 0, 0 };


    // COLOR LIST
    int simpleColorList[12][3] = {
        {178, 51, 53},
        {255, 116, 53},
        {255, 203, 53},
        {255, 249, 53},
        {0, 117, 58},
        {22, 221, 53},
        {0, 82, 165},
        {0, 121, 231},
        {0, 169, 252},
        {104, 30, 126},
        {125, 60, 181}, 
        {189, 122, 256}
    };


    // INITIALIZE COLOR LINE
    //ColorLine *listColorLine = new ColorLine[colorLineAmount];


    InitListColorLine(simpleColorList, colorLineAmount);


    
    Button restartButton(14, 14, 52, 52, "", "RestartButton.png");
    Button returnMenuButton(78, 14, 52, 52, "", "HomeButton.png");

    int startButtonW = 140;
    int startButtonH = 40;
    int menuButtonSpacing = 30;
    Button startGameButton((SCREEN_WIDTH - startButtonW) / 2, (SCREEN_HEIGHT - startButtonH) / 2, startButtonW, startButtonH, "START", "");
    Button exitGameButton((SCREEN_WIDTH - startButtonW) / 2, (SCREEN_HEIGHT - startButtonH) / 2 + startButtonH + menuButtonSpacing, startButtonW, startButtonH, "EXIT", "");

    

    CustomTexture gameplayBgTexture("ColorLine Game UI.png", 0, 0);
    CustomTexture mainMenuTexture("menuBg.png", 0, 0);






    bool close = false;
    // GAME LOOP _________________________________________________________________
    while (!close)
    {

        //Main Menu Controller
        while (!gameStarted)
        {

            //Menu Event Holder
            SDL_Event menuEvent;
            while (SDL_PollEvent(&menuEvent))
            {
                switch (menuEvent.type)
                {
                case SDL_QUIT:
                {
                    gameStarted = true;
                    close = true;
                    break;

                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    switch (menuEvent.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                    {
                        isClicked = true;
                    }
                    default:
                        break;
                    }
                }
                case SDL_MOUSEMOTION:
                {
                    mouseX = menuEvent.motion.x;
                    mouseY = menuEvent.motion.y;

                    std::stringstream ss;
                    ss << "X: " << mouseX << " Y: " << mouseY;

                    SDL_SetWindowTitle(window, ss.str().c_str());
                    break;

                }
                default:
                    break;

                }

            }


            mainMenuTexture.RenderTexture();



            // Start game Button
            startGameButton.RenderButton(pixelFont_Small);
            startGameButton.DetectMouseClick();
            if (startGameButton.DetectMouseClick())
            {
                gameStarted = true;
                RestartGame(simpleColorList, colorLineAmount);

            }
            
            // Exit game Button
            exitGameButton.RenderButton(pixelFont_Small);
            exitGameButton.DetectMouseClick();
            if (exitGameButton.DetectMouseClick())
            {
                gameStarted = true;
                close = true;
            }




            isClicked = false;

            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            SDL_Delay(1000 / fps);
        }
        if (close)
        {
            break;
        }




        srand(time(NULL));

        //Count RemainingTime
        CountRemainingLine();
        if (!stopCounting)
        {
            timeRemainingCounter -= deltaTime;
        }

        //cout << level << endl;

        //Gameplay Background
        gameplayBgTexture.RenderTexture();

        //Gameplay TextLine
        int y = 200;
        StringText(pixelFont_Small, color, "Remaining Line:", 2, y);
        IntText(pixelFont_Small, color, remainingLine, 2, y + fontSize);
        



        int timeLeftText_W, timeLeftText_H;
        int roundedTimeLeftSecond = (int)(round(timeRemainingCounter));
        GetTextWidthHeight(pixelFont_Small, to_string(roundedTimeLeftSecond), timeLeftText_W, timeLeftText_H);
        IntText(pixelFont_Small, {255, 255, 255}, roundedTimeLeftSecond, 21 + (109 - timeLeftText_W) / 2, 427 + (21 - timeLeftText_H) / 2);




        // EVENT HOLDER
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type) 
            {
            case SDL_QUIT:
            {
                close = true;
                break;

            }
            case SDL_MOUSEBUTTONDOWN:
            {
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                {
                    isClicked = true;
                }
                default:
                    break;
                }
            }
            case SDL_MOUSEMOTION:
            {
                mouseX = event.motion.x;
                mouseY = event.motion.y;

                std::stringstream ss;
                ss << "X: " << mouseX << " Y: " << mouseY;

                SDL_SetWindowTitle(window, ss.str().c_str());
                break;

            }
            default:
                break;
                            
            }

        }


        //Render and DetectMouseClick ColorLines
        for (int i = 0; i < listColorLine.size(); i++)
        {
            if (listColorLine[i].isEnabled)
            {
                listColorLine[i].RenderLine();
                listColorLine[i].DetectMouseClick();

            }
        }

        ResizeListColorLine();




        WinLoseSystem(pixelFont_Med, pixelFont_Small);

        //Restart Button
        restartButton.RenderButton(pixelFont_Small);
        restartButton.DetectMouseClick();
        if (restartButton.DetectMouseClick())
        {
            RestartGame(simpleColorList, colorLineAmount);
        }
        
        //ReturnMenu Button
        returnMenuButton.RenderButton(pixelFont_Small);
        returnMenuButton.DetectMouseClick();
        if (returnMenuButton.DetectMouseClick())
        {
            gameStarted = false;
        }


        //Reset mouseClick
        isClicked = false;

        



        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1000 / fps);

    }

    
    TTF_CloseFont(pixelFont_Small);
    TTF_CloseFont(pixelFont_Med);
    TTF_Quit();
    quitSDL(window, renderer);

    


//#pragma region MyRegion
//
//    
//    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
//
//    dest.w /= 6;
//    dest.h /= 6;
//
//    dest.x = (SCREEN_WIDTH - dest.w) / 2;
//
//    dest.y = (SCREEN_HEIGHT - dest.h) / 2;
//
//    // controls animation loop
//    bool close = false;
//
//    // speed of box
//    int speed = 300;
//    int moveDirX = 1;
//    int moveDirY = 0;
//
//    // animation loop
//    while (!close) {
//        SDL_Event event;
//
//        dest.y += deltaTime * speed * moveDirY;
//        dest.x += deltaTime * speed * moveDirX;
//        while (SDL_PollEvent(&event)) 
//        {
//            switch (event.type) 
//            {
//
//            case SDL_QUIT:
//                close = true;
//                break;
//                
//            case SDL_KEYDOWN:
//                switch (event.key.keysym.scancode) 
//                {
//                case SDL_SCANCODE_ESCAPE:
//                    close = true;
//                    break;
//                case SDL_SCANCODE_W:
//                case SDL_SCANCODE_UP:
//                    moveDirY = -1;
//                    moveDirX = 0;
//                    //dest.y -= 1.0 / 60 * speed;
//                    break;
//                case SDL_SCANCODE_A:
//                case SDL_SCANCODE_LEFT:
//                    moveDirX = -1;
//                    moveDirY = 0;
//                    //dest.x -= 1.0 / 60 * speed;
//                    break;
//                case SDL_SCANCODE_S:
//                case SDL_SCANCODE_DOWN:
//                    moveDirY = 1;
//                    moveDirX = 0;
//                    //dest.y += 1.0 / 60 * speed;
//                    break;
//                case SDL_SCANCODE_D:
//                case SDL_SCANCODE_RIGHT:
//                    moveDirX = 1;
//                    moveDirY = 0;
//                    //dest.x += 1.0 / 60 * speed;
//                    break;
//                default:
//                    break;
//                }
//            }
//        }
//
//        // right boundary
//        if (dest.x + dest.w >= SCREEN_WIDTH)
//            dest.x = SCREEN_WIDTH - dest.w;
//
//        // left boundary
//        if (dest.x < 0)
//            dest.x = 0;
//
//        // bottom boundary
//        if (dest.y + dest.h > SCREEN_HEIGHT)
//            dest.y = SCREEN_HEIGHT - dest.h;
//
//        // upper boundary
//        if (dest.y < 0)
//            dest.y = 0;
//
//        // clears the screen
//        SDL_RenderClear(rend);
//        SDL_RenderCopy(rend, tex, NULL, &dest);
//
//        // triggers the double buffers
//        // for multiple rendering
//        SDL_RenderPresent(rend);
//
//        // calculates to 60 fps
//        SDL_Delay(1000 / fps);
//    }
//
//    // destroy texture
//    SDL_DestroyTexture(tex);
//
//    // destroy renderer
//    SDL_DestroyRenderer(rend);
//
//    // destroy window
//    SDL_DestroyWindow(win);
//
//    // close SDL
//    SDL_Quit();
//
//#pragma endregion



    return 0;
}








void CountRemainingLine()
{
    remainingLine = listColorLine.size();  
}


void RestartGame(int simpleColorList[][3], int newAmount)
{
    InitListColorLine(simpleColorList, newAmount);
    timeRemainingCounter = maxTimeSecond;
    stopCounting = false;
}


void InitListColorLine(int simpleColorList[][3], int newAmount)
{
    listColorLine.clear();
    colorLineAmount = newAmount;
    srand(time(NULL));
    for (int i = 0; i < newAmount; i++)
    {
        int dir = rand() % 2;
        int randomColor = rand() % 12;
        ColorLine tempColorLine;
        tempColorLine.SetDir(dir);
        tempColorLine.SetBaseColor(simpleColorList[randomColor][0], simpleColorList[randomColor][1], simpleColorList[randomColor][2], 1);
        listColorLine.emplace_back(tempColorLine);
    }
    

    listColorLine[0].layer = 0;
    int layerCount = 1;

    for (int i = 1; i < newAmount; i++)
    {
        if (listColorLine[i].dir == listColorLine[i].dir)
        {
            if (listColorLine[i].dir == 1 &&
                (listColorLine[i].baseBorder.x + listColorLine[i].baseBorder.w <= listColorLine[i - 1].baseBorder.x ||
                    listColorLine[i - 1].baseBorder.x + listColorLine[i - 1].baseBorder.w <= listColorLine[i].baseBorder.x))//vertical
            {
                listColorLine[i].layer = listColorLine[i - 1].layer;
            }
            else if (listColorLine[i].dir == 0 &&
                (listColorLine[i].baseBorder.y + listColorLine[i].baseBorder.h <= listColorLine[i - 1].baseBorder.y ||
                    listColorLine[i - 1].baseBorder.y + listColorLine[i - 1].baseBorder.h <= listColorLine[i].baseBorder.y))//horizontal
            {
                listColorLine[i].layer = listColorLine[i - 1].layer;
            }
            else
            {
                listColorLine[i].layer = layerCount;
                layerCount++;
            }


        }
        else
        {
            listColorLine[i].layer = layerCount;
            layerCount++;
        }
    }


    highestLayer = layerCount - 1;

}



