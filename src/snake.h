#ifndef _SNAKE_H
#define _SNAKE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <deque>

class Snake
{
public:
    // constructor/destructor
    //Snake (int grid_width, int grid_height);
    Snake(int grid_width, int grid_height); 

    // getters/setters
    std::size_t Size() const;

    // behavior specific members
    enum Direction {
        kUp,
        kDown,
        kLeft,
        kRight,
    };
    std::deque<SDL_Point> body;
    Direction currentDirection = Direction::kUp;
    bool alive;
    double speed;
    double head_x;
    double head_y;
    void Update();
    void GrowBody();
    bool IsSnakeCell (const int x, const int y);

private:
    std::size_t size_;
    bool growing_;
    int grid_width_;
    int grid_height_;

    void UpdateHead();
    void UpdateBody(const SDL_Point prev_head);
};

#endif // _SNAKE_H