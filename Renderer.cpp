#include "Renderer.h"

Renderer::Renderer(void) : _width(640), _height(480), _win(NULL), _ren(NULL)
{}

Renderer::~Renderer(void)
{}

bool Renderer::init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0 && TTF_Init() != 0) {
        std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
    }

    _win = SDL_CreateWindow("Histogram", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);
    if (_win == NULL) {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        ok = false;
    }

    _ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED);
    if (_ren == NULL) {
        std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
        ok = false;
    }

    return ok;
}

void Renderer::quit() {
    SDL_DestroyWindow(_win);
    _win = NULL;

    SDL_DestroyRenderer(_ren);
    _ren = NULL;

    SDL_Quit();
}

void Renderer::drawVLine(int height, int start)
{
    int bottom = 460;

    SDL_RenderDrawLine(_ren, start, bottom, start, bottom - height);
    SDL_RenderDrawLine(_ren, start + 1, bottom, start + 1, bottom - height);
    SDL_RenderDrawLine(_ren, start + 2, bottom, start + 2, bottom - height);
}

int Renderer::render(std::vector<double> array_of_space, double maxSpace) {
    SDL_Event e;
    bool run = true;

    double val = 400 / maxSpace;

    if (!init()) {
        quit();
        system("pause");
        return 1;
    }

    while (run)
    {
        SDL_SetRenderDrawColor(_ren, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(_ren);
        SDL_SetRenderDrawColor(_ren, 0xFF, 0xFF, 0xFF, 0xFF);

        SDL_RenderDrawLine(_ren, 20, 20, 20, 460);
        SDL_RenderDrawLine(_ren, 20, 460, 620, 460);

        SDL_RenderDrawLine(_ren, 40, 460, 40, 470);
        SDL_RenderDrawLine(_ren, 310, 460, 310, 470);
        SDL_RenderDrawLine(_ren, 580, 460, 580, 470);

        for (int i = 0; i < array_of_space.size(); i++)
        {
            drawVLine(round(array_of_space.at(i) * val), 39 + (i * 3));
        }

        SDL_RenderPresent(_ren);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit();
                return 0;
            }
        }
    }

    quit();
    return 0;
}