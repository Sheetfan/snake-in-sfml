#pragma once
#include <array>
#include <vector>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <string>
#include <sstream>
#include "Snake.h"
#include "Food.h"

class Snake;
class Food;
class Gameplay :public sf::Text {
	sf::Font font;

public:
	int score = 0;

	Gameplay(std::string file);
	//will update UI
	void UI();
	void increaseScore();
	//sets the game up
	void set(std::vector<Snake>& length, class Food& food, class Snake& snake);

};

