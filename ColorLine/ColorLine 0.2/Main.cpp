#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "draw.h"



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


#pragma endregion

#pragma region VariableInitialize

SDL_Window* window;
SDL_Renderer* renderer;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const string WINDOW_TITLE = "MUSE DASH";
const int fps = 144;

SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL;
SDL_Event g_even;


int mouseX = 0;
int mouseY = 0;
bool isClicked = false;

int colorLineAmount = 100;
int highestLayer = 0;


#pragma endregion




class ColorLine
{
public:
#pragma region Variable Initialize

    SDL_Rect baseLine;
    SDL_Rect baseBorder;
    //int baseColor[3];
    int borderThickness;
    int r, g, b;
    bool isPointed = false;
    int layer;
    //int layer;
    int dir;
    bool isEnabled;
    bool isClickable;
#pragma endregion


    ColorLine()
    {
        borderThickness = 3;


        baseBorder.x = 50;
        baseBorder.y = 50;
        baseBorder.w = SCREEN_WIDTH;
        baseBorder.h = 40;

        baseLine.x = baseBorder.x + borderThickness;
        baseLine.y = baseBorder.y + borderThickness;
        baseLine.w = baseBorder.w - borderThickness * 2;
        baseLine.h = baseBorder.h - borderThickness * 2;
        
        r = 0;
        g = 0;
        b = 0;

        layer = 0;
        dir = 0;//horizontal
        //layer = 0;
        
        isEnabled = true;
        isClickable = true;
    }
    ~ColorLine();

    void SetDir(int dirParameter)
    {
        dir = dirParameter;
        if (dirParameter == 1)//vertical
        {
            baseBorder.w = baseBorder.h;
            baseBorder.h = SCREEN_HEIGHT;
            baseBorder.x += rand() % (SCREEN_WIDTH - baseBorder.w - baseBorder.x * 2 + 1) ;
            baseBorder.y = 0;
        }
        else
        {
            baseBorder.y += rand() % (SCREEN_HEIGHT - baseBorder.h - baseBorder.y * 2 + 1) ;
            baseBorder.x = 0;
        }
        baseLine.x = baseBorder.x + borderThickness;
        baseLine.y = baseBorder.y + borderThickness;
        baseLine.w = baseBorder.w - borderThickness * 2;
        baseLine.h = baseBorder.h - borderThickness * 2;

    }

    void SetBaseColor(int rPar, int gPar, int bPar)
    {
        r = rPar;
        g = gPar;
        b = bPar;
    }

    void RenderLine()
    {
        
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &baseBorder);

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &baseLine);
    }

    void DetectMouseClick(ColorLine listColorLine[])
    {
        if (isClicked)
        {
            if (mouseX >= baseBorder.x && mouseY >= baseBorder.y && 
                mouseX <= baseBorder.x + baseBorder.w && mouseY <= baseBorder.y + baseBorder.h)
            {
                cout << "Id: " << layer << endl;
                cout << "highestId: " << highestLayer << endl;


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

    
   
    
private:

};


ColorLine::~ColorLine()
{
}



int main(int argc, char* argv[])
{
    float deltaTime = 1 / (float)fps;

    initSDL(window, renderer);

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


#pragma region MyRegion

    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    //SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red
    //SDL_RenderDrawLine(renderer, 100, 100, 200, 200);

    //SDL_Rect filled_rect;
    //filled_rect.x = SCREEN_WIDTH - 400;
    //filled_rect.y = SCREEN_HEIGHT - 150;
    //filled_rect.w = 320;
    //filled_rect.h = 100;
    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    //SDL_RenderFillRect(renderer, &filled_rect);
    //
    //SDL_Rect filled_rect_1;
    //filled_rect_1.x = SCREEN_WIDTH - 500;
    //filled_rect_1.y = SCREEN_HEIGHT - 150;
    //filled_rect_1.w = 320;
    //filled_rect_1.h = 100;
    //SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // green
    //SDL_RenderFillRect(renderer, &filled_rect_1);
    
#pragma endregion

    
    // COLOR LIST
    int simpleColorList[5][3] = {
        {178, 51, 53},
        {255, 116, 53},
        {255, 203, 53},
        {255, 249, 53},
        {0, 117, 58}
    };

    bool close = false;

    // INITIALIZE COLOR LINE
    ColorLine *listColorLine = new ColorLine[colorLineAmount];

    srand(time(NULL));
    for (int i = 0; i < colorLineAmount; i++)
    {
        int dir = rand() % 2;
        int randomColor = rand() % 5;
        listColorLine[i].SetDir(dir);
        listColorLine[i].SetBaseColor(simpleColorList[randomColor][0], simpleColorList[randomColor][1], simpleColorList[randomColor][2]);
    }


    listColorLine[0].layer = 0;
    int layerCount = 1;
    for (int i = 1; i < colorLineAmount; i++)
    {
        cout << layerCount << endl;

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
    








    // GAME LOOP _________________________________________________________________
    while (!close)
    {
        srand(time(NULL));

        //cout << "highestId: " << highestId << endl;
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

        // BACKGROUND BLACK
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1000 / fps);

    }




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


