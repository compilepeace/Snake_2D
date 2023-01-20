
#include <iostream>
#include "game.h"

Game::Game(std::size_t width, std::size_t height): 
    snake_(width, height), score_(0),
    engine(dev()),
    random_w(0, static_cast<int>(width-1)),
    random_h(0, static_cast<int>(width-1))
{
    std::cout << "Game constructor\n";
    // create a grid and PlaceFood at random point in grid window
    PlaceFood();
}

/* execute game loop */
void Game::Run(Controller &controller, Renderer &renderer, const size_t frameRate)
{
    std::cout << "Starting game loop\n";
    int desiredFrameDuration = 1000/frameRate;
    Uint64 frameStartTick; 
    Uint64 frameEndTick;  
    int frameCount = 0;
    int timeElapsed = 0;

    Uint64 titleTimePoint = SDL_GetTicks64();
    // game loop: input, update, render 
    // Each iteration of game loop corresponds to a Frame in game
    bool running = true;
    while (running){
        frameStartTick = SDL_GetTicks64();

        controller.HandleInput(running, snake_);   // input
        UpdateState();                      // update
        renderer.Render(snake_, food_);                  // render

        frameEndTick = SDL_GetTicks64();

        /*
            after 1 second has passed (1000 milliseconds) 
        */
        if ((frameEndTick - titleTimePoint) >= 1000){ 
            std::cout << "1 second lapsed, fps:" << frameCount << "\n";
            renderer.UpdateWindowTitle(Score(), frameCount);       // update the window title every second 
            titleTimePoint = frameEndTick;
            frameCount = 0;
        }

        /*
            To find k seconds delay for each iteration/frame. 
            desiredFrameDuration = 1000/frameRate
            timeElapsed
        */ 
        timeElapsed = frameStartTick - frameEndTick;
        if (timeElapsed < desiredFrameDuration) {
            SDL_Delay(desiredFrameDuration - timeElapsed);
        }

        ++frameCount;
    }
}

/*
    If snake head lands over food coordinates -
        - SnakeGrow();
        - PlaceFood();
*/
void Game::UpdateState()
{
    if (!snake_.alive) return;

    snake_.Update();

    //std::cout << "UpdateState(" << snake_.head_x << "," <<  snake_.head_y << ")\n";

    // snake lands on food
    /*
#define EPSILON 1e-7
    auto new_x = fabs(snake_.head_x - food_.x);
    auto new_y = fabs(snake_.head_y - food_.y);
    if (new_x < EPSILON && new_y < EPSILON){
    */
    int new_x = static_cast<int>(snake_.head_x);
    int new_y = static_cast<int>(snake_.head_y);
    if (new_x == food_.x && new_y == food_.y){
        std::cerr << "Snake eat food at: " << snake_.head_x << "," << snake_.head_y << "\n"; 
        ++score_;
        snake_.speed += 0.02;
        snake_.GrowBody();
        PlaceFood();
    }
}

/* place food at a random point on grid */
bool Game::PlaceFood() {
    SDL_Point pos;
    while (true){
        pos.x = random_w(engine); 
        pos.y = random_h(engine);
        if (!snake_.IsSnakeCell(pos)){
            food_.x = pos.x;
            food_.y = pos.y;
            break;
        }
    }
    return true;
}

std::size_t Game::Score() const { return score_;}
std::size_t Game::SnakeSize() const {return snake_.Size();}