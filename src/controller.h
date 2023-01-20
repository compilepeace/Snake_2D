#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <SDL2/SDL.h>
#include "snake.h"

class Controller
{
public:
    void HandleInput(bool &running, Snake &snake);
private:
    void ChangeDirection(Snake &snake, Snake::Direction new_direction, Snake::Direction old_direction);
};

#endif // _CONTROLLER_H