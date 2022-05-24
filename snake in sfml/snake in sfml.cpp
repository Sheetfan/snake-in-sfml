#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <string>
#include <sstream>

class Snake: public sf::RectangleShape {
	sf::Vector2f direction;//this stores the direction of the head of the snake
	int speed = 10; // the speed of the snake
	int directionNot = 2; // to make sure the user cann'y move the head of the snake in to its self

public:
	bool active = true;

	Snake() {
		//sets the size, colour and direction of the snake
		this->setSize(sf::Vector2f(35.f, 35.f));
		this->setFillColor(sf::Color::White);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(5.f);
		this->direction = sf::Vector2f(40, 0);
	}
	~Snake() {
	
	}
	void Grow(std::vector<Snake> &length,Snake snake) {
		//it will grow the snake by one
		snake.setPosition(length[length.size() - 1].getPosition());
		length.push_back(Snake(snake));
	}
	
	void movements() {
		//the movement keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && directionNot != 1) {
			this->direction = sf::Vector2f(0, -40);
			directionNot = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && directionNot != 0) {
			this->direction = sf::Vector2f(40, 0);
			directionNot = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && directionNot != 3) {
			this->direction = sf::Vector2f(0, 40);
			directionNot = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && directionNot != 2) {
			this->direction = sf::Vector2f(-40, 0);
			directionNot = 0;
		}
	}
	sf::Vector2f getMovement() {
		return this->direction;
	}
	void movement(int &timerM, std::vector<Snake> &length) {
		/*the snake will move the snake if the speed timer it the same as the game timer*/
		if (timerM == speed) {
			timerM = 0;
			 
			for (int i = 0; i < length.size() - 1; i++) {
				length[i].setPosition(length[i + 1].getPosition());
				
			}
			length[length.size() - 1].move(this->getMovement());
		}
	}

	void setSpeed(sf::Vector2f dir) {
		this->direction = dir;
	}
	void dead(std::vector<Snake>& length, sf::RenderWindow& window, int &timerM) { 
		//if the snake head is greater then the edge of the screen kill the snake
		if (length[length.size() - 1].getPosition().x < 0 - 5.f || length[length.size() - 1].getPosition().x +5.f > window.getSize().x ||
			length[length.size() - 1].getPosition().y - 5.f < 0 || length[length.size() - 1].getPosition().y +5.f > window.getSize().y) {

			this->active = false;

		}
		if (timerM == speed) {
			/*if the speed timer is the same as the game timer if will check if the snake head position is 
			the same as all the other parts of the snake and if it is end game.
			*/
			timerM = 0;
			
			for (int i = 0; i < length.size() - 1; i++) {
				if (length[length.size() - 1].getPosition() == length[i].getPosition()) {
					this->active = false;
					
					break;
				}
			}
		}
		

	}


	
	/*void() {
		
	}*/

};

class Gameplay:public sf::Text{
	sf::Font font;
		
public:
	int score = 0;
	
	Gameplay(std::string file) {
		if(font.loadFromFile(file)) {
			//set the font 
			this->setFont(font);
			this->setPosition(sf::Vector2f(10, 10));
			UI();
		}
		else {
			throw "Can't find font";
		}
			
	}
	//will update UI
	void UI() {
		//will update the score
		std::stringstream ss;
		ss << score;
		this->setString("Score: " + ss.str());
	}
	void increaseScore() {
		this->score++;
	}
	
	
};

class Food: public sf::RectangleShape {
	sf::Vector2f position;
public:
	
	
	Food() {
		//set the postion of the food on screen
		this->setSize(sf::Vector2f(35.f, 35.f));
		this->setFillColor(sf::Color::Red);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(5.f);
		
	}

	//will set a new food Postion
	void randomPosition(std::vector <Snake> length) {
		bool check = true;
		
		/*
			it will generate a new position numbers if the position numbers are the same as the 
			snake position then it will generrate a new number .
		*/
		while (check) {
			this->position.x = (rand() % 25) * 40.f;
			this->position.y = (rand() % 20) * 40.f;
			check = false;
			for (int i = 0; i < length.size(); i++) {
				if (length[i].getPosition() == this->position) {
					check = true;
					break;

				}
				
			}
			this->setPosition(this->position);
		}
		
	}
};

//sets the game up
void set(std::vector<Snake>& length, class Food& food, class Snake& snake, Gameplay& game) {
	game.score = 0;
	length.clear();
	length = { Snake(),Snake(),Snake() };
	length[0].setPosition(2 * 40, 8 * 40);
	length[1].setPosition(3 * 40, 8 * 40);
	length[2].setPosition(4 * 40, 8 * 40);
	food.randomPosition(length);
	snake.setSpeed(sf::Vector2f(40, 0));
	snake.active = true;
}

void eating(std::vector<Snake>& length, Snake& snake, Food& food, Gameplay& game, int &timerM) {
	/*
		if the snake head position is the same as the food position then grow the snake; set a new food position
		and increase the snake score by one
	*/
	if (length[length.size() - 1].getPosition() == food.getPosition()) {
		food.randomPosition(length);
		snake.Grow(length, snake);
		game.increaseScore();

	}
}
int main() {
	srand(time(NULL));
	int timerM  = 0;
	int timerd = 0;

	sf::RenderWindow window(sf::VideoMode(1000,800),"Snake", sf::Style::Close);
	window.setFramerateLimit(60);

	Gameplay game("fonts/NotoSans-Bold.ttf");

	Snake snake;	
	std::vector<Snake> length;;

	Food food;

	set(length,food,snake,game);

	while (window.isOpen()) {	
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !snake.active) {
			set(length, food, snake, game);
		}
		while (snake.active) {

			while (window.pollEvent(event)) {
				if (event.type == event.Closed) {
					window.close();
				}
			}

			//update
			window.clear(sf::Color::Black);
			
			//snake controls
			snake.movements();

			//snake eating
			eating(length, snake, food, game, timerM);

			//snake movement
			snake.movement(timerM, length);
				
			//end game
			snake.dead(length, window, timerd);

			//update score
			game.UI();

			//draw
			for (int i = 0; i < length.size(); i++) {
				window.draw(length[i]);
			}
			
			window.draw(food);
			window.draw(game);
			window.display();
			timerd++;
			timerM++;
		}
		
		
	}

}