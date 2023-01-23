#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "game.h"
#include "controller.h"
#include "renderer.h"

// Useful data types
typedef struct Player {
	std::string name;
	size_t score;
} Player;

// function prototypes
void GetHighScore(const std::string &fname, Player &score);
void SetHighScore(const std::string &fname, const Player &score);

int main ()
{
	constexpr size_t kScreenWidth = 720;
	constexpr size_t kScreenHeight = 720;
	constexpr size_t kGridWidth = kScreenWidth/15;
	constexpr size_t kGridHeight = kScreenHeight/15;
	constexpr size_t kFrameRate = 60; 
	const std::string kScoreFile{"./snake.highscore"}; 

	Player rockstar;
	GetHighScore(kScoreFile, rockstar);

	Player player;
	std::cout << "Please enter your name: ";
	std::cin >> player.name;
	player.score = 0;

	Controller controller;
	Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
	Game game(kGridWidth, kGridHeight);
	game.Run(controller, renderer, kFrameRate);

	player.score = game.Score();
	std::cout << "Game over!\n";
	std::cout << player.name << "'s snake size: " << game.SnakeSize() << "\n";
	std::cout << player.name << "'s score: " << player.score << "\n";

	// update highscore
	if (rockstar.score < player.score){
		rockstar = player;
		SetHighScore(kScoreFile, player);
	}
	
	std::cout << "High score: " << rockstar.score << " (" << rockstar.name << ")\n"; 
}

/*
	fills Score structure (2nd parameter) with highscore read from file fname.
	Sets score = 0 if fname does not exist and prints a message at std::cerr
*/
void GetHighScore(const std::string &fname, Player &player)
{
	// open file for reading
	std::fstream fis(fname, std::ios::in);
	if (!fis.is_open()){
		// highscore file not found
		player.score = 0;
		//std::cerr << fname << ": could not find previous highscores.\n";
	}
	else{
		// read highscore
		std::string line;
		getline(fis, line);
		std::istringstream ss(line);
		ss >> player.name >> player.score;		// capture name and highscore
		fis.close();
	}
}

void SetHighScore(const std::string &fname, const Player &player)
{
		// write player's highscore to file
		std::fstream fos(fname, std::ios::out | std::ios::trunc);
		if (!fos.is_open()){
			std::cerr << fname << ": cannot be opened for writing, exiting without writing highscore\n";
		}
		else{
			fos << player.name << " " << player.score << "\n";
		}
}