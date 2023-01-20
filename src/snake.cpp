#include <algorithm>
#include "snake.h"

Snake::Snake(int grid_width, int grid_height): alive(true), size_(1), speed(0.2), growing_(false) {
    std::cout << "Snake constructor\n";
    grid_width_ = grid_width;
    grid_height_ = grid_height;
    head_x = grid_width/2;
    head_y = grid_height/2;
    std::cout << "grid coordinates: " << grid_width << "," << grid_height << "\n";
    std::cout << "snake head: (" << static_cast<int>(head_x) << "," << static_cast<int>(head_y) << ")\n";
}

std::size_t Snake::Size() const { return size_; }

/*
    Update snake position/coordinates
*/
void Snake::Update()
{

    SDL_Point prev_head {
        static_cast<int>(head_x),
        static_cast<int>(head_y)
    }; 
    //std::cout << "curr head: (" << static_cast<int>(head_x) << "," << static_cast<int>(head_y) << ")\n";
    UpdateHead();
    SDL_Point curr_head {
        static_cast<int>(head_x),
        static_cast<int>(head_y)
    };
    if (curr_head.x != prev_head.x || curr_head.y != prev_head.y){
        UpdateBody(prev_head);

    }

    /*
        set snake alive status by checking if current head 
        has land over snake body.
    */
    if (IsSnakeCell(curr_head) || Size() == 0){
        alive = false;
    }
    //std::cout << "updated head: (" << static_cast<int>(head_x) << "," << static_cast<int>(head_y) << ")\n";
}

/*
    Update snake head based on currentDirection 
*/
void Snake::UpdateHead()
{
    switch (currentDirection)
    {
        case Direction::kUp:
            head_y -= speed;
        break;
        case Direction::kDown:
            head_y += speed; 
        break;
        case Direction::kLeft:
            head_x -= speed;
        break;
        case Direction::kRight:
            head_x += speed;
        break;
    }

    head_x = fmod(head_x + grid_width_, grid_width_);
    head_y = fmod(head_y + grid_height_, grid_height_);
}

/*
    deque : (Tail)=========>(Head)
*/
void Snake::UpdateBody(const SDL_Point head)
{
    body.emplace_back(head);       // new head pushed at front 
    if (!growing_){
        body.pop_front();      // the snake moves without eating
    }
    else {
        growing_ = false;
        ++size_;    
    }
}

/* set growing_ flag to true */
void Snake::GrowBody() { growing_ = true;}

/*

*/
bool Snake::IsSnakeCell (const SDL_Point &cell)
{
    /*
    bool found;
    std::for_each(body_.begin(), body_.end(), [found, cell](const SDL_Point &snake_cell){
       if (cell.x == snake_cell.x && cell.y == snake_cell.y)
            found = true;
    });
    */
    for(auto &snake_cell: body){
        if (cell.x == snake_cell.x && cell.y == snake_cell.y)
            return true;
    }
    return false;
}