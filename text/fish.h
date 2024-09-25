#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <math.h>
#include <vector>
#include <random>
#include <ctime>
#define height 480
#define width 640

using namespace std;

SDL_Texture* loadTexture(const char file[], SDL_Renderer* ren)
{
    SDL_Texture* texture = IMG_LoadTexture(ren, file);
    if (!texture)
    {
        cout << IMG_GetError();
    }
    return texture;
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

SDL_Texture* fish1;
SDL_Texture* fish2;
SDL_Texture* inversed_fish1;
SDL_Texture* inversed_fish2;
SDL_Texture* trash1;
SDL_Texture* trash2;

class object
{
protected:
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* image;
    int y = 0; int x = 0;
public:
    int GetX()
    {
        return x;
    }
    int GetY()
    {
        return y;
    }
    virtual void XX() = 0;
};

class background : public object
{
public:
    void XX() {};
    background(SDL_Renderer* base_renderer)
    {
        renderer = base_renderer;
    }
    void show(string name_image)
    {
        image = loadTexture(name_image.c_str(), renderer);
        renderTexture(image, renderer, 0, 0, width, height);
        SDL_DestroyTexture(image);
        image = NULL;
    }
};

class fish : public object
{
private:
    int speed=0;
    int cost=0;
public:
    void XX() {};
    fish(SDL_Renderer* base_renderer, int layer, bool side1)
    {
        renderer = base_renderer;
        y = layer;
        newfish();
    }
    void move(int i)
    {
        y = 200 + 50 * i;
        x += speed;
        renderTexture(image, renderer, x, y, 53, 45);
        if (x < -53)
            newfish();
        if (x>width)
            newfish();
    }
    int moveup(int i)
    {
        int cur_cost = cost;
        if (y > 20)
        {
            y -= 3;
            renderTexture(image, renderer, x, y, 53, 45);
            return 0;
        }
        else
        {
            newfish();
            return cur_cost;
        }
    }
    void newfish()
    {
        int rando;
        rando = rand() % 6;
        switch (rando)
        {
        case 0:
            image = fish1; speed = -1; cost = 100;
            x = width; break;
        case 1:
            image = inversed_fish1; speed = 1; cost = 100;
            x = -53; break;
        case 2:
            image = trash1; speed = -1; cost = -100;
            x = width; break;
        case 3:
            image = trash2; speed = -2; cost = -50;
            x = width; break;
        case 4:
            image = fish2; speed = -2; cost = 300;
            x = width; break;
        case 5:
            image = inversed_fish2; speed = 2; cost = 300;
            x = -53; break;
        }
    }
};

class hook : public object
{
private:
    bool flagback = 0;
    int flagmove = 0;
    int ifish = -1;
public:
    void XX() {};
    hook(SDL_Renderer* base_renderer)
    {
        renderer = base_renderer;
        image = loadTexture("hook.png", renderer);
        x = width/2; y = 20;
        renderTexture(image, renderer, x, y, 60, 60);
    }
    void move(bool* flag, vector<class object*>* fishes, int* ifish)
    {
        if (!*flag)
        {
            renderTexture(image, renderer, x, y, 60, 60);
        }
        else
        {
            switch (flagmove)
            {
            case 0: if (y <= height - 60)
            {
                y += 3;
                renderTexture(image, renderer, x, y, 60, 60);
            }
                  else
            {
                flagmove = 1;
            }
                  for (int i = 0; i < 5; i++)
                  {
                      if ((abs(x - fishes->at(i)->GetX()) <= 10) && (abs(y - fishes->at(i)->GetY()) <= 10))
                      {
                          flagmove = 2;
                          *ifish = i;
                      }
                  }
                  break;
            case 1: if (y != 20)
            {
                y -= 3;
                renderTexture(image, renderer, x, y, 60, 60);
            }
                  else
            {
                flagmove = 0;
                *flag = 0;
            }
                  for (int i = 0; i < 5; i++)
                  {
                      if ((abs(x - fishes->at(i)->GetX()) <= 10) && (abs(y - fishes->at(i)->GetY()) <= 10))
                      {
                          flagmove = 2;
                          *ifish = i;
                      }
                  }
                  break;
            case 2: if (y != 20)
            {
                y -= 3;
                renderTexture(image, renderer, x, y, 60, 60);
            }
                  else
            {
                flagmove = 0;
                *flag = 0;
            }
            }
        }
    }
};