#include "Food.h"

	Food::Food() {
		this->setSize(sf::Vector2f(35.f, 35.f));
		this->setFillColor(sf::Color::Red);
		this->setOutlineColor(sf::Color::Black);
		this->setOutlineThickness(5.f);
	}

	void Food::randomPosition(std::vector <Snake> length) {
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