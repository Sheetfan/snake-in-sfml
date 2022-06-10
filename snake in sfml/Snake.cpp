#include "Snake.h"

Snake::Snake() {
	this->setSize(sf::Vector2f(35.f, 35.f));
	this->setFillColor(sf::Color::White);
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(5.f);
	this->direction = sf::Vector2f(0, 0);
}

Snake::~Snake() {}

void Snake::Grow(std::vector<Snake>& length, Snake snake) {
	snake.setPosition(length[length.size() - 1].getPosition());
	length.push_back(Snake(snake));
}

void Snake::movements(int count) {
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && directionNot != 1 && this->canMove) {
		this->direction = sf::Vector2f(0, -40);
		directionNot = 3;
		canMove = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && directionNot != 3 && this->canMove) {
		this->direction = sf::Vector2f(0, 40);
		directionNot = 1;
		canMove = false;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && directionNot != 0 && this->canMove) {
		this->direction = sf::Vector2f(40, 0);
		directionNot = 2;
		canMove = false;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && directionNot != 2 && this->canMove) {
		this->direction = sf::Vector2f(-40, 0);
		directionNot = 0;
		canMove = false;
	}

	if (count == this->speed) {
		canMove = true;
	}
}

sf::Vector2f Snake::getMovement() {
	return this->direction;
}

void Snake::movement(float& timerM, std::vector<Snake>& length) {
	/*the snake will move the snake if the speed timer it the same as the game timer*/
	if (timerM >= speed) {
		timerM = 0.0;

		for (int i = 0; i < length.size() - 1; i++) {
			length[i].setPosition(length[i + 1].getPosition());
			}
		length[length.size() - 1].move(this->getMovement());
	}
}

void Snake::setSpeed(sf::Vector2f dir) {
	this->direction = dir;
}

void Snake::dead(std::vector<Snake>& length, sf::RenderWindow& window, float& timerM) {
	//if the snake head is greater then the edge of the screen kill the snake
	if (length[length.size() - 1].getPosition().x < 0 - 5.f || length[length.size() - 1].getPosition().x + 5.f > window.getSize().x ||
		length[length.size() - 1].getPosition().y < 0 - 5.f || length[length.size() - 1].getPosition().y + 5.f > window.getSize().y) {
			this->active = false;
		}
	if (timerM >= speed) {
		/*if the speed timer is the same as the game timer if will check if the snake head position is
		the same as all the other parts of the snake and if it is end game.
		*/
		timerM = 0.0;

		for (int i = 0; i < length.size() - 1; i++) {
			if (length[length.size() - 1].getPosition() == length[i].getPosition()) {
				this->active = false;
					break;
			}
		}
	}
}

void Snake::eating(std::vector<Snake>& length, Food& food, Gameplay& game, Snake snake) {
	/*
		if the snake head position is the same as the food position then grow the snake; set a new food position
		and increase the snake score by one
	*/
	if (length[length.size() - 1].getPosition() == food.getPosition()) {
		food.randomPosition(length);
		length[length.size() - 1].setFillColor(sf::Color::White);
		this->Grow(length, snake);
		length[length.size() - 1].setFillColor(sf::Color(255, 143, 1));
		game.increaseScore();
	}
}
