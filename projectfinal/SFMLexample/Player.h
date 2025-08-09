#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
public:
	Player();
	
	void handleInput();
	void update();
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape shape;
	float velocityX;
	float velocityY;
	float speed;
};

#endif
