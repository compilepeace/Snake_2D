#include <iostream>
#include "renderer.h"

Renderer::Renderer (const size_t sw,
                    const size_t sh,
                    const size_t gw,
                    const size_t gh):
screen_width(sw), screen_height(sh),
grid_width(gw), grid_height(gh)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL could not be inititalized (" << SDL_GetError() << ")\n";
    }

    // create a window
    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN);

    if (sdl_window == nullptr) {
      std::cerr << "Window could not be created. (" << SDL_GetError() << ")\n";
    }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created. (" << SDL_GetError() << ")\n";
  }
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Snake const &snake, std::vector<Food> const &food)
{
  SDL_Rect block;
  block.w = screen_width / grid_width;    // width of a single block/cell
  block.h = screen_height / grid_height;  // height of a single block/cell

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food items
  for (auto &item : food) {
    if (item.onGrid) {
      switch (item.type) {
      case Food::Type::kHealthy:
        // 0xffcc00
        SDL_SetRenderDrawColor(sdl_renderer, 0x3F, 0xA4, 0x7D, 0xFF);
        break;
      case Food::Type::kBonus:
        SDL_SetRenderDrawColor(sdl_renderer, 0xF9, 0xC5, 0x52, 0xFF);
        break;
      case Food::Type::kPoison:
        SDL_SetRenderDrawColor(sdl_renderer, 0xBA, 0x4D, 0x2D, 0xFF);
        break;
      }

      block.x = item.x * block.w;
      block.y = item.y * block.h;
      // std::cout << "F(" << block.x << "," <<  block.y << ")\n";
      SDL_RenderFillRect(sdl_renderer, &block);
    }
  }

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xEC, 0xE9, 0xD4, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
    //std::cout << "snake body: " << block.x << "," <<  block.y << ")\n" ;
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
    //std::cout << "snake head rendering(" << block.x << "," <<  block.y << ")";
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
    std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}