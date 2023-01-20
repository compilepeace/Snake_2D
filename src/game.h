#ifndef _GAME_H
#define _GAME_H

#include <random>
#include <SDL2/SDL.h>
#include "snake.h"
#include "controller.h"
#include "renderer.h"

/* responsible for managing game state */
class Game
{
public:
    // constructor/destructor
    Game(std::size_t w, std::size_t h);

    // getters/setters
    std::size_t Score() const;
    std::size_t SnakeSize() const;

    // typical behavior functionality
    void Run(Controller &controller, Renderer &renderer, const std::size_t fps);

private:
    Snake snake_;
    SDL_Point food_;
    std::size_t score_{0};

    // random number generator for PlaceFood()
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    bool PlaceFood();
    void UpdateState();
};

#endif  // _GAME_H