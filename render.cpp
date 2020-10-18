#include "Header.h"
#include <iostream>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

bool init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
    }

    win = SDL_CreateWindow("Histogram", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        ok = false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL) {
        std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
        ok = false;
    }

    return ok;
}

void quit() {
    SDL_DestroyWindow(win);
    win = NULL;

    SDL_DestroyRenderer(ren);
    ren = NULL;

    SDL_Quit();
}

void drawVLine(int height, int start)
{
    int bottom = 460;

    SDL_RenderDrawLine(ren, start,   bottom, start,   bottom - height);
    SDL_RenderDrawLine(ren, start+1, bottom, start+1, bottom - height);
    SDL_RenderDrawLine(ren, start+2, bottom, start+2, bottom - height);
}

int render(std::vector<double> array_of_space, double maxSpace) {
    SDL_Event e;
    bool run = true;

    double val = 400/maxSpace;

    if (!init()) {
        quit();
        system("pause");
        return 1;
    }

    while (run)
    {
        SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

        SDL_RenderDrawLine(ren, 20, 20, 20, 460);
        SDL_RenderDrawLine(ren, 20, 460, 620, 460);

        SDL_RenderDrawLine(ren, 40, 460, 40, 470);
        SDL_RenderDrawLine(ren, 310, 460, 310, 470);
        SDL_RenderDrawLine(ren, 580, 460, 580, 470);


        for (int i = 0; i <= 180; i++)
        {
            drawVLine(round(array_of_space[180 - i] * val), 39 + (i * 3));
        }

        SDL_RenderPresent(ren);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                quit();
                return 0;
            }
        }
    }

    quit();
    return 0;
}
