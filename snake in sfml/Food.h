#pragma once

#include "Snake.h"

class Snake;
class Food : public sf::RectangleShape {
	sf::Vector2f position;
public:

	//set the postion of the food on screen
	Food();

	//will set a new food Postion
	void randomPosition(std::vector <Snake> length);
};
