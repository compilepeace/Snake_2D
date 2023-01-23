#ifndef _GAME_H
#define _GAME_H

#include <random>
#include <SDL2/SDL.h>
#include <chrono>
#include "snake.h"
#include "controller.h"
#include "renderer.h"
#include "food.h"

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
    std::size_t score_{0};
    std::vector<Food> food_; 

    // remove food from grid after certain duration
    std::chrono::time_point<std::chrono::system_clock> tp_start_poison;
    std::chrono::time_point<std::chrono::system_clock> tp_start_bonus;
    std::chrono::time_point<std::chrono::system_clock> tp_end;
    bool eat_healthy;

    // random number generator for PlaceFood()
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    void PlaceFood(Food::Type type);
    void UpdateState();
};

#endif  // _GAME_H