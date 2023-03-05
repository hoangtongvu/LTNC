#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "draw.h"
#include "GameplayCtrl.h"
#include "ColorLine.h"



using namespace std;

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

void StringAndIntText(TTF_Font* font, SDL_Color color, string s, int num, int x, int y);
void IntText(TTF_Font* font, SDL_Color color, int num, int x, int y);
void StringText(TTF_Font* font, SDL_Color color, string s, int x, int y);
void GetTextWidthHeight(TTF_Font* font, string s, int& w, int& h);

void WinLoseSystem(TTF_Font* font);
void WinGame(TTF_Font* font);
void LoseGame(TTF_Font* font);


#pragma endregion



#pragma region VariableInitialize

SDL_Window* window;
//SDL_Renderer* renderer;
//const int SCREEN_WIDTH = 1280;
//const int SCREEN_HEIGHT = 720;
const string WINDOW_TITLE = "MUSE DASH";
const int fps = 144;

SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL;
SDL_Event g_even;


//int mouseX = 0;
//int mouseY = 0;
//bool isClicked = false;

//int colorLineAmount = 1000;
//int highestLayer = 0;


#pragma endregion


class Button
{
public:
    SDL_Rect baseButton;
    string buttonLabel;
    bool isSelected;


    Button(int x, int y, int w, int h, string label)
    {
        baseButton = { x, y, w, h };
        buttonLabel = label;
        isSelected = false;
    }
    void RenderButton(TTF_Font* font);
    void DetectMouseClick();
    ~Button();

private:

};


void Button::RenderButton(TTF_Font* font)
{
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderFillRect(renderer, &baseButton);
    int textW, textH;
    GetTextWidthHeight(font, buttonLabel, textW, textH);

}

void Button::DetectMouseClick()
{
    if (isClicked)
    {
        if (mouseX >= baseButton.x && mouseY >= baseButton.y &&
            mouseX <= baseButton.x + baseButton.w && mouseY <= baseButton.y + baseButton.h)
        {
            isSelected = true;
        }
    }
}

Button::~Button()
{
}



int main(int argc, char* argv[])
{
    float deltaTime = 1 / (float)fps;
    initSDL(window, renderer);
    TTF_Init();


    TTF_Font* font;
    TTF_Font* biggerFont;

    int fontSize = 17;
    font = TTF_OpenFont("Minecraft.ttf", fontSize);
    biggerFont = TTF_OpenFont("Minecraft.ttf", fontSize * 3);
    if (!font) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    }

    // Set color to white
    SDL_Color color = { 255, 255, 255 };



#pragma region MyRegion

    //SDL_Texture* background_0 = LoadTexture("background_0.png", renderer);
    //SDL_Rect background_0_Rect;
    //SDL_QueryTexture(background_0, NULL, NULL, &background_0_Rect.w, &background_0_Rect.h);
    //background_0_Rect.x = 100;
    //background_0_Rect.y = 100;
    //background_0_Rect.w = background_0_Rect.w;
    //background_0_Rect.h = background_0_Rect.h;
    //SDL_RenderCopy(renderer, background_0, NULL, &background_0_Rect);



    //RenderGame();

    //SDL_RenderClear(renderer);
#pragma endregion


    
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

    bool close = false;

    // INITIALIZE COLOR LINE
    ColorLine *listColorLine = new ColorLine[colorLineAmount];

    srand(time(NULL));
    for (int i = 0; i < colorLineAmount; i++)
    {
        int dir = rand() % 2;
        int randomColor = rand() % 12;
        listColorLine[i].SetDir(dir);
        listColorLine[i].SetBaseColor(simpleColorList[randomColor][0], simpleColorList[randomColor][1], simpleColorList[randomColor][2], 1);
    }


    listColorLine[0].layer = 0;
    int layerCount = 1;
    for (int i = 1; i < colorLineAmount; i++)
    {
        //cout << layerCount << endl;
        

        if (listColorLine[i].dir == listColorLine[i].dir)
        {
            if (listColorLine[i].dir == 1 &&
               ( listColorLine[i].baseBorder.x + listColorLine[i].baseBorder.w <= listColorLine[i - 1].baseBorder.x ||
                 listColorLine[i - 1].baseBorder.x + listColorLine[i - 1].baseBorder.w <= listColorLine[i].baseBorder.x ) )//vertical
            {
                listColorLine[i].layer = listColorLine[i - 1].layer;
            }
            else if (listColorLine[i].dir == 0 &&
               ( listColorLine[i].baseBorder.y + listColorLine[i].baseBorder.h <= listColorLine[i - 1].baseBorder.y ||
                 listColorLine[i - 1].baseBorder.y + listColorLine[i - 1].baseBorder.h <= listColorLine[i].baseBorder.y ) )//horizontal
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

        
        //listColorLine[i].SetId(i);

    }

    highestLayer = layerCount - 1;
    

    SDL_Rect gameplayBorder;
    gameplayBorder.x = gameplayScreen_X;
    gameplayBorder.y = gameplayScreen_Y;
    gameplayBorder.w = gameplayScreen_Width;
    gameplayBorder.h = gameplayScreen_Height;

    
    Button restartButton(0, 0, 70, 70, "RESTART");


    // GAME LOOP _________________________________________________________________
    while (!close)
    {
        srand(time(NULL));
        if (!stopCounting)
        {
            timeRemainingCounter -= deltaTime;
        }

        CountRemainingLine(listColorLine, colorLineAmount, remainingLine);


        // BACKGROUND BLACK
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect bgRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &bgRect);



        





        int y = 200;
        StringText(font, color, "Remaining Line:", 2, y);
        IntText(font, color, remainingLine, 2, y + fontSize);
        
        StringText(font, color, "Time left:", 2, y + 2 * fontSize);
        IntText(font, color, (int)(round(timeRemainingCounter)), 2, y + 3 * fontSize);


        
        






        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &gameplayBorder);



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


        restartButton.RenderButton(font);
        restartButton.DetectMouseClick();
        if (restartButton.isSelected)
        {
            LoseGame(font);
            restartButton.isSelected = false;
        }




        for (int i = 0; i < colorLineAmount; i++)
        {
            //cout << listColorLine[i].r << " ";
            if (listColorLine[i].isEnabled)
            {
                listColorLine[i].RenderLine();
                listColorLine[i].DetectMouseClick(listColorLine);

            }
        }


        isClicked = false;

        

        WinLoseSystem(biggerFont);

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




#pragma region ColorLine Function


ColorLine::ColorLine()
{
    borderThickness = 4;


    baseBorder.x = 0;
    baseBorder.y = 0;
    baseBorder.w = gameplayScreen_Width;
    baseBorder.h = 40;

    baseLine.x = baseBorder.x + borderThickness;
    baseLine.y = baseBorder.y + borderThickness;
    baseLine.w = baseBorder.w - borderThickness * 2;
    baseLine.h = baseBorder.h - borderThickness * 2;

    r = 0;
    g = 0;
    b = 0;
    alpha = 0;

    layer = 0;
    dir = 0;//horizontal

    isEnabled = true;

}

void ColorLine::SetDir(int dirParameter)
{
    dir = dirParameter;
    if (dirParameter == 1)//vertical
    {
        baseBorder.w = baseBorder.h;
        baseBorder.h = gameplayScreen_Height;
        baseBorder.x += gameplayScreen_X + rand() % (gameplayScreen_Width - baseBorder.w - baseBorder.x * 2 + 1);
        baseBorder.y = 0;
    }
    else
    {
        baseBorder.y += rand() % (gameplayScreen_Height - baseBorder.h - baseBorder.y * 2 + 1);
        baseBorder.x = gameplayScreen_X;
    }
    baseLine.x = baseBorder.x + borderThickness;
    baseLine.y = baseBorder.y + borderThickness;
    baseLine.w = baseBorder.w - borderThickness * 2;
    baseLine.h = baseBorder.h - borderThickness * 2;
}

void ColorLine::SetBaseColor(int rPar, int gPar, int bPar, int alphaPar)
{
    r = rPar;
    g = gPar;
    b = bPar;
    alpha = alphaPar;
}

void ColorLine::RenderLine()
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &baseBorder);

    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderFillRect(renderer, &baseLine);
}

void ColorLine::DetectMouseClick(ColorLine listColorLine[])
{
    if (isClicked)
    {
        if (mouseX >= baseBorder.x && mouseY >= baseBorder.y &&
            mouseX <= baseBorder.x + baseBorder.w && mouseY <= baseBorder.y + baseBorder.h)
        {
            //cout << "Id: " << layer << endl;
            //cout << "highestId: " << highestLayer << endl;


            if (layer == highestLayer)
            {
                isEnabled = false;


                highestLayer = listColorLine[0].layer;
                for (int i = 1; i < colorLineAmount; i++)
                {
                    if (highestLayer < listColorLine[i].layer && listColorLine[i].isEnabled)
                    {
                        highestLayer = listColorLine[i].layer;
                    }
                }
                //cout << "clicked";
            }

        }
    }
}

ColorLine::~ColorLine()
{
}

#pragma endregion


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



#pragma region Text Manager

void StringAndIntText(TTF_Font* font, SDL_Color color, string s, int num, int x, int y)
{
    s += to_string(num);
    SDL_Surface* text;
    text = TTF_RenderText_Solid(font, s.c_str(), color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = text->w;
    dest.h = text->h;

    SDL_RenderCopy(renderer, text_texture, NULL, &dest);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text);
}


void IntText(TTF_Font* font, SDL_Color color, int num, int x, int y)
{
    string s = to_string(num);
    SDL_Surface* text;
    text = TTF_RenderText_Solid(font, s.c_str(), color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = text->w;
    dest.h = text->h;

    SDL_RenderCopy(renderer, text_texture, NULL, &dest);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text);
}

void StringText(TTF_Font* font, SDL_Color color, string s, int x, int y)
{
    SDL_Surface* text;
    text = TTF_RenderText_Solid(font, s.c_str(), color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = text->w;
    dest.h = text->h;

    SDL_RenderCopy(renderer, text_texture, NULL, &dest);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text);
}


void GetTextWidthHeight(TTF_Font* font, string s, int& w, int& h)
{
    SDL_Surface* text;
    text = TTF_RenderText_Solid(font, s.c_str(), {0, 0, 0});
    w = text->w;
    h = text->h;
    SDL_FreeSurface(text);
}
#pragma endregion



#pragma region WIN LOSE SYSTEM

void WinLoseSystem(TTF_Font* font)
{
    if (remainingLine <= 0 && timeRemainingCounter > 0)
    {
        WinGame(font);
        stopCounting = true;
    }
    else if (timeRemainingCounter <= 0 && remainingLine > 0)
    {
        LoseGame(font);
        stopCounting = true;
    }

}

void WinGame(TTF_Font* font)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect winScreen = {gameplayScreen_X, gameplayScreen_Y, gameplayScreen_Width, gameplayScreen_Height};
    SDL_RenderFillRect(renderer, &winScreen);
    string winMessage = "YOU WIN";
    int textW, textH;
    GetTextWidthHeight(font, winMessage, textW, textH);
    StringText(font, { 255, 255, 255 }, winMessage, gameplayScreen_X + (gameplayScreen_Width - textW) / 2, gameplayScreen_Y + (gameplayScreen_Height - textH) / 2);


}

void LoseGame(TTF_Font* font)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect loseScreen = { gameplayScreen_X, gameplayScreen_Y, gameplayScreen_Width, gameplayScreen_Height };
    SDL_RenderFillRect(renderer, &loseScreen);
    string loseMessage = "YOU LOSE";
    int textW, textH;
    GetTextWidthHeight(font, loseMessage, textW, textH);
    StringText(font, { 255, 255, 255 }, loseMessage, gameplayScreen_X + (gameplayScreen_Width - textW) / 2, gameplayScreen_Y + (gameplayScreen_Height - textH) / 2);

}
#pragma endregion

