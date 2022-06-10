#include "Gameplay.h"

Gameplay::Gameplay(std::string file) {
	if (font.loadFromFile(file)) {
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
void Gameplay::UI() {
	//will update the score
	std::stringstream ss;
	ss << score;
	this->setString("Score: " + ss.str());
}

void Gameplay::increaseScore() {
	this->score++;
}

//sets the game up
void Gameplay::set(std::vector<Snake>& length, class Food& food, class Snake& snake) {
	score = 0;
	length.clear();
	length = { Snake(),Snake(),Snake() };
	length[0].setPosition(2 * 40, 8 * 40);
	length[1].setPosition(3 * 40, 8 * 40);
	length[2].setPosition(4 * 40, 8 * 40);
	length[length.size() - 1].setFillColor(sf::Color(255, 143, 1));
	food.randomPosition(length);
	snake.setSpeed(sf::Vector2f(40, 0));
	snake.active = true;
}
