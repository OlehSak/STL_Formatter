#include "SDL2-2.0.12/include/SDL.h"
#include "SDL2_ttf-2.0.15/include/SDL_ttf.h"
#include <vector>
#include <iostream>

class Renderer
{
private:
	int _width;
	int _height;

	SDL_Window* _win;
	SDL_Renderer* _ren;

public:
	Renderer();
	~Renderer();

	bool	init();
	void	quit();
	void	drawVLine(int height, int start);
	int		render(std::vector<double> array_of_space, double maxSpace);
};

