#include "Gameplay.h"
#include "Snake.h"
#include "Food.h"
#include <iostream>

int main() {
	srand(time(NULL));
	float timerM  = 0.0;
	float timerd = 0;
	//float dt = 0.0;
	sf::Time timePerFrame = sf::seconds(1.f / 620.f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1000,800),"Snake", sf::Style::Close);
	//window.setFramerateLimit(60);
	
	Gameplay game("fonts/NotoSans-Bold.ttf");

	Snake snake;	
	std::vector<Snake> length;

	Food food;

	game.set(length,food,snake);

	while (window.isOpen()) {	
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == event.Closed) {
				window.close();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !snake.active) {
			game.set(length, food, snake);
		}
		while (snake.active) {
			timeSinceLastUpdate += clock.restart();
			std::cout << timeSinceLastUpdate.asSeconds() << "\n";
			//dt = clock.restart().asSeconds();
			while (window.pollEvent(event)) {
				if (event.type == event.Closed) {
					window.close();
				}
			}

			//update
			while (timeSinceLastUpdate > timePerFrame)
			{
				timeSinceLastUpdate -= timePerFrame;
				//processEvents();
				while (window.pollEvent(event)) {
					if (event.type == event.Closed) {
						window.close();
					}
				}
				window.clear(sf::Color::Black);

				//snake controls
				snake.movements(timerM);

				//snake eating
				snake.eating(length, food, game, snake);

				//snake movement
				snake.movement(timerM, length);

				//end game
				snake.dead(length, window, timerd);

				//update score
				game.UI();

				timerd += timePerFrame.asSeconds() * 58.82352941;
				timerM += timePerFrame.asSeconds() * 58.82352941;

			}
			
			//draw
			for (int i = 0; i < length.size(); i++) {
				window.draw(length[i]);
			}
			
			window.draw(food);
			window.draw(game);
			window.display();
			/*timerd += dt * 58.82352941;
			timerM += dt * 58.82352941;*/
		}
	}
}