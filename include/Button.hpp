#pragma once
#include <SFML/Graphics.hpp>

//Placeholder for now
class Button {
private:
	sf::RectangleShape shape;	//visual apperance of said button

public:
	Button();			//constructor
	void draw(sf::RenderWindow& window); //draw the button
};
