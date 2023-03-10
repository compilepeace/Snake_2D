#ifndef _RENDERER_H
#define _RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include "snake.h"
#include "food.h"

class Renderer
{
public:
    // constructor/destructor
    Renderer(const std::size_t screen_width,
             const std::size_t screen_height,
             const std::size_t grid_width,
             const std::size_t grid_height);
    ~Renderer();

    // behavior specific members
    void Render(Snake const &snake, std::vector<Food> const &food);
    void UpdateWindowTitle(int score, int fps);

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif // _RENDERER_H