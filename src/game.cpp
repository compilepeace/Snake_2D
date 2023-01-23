
#include <iostream>
#include "game.h"

/*
    Constructs snake and places food at a random location on grid
*/
Game::Game(std::size_t width, std::size_t height): 
    snake_(width, height), score_(0), eat_healthy(false),
    engine(dev()),
    random_w(0, static_cast<int>(width-1)),
    random_h(0, static_cast<int>(width-1))
{
    // add each type of food to food_ vector
    for (auto i = 0; i < Food::Type::kSizeOfEnum; ++i){
        Food item(static_cast<Food::Type>(i));
        food_.emplace_back(item);
    }

    // create a grid and PlaceFood at random point in grid window
    PlaceFood(Food::Type::kHealthy);
}

/* 
    Starts the game loop at a desired frame rate.
*/
void Game::Run(Controller &controller, Renderer &renderer, const size_t frameRate)
{
    size_t seconds = 0;
    Uint64 frameStartTick; 
    Uint64 frameEndTick;  
    int frameCount = 0;
    int timeElapsed = 0;
    // time duration (in ms) for which a frame (i.e. a game loop iteration)
    // is supposed to be rendered (executed).
    int desiredFrameDuration = 1000/frameRate;  

    Uint64 titleTimePoint = SDL_GetTicks64();
    // game loop: input, update, render 
    // Each iteration of game loop corresponds to a Frame in game
    bool running = true;
    while (running){
        frameStartTick = SDL_GetTicks64();

        controller.HandleInput(running, snake_);   // input - change snake direction based on i/p
        UpdateState();                      // update game state (i.e. move snake and/or place food)
        renderer.Render(snake_, food_);            // render snake and food

        frameEndTick = SDL_GetTicks64();

        /*
            after 1 second has passed (1000 milliseconds) 
        */
        if ((frameEndTick - titleTimePoint) >= 1000){ 
            //std::cout << "1 second lapsed, fps:" << frameCount << "\n";
            renderer.UpdateWindowTitle(Score(), frameCount);       // update the window title every second 
            titleTimePoint = frameEndTick;
            frameCount = 0;
        }

        /*
            Delay current iteration if it executed quicker than desiredFrameDuration.
        */ 
        timeElapsed = frameEndTick - frameStartTick;
        if (timeElapsed < desiredFrameDuration) {
            SDL_Delay(desiredFrameDuration - timeElapsed);
        }

        ++frameCount;
    }
}

/*
    Updates game state, i.e. updating snake & maybe food coordinates too.)
*/
void Game::UpdateState()
{
    if (score_ < 0 || !snake_.alive){
        snake_.alive = false;
        return;
    }

    // update snake
    snake_.Update();

    // place bonus item (depending on score)
    if (food_[Food::Type::kBonus].onGrid == false
        && score_ > 0
        && (score_ % 7 == 0)
        && eat_healthy          // most recently, snake ha
        ){
      PlaceFood(Food::Type::kBonus);
      food_[Food::Type::kBonus].onGrid = true;
      tp_start_bonus = std::chrono::system_clock::now();    // start time point
    }
    // place poison if score resides in a multiple of 5
    if (food_[Food::Type::kPoison].onGrid == false
        && score_ != 0 
        && score_ % 5 == 0) {
      PlaceFood(Food::Type::kPoison);
      food_[Food::Type::kPoison].onGrid = true;
      tp_start_poison = std::chrono::system_clock::now();   // start time point
    }

    // remove poison from grid after 4 seconds of its placement
    tp_end = std::chrono::system_clock::now();              // end time point
    auto poison_duration = std::chrono::duration_cast<std::chrono::seconds>(tp_end - tp_start_poison).count();
    if (poison_duration > 4
        && food_[Food::Type::kPoison].onGrid){
            food_[Food::Type::kPoison].onGrid = false;
        }
    // remove bonus from grid after 2 seconds of its placement
    tp_end = std::chrono::system_clock::now();
    auto bonus_duration = std::chrono::duration_cast<std::chrono::seconds>(tp_end - tp_start_bonus).count();
    if (bonus_duration > 2
        && food_[Food::Type::kBonus].onGrid){
            food_[Food::Type::kBonus].onGrid = false;
        }

    int new_x = static_cast<int>(snake_.head_x);
    int new_y = static_cast<int>(snake_.head_y);
    /*
        Iterate over food_ item.
        If snake head lands on a food item, update accordingly -
            * score
            * speed
            * body growth
    */
    for (auto &item: food_)
    {
      // item is present on grid and snake head lands on it
      if (item.onGrid && new_x == item.x && new_y == item.y) {
        if (item.type == Food::Type::kHealthy){
            ++score_;
            PlaceFood(item.type);
            eat_healthy = true;
        }
        else {
            if (item.type == Food::Type::kBonus){
                score_ += 3;
                eat_healthy = false;
            }
            if (item.type == Food::Type::kPoison){
                --score_; 
            }
            // update food properties
            item.onGrid = false; // renderer should not display this item
            item.x = -1;         // even if it attempts to render, the item
            item.y = -1;         // must fall outside the cartesian plane
        }
        snake_.speed += 0.02;
        snake_.GrowBody();
      }
    }
}

/* place food at a random point on grid */
void Game::PlaceFood(Food::Type type)
{
    int x, y;
    while (true){
        x = random_w(engine); 
        y = random_h(engine);
        if (!snake_.IsSnakeCell(x, y)){
            food_[type].x = x;
            food_[type].y = y;
            food_[type].onGrid = true;
            break;
        }
    }
}

std::size_t Game::Score() const { return score_;}
std::size_t Game::SnakeSize() const {return snake_.Size();}