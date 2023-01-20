#include <iostream>
#include "game.h"
#include "controller.h"
#include "renderer.h"

int main ()
{
	constexpr size_t kScreenWidth = 768;
	constexpr size_t kScreenHeight = 768;
	constexpr size_t kGridWidth = 60;
	constexpr size_t kGridHeight = 60;
	constexpr size_t kFrameRate = 60; 

	Controller controller;
	Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
	Game game(kGridWidth, kGridHeight);
	game.Run(controller, renderer, kFrameRate);

	std::cout << "Game over!\n";
	std::cout << "Score: " << game.Score() << "\n";
	std::cout << "Size: " << game.SnakeSize() << "\n";
}