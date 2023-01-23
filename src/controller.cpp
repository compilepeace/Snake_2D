#include "controller.h"

void Controller::HandleInput(bool &running, Snake &snake)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT){
            running = false;
            return;
        }
        else if (e.type == SDL_KEYDOWN){
          switch (e.key.keysym.sym) {
          case SDLK_UP:
            //std::cout << "\tSnake goes UP\n";
            ChangeDirection(snake, Snake::Direction::kUp,
                            Snake::Direction::kDown);
            break;

          case SDLK_DOWN:
            //std::cout << "\tSnake goes down\n";
            ChangeDirection(snake, Snake::Direction::kDown,
                            Snake::Direction::kUp);
            break;

          case SDLK_LEFT:
            //std::cout << "\tSnake goes left\n";
            ChangeDirection(snake, Snake::Direction::kLeft,
                            Snake::Direction::kRight);
            break;

          case SDLK_RIGHT:
            //std::cout << "\tSnake goes right\n";
            ChangeDirection(snake, Snake::Direction::kRight,
                            Snake::Direction::kLeft);
            break;
          }
        }
    }
}

void Controller::ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite)
{
    if (snake.currentDirection != opposite)
        snake.currentDirection = input;
}