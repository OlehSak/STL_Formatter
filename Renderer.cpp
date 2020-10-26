#include "Renderer.h"
#include <string>

Renderer::Renderer(void) :
    _width(800),
    _height(600),
    _win(NULL),
    _ren(NULL),
    _font(NULL)
{
}

Renderer::~Renderer(void)
{
}

void    Renderer::draw_text(double value, int x, int y)
{
    SDL_Surface* surface = TTF_RenderText_Solid(_font,
        std::to_string(value).c_str(), _color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(_ren, surface);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { x, y, texW, texH };

    SDL_RenderCopy(_ren, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

bool    Renderer::init() {

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    bool ok = true;
    TTF_Init();
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
    _color = { 255, 255, 255 };
    _font = TTF_OpenFont("OpenSans-Regular.ttf", 14);

    return ok;
}

void Renderer::quit() {
    SDL_DestroyWindow(_win);
    _win = NULL;

    SDL_DestroyRenderer(_ren);
    _ren = NULL;

    TTF_CloseFont(_font);
    TTF_Quit();
    SDL_Quit();
}

void Renderer::drawVLine(int height, int start, int bottom)
{
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

    int x, y;

    x = 80;
    y = 80;

    SDL_SetRenderDrawColor(_ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_ren);
    SDL_SetRenderDrawColor(_ren, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(_ren, x + 20, y + 20, x + 20, y + 460);
    SDL_RenderDrawLine(_ren, x + 20, y + 460, x + 620, y + 460);

    SDL_RenderDrawLine(_ren, x + 40, y + 460, x + 40, y + 470);
    SDL_RenderDrawLine(_ren, x + 310, y + 460, x + 310, y + 470);
    SDL_RenderDrawLine(_ren, x + 580, y + 460, x + 580, y + 470);

    for (int i = 0; i < (int)array_of_space.size(); i++)
    {
        drawVLine((int)round(array_of_space.at(i) * val), x + 39 + (i * 3), y + 460);
    }

    draw_text(maxSpace, 0 + 35 + 3, 120);
    draw_text(maxSpace/2, 0 + 35 + 3, (120 + 420/2));
    draw_text(0, 0 + 35 + 3, 120 + 420);

    draw_text(-90, x + 40 - 30, y + 475);
    draw_text(0, x + 310 - 30, y + 475);
    draw_text(90, x + 580 - 30, y + 475);


    while (run)
    {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                run = false;
                quit();
                return 0;
            }
        }

        SDL_RenderPresent(_ren);
    }
  
    quit();
    return 0;
}