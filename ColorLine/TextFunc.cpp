#include "TextFunc.h"


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
    text = TTF_RenderText_Solid(font, s.c_str(), { 0, 0, 0 });
    w = text->w;
    h = text->h;
    SDL_FreeSurface(text);
}
