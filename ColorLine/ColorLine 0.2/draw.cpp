#include <iostream>
#include <thread>
#include <chrono>
#include <SDL_image.h>



using namespace std;

void RenderGame()
{
	//cout << "ngu";
    int i = 0;
    while (i < 100)
    {

        cout << i++ << " ";
        this_thread::sleep_for(chrono::milliseconds(500));
    }

}

SDL_Texture* LoadTexture(string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        cout << "Unable to load image " << path << " SDL_image Error: "
            << IMG_GetError() << endl;

    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr)
        {
            cout << "Unable to create texture from " << path << " SDL Error: "
                << SDL_GetError() << endl;

        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
