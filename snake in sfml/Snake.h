#pragma once

#include "Gameplay.h"
#include "Food.h"

class Gameplay;
class Food;
class Snake : public sf::RectangleShape {
	sf::Vector2f direction;//this stores the direction of the head of the snake
	int speed = 10; // the speed of the snake
	int directionNot = 2; // to make sure the user cann'y move the head of the snake in to its self
	bool canMove = true; //
public:
	bool active = true;

	//sets the size, colour and direction of the snake
	Snake();

	~Snake();

	//it will grow the snake by one
	void Grow(std::vector<Snake>& length, Snake snake);

	//the movement keys
	void movements(int count);

	sf::Vector2f getMovement();

	void movement(float& timerM, std::vector<Snake>& length);

	void setSpeed(sf::Vector2f dir);

	void dead(std::vector<Snake>& length, sf::RenderWindow& window, float& timerM);
	
	void eating(std::vector<Snake>& length, Food& food, Gameplay& game, Snake snake);
};
