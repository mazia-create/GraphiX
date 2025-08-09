#include <SFML/Graphics.hpp>
#include "Player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(500,500), "Movement Example");
	
	Player player;
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			}
		player.handleInput();
		player.update();
		
		window.clear();
		player.draw(window);
		window.display();
	}
	return 0;
}
