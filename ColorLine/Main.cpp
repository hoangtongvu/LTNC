#include "Header.h"
#include "GameplayCtrl.h"
#include "ColorLine.h"
#include "Button.h"
#include "TextFunc.h"
#include "CustomTexture.h"





#pragma region FunctionInitialize
void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);
void logSDLError(std::ostream& os, const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();


void CountRemainingLine(ColorLine listColorLine[], int colorLineAmount, int& remainingLine);

void RestartGame(ColorLine oldListColorLine[], int simpleColorList[][3], int& oldAmount, int newAmount, int& highestLayer);
void InitListColorLine(ColorLine listColorLine[], int simpleColorList[][3], int& amountVariable, int newAmount, int& highestLayer);

#pragma endregion



#pragma region VariableInitialize

SDL_Window* window;

const string WINDOW_TITLE = "MUSE DASH";
const int fps = 144;

SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL;
SDL_Event g_even;


#pragma endregion





int main(int argc, char* argv[])
{
    float deltaTime = 1 / (float)fps;
    initSDL(window, renderer);
    TTF_Init();


    int fontSize = 20;
    TTF_Font* font = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize);
    TTF_Font* biggerFont = TTF_OpenFont((fontDir + "Minecraft.ttf").c_str(), fontSize * 3);

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
    ColorLine *listColorLine = new ColorLine[colorLineAmount];


    InitListColorLine(listColorLine, simpleColorList, colorLineAmount, colorLineAmount, highestLayer);


    
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
            startGameButton.RenderButton(font);
            startGameButton.DetectMouseClick();
            if (startGameButton.isSelected)
            {
                gameStarted = true;
                RestartGame(listColorLine, simpleColorList, colorLineAmount, colorLineAmount, highestLayer);
                startGameButton.isSelected = false;
            }
            
            // Exit game Button
            exitGameButton.RenderButton(font);
            exitGameButton.DetectMouseClick();
            if (exitGameButton.isSelected)
            {
                gameStarted = true;
                close = true;
                exitGameButton.isSelected = false;
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
        CountRemainingLine(listColorLine, colorLineAmount, remainingLine);
        if (!stopCounting)
        {
            timeRemainingCounter -= deltaTime;
        }



        //Gameplay Background
        gameplayBgTexture.RenderTexture();

        //Gameplay TextLine
        int y = 200;
        StringText(font, color, "Remaining Line:", 2, y);
        IntText(font, color, remainingLine, 2, y + fontSize);
        
        StringText(font, color, "Time left:", 2, y + 2 * fontSize);
        IntText(font, color, (int)(round(timeRemainingCounter)), 2, y + 3 * fontSize);




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
        for (int i = 0; i < colorLineAmount; i++)
        {
            if (listColorLine[i].isEnabled)
            {
                listColorLine[i].RenderLine();
                listColorLine[i].DetectMouseClick(listColorLine);

            }
        }




        WinLoseSystem(biggerFont);

        //Restart Button
        restartButton.RenderButton(font);
        restartButton.DetectMouseClick();
        if (restartButton.isSelected)
        {
            RestartGame(listColorLine, simpleColorList, colorLineAmount, colorLineAmount, highestLayer);
            restartButton.isSelected = false;
        }
        
        //ReturnMenu Button
        returnMenuButton.RenderButton(font);
        returnMenuButton.DetectMouseClick();
        if (returnMenuButton.isSelected)
        {
            gameStarted = false;
            returnMenuButton.isSelected = false;
        }


        //Reset mouseClick
        isClicked = false;

        



        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1000 / fps);

    }

    
    TTF_CloseFont(font);
    TTF_Quit();
    quitSDL(window, renderer);

    


//#pragma region MyRegion
//
//    // returns zero on success else non-zero
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//        printf("error initializing SDL: %s\n", SDL_GetError());
//    }
//    SDL_Window* win = SDL_CreateWindow("MUSE DASH", // creates a window
//        SDL_WINDOWPOS_CENTERED,
//        SDL_WINDOWPOS_CENTERED,
//        1280, 720, 0);
//
//    // triggers the program that controls
//    // your graphics hardware and sets flags
//    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
//
//    // creates a renderer to render our images
//    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
//
//    // creates a surface to load an image into the main memory
//    SDL_Surface* playerSurface;
//
//    // please provide a path for your image
//    playerSurface = IMG_Load("background_0.png");
//
//    // loads image to our graphics hardware memory.
//    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, playerSurface);
//
//    // clears main-memory
//    SDL_FreeSurface(playerSurface);
//
//    // let us control our image position
//    // so that we can move it with our keyboard.
//    SDL_Rect dest;
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




void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);
    if (TTF_Init() < 0) 
    {
        cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
    }
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}




void CountRemainingLine(ColorLine listColorLine[], int colorLineAmount, int& remainingLine)
{
    remainingLine = 0;
    for (int i = 0; i < colorLineAmount; i++)
    {
        if (listColorLine[i].isEnabled)
        {
            remainingLine++;
        }
    }
}


void RestartGame(ColorLine oldListColorLine[], int simpleColorList[][3], int& oldAmount, int newAmount, int& highestLayer)
{
    InitListColorLine(oldListColorLine, simpleColorList, oldAmount, newAmount, highestLayer);
    timeRemainingCounter = maxTimeSecond;
    stopCounting = false;
}


void InitListColorLine(ColorLine listColorLine[], int simpleColorList[][3], int& amountVariable, int newAmount, int& highestLayer)
{
    delete[] listColorLine;
    listColorLine = new ColorLine[newAmount];
    srand(time(NULL));
    for (int i = 0; i < newAmount; i++)
    {
        int dir = rand() % 2;
        int randomColor = rand() % 12;
        listColorLine[i].SetDir(dir);
        listColorLine[i].SetBaseColor(simpleColorList[randomColor][0], simpleColorList[randomColor][1], simpleColorList[randomColor][2], 1);
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
    amountVariable = newAmount;

}



