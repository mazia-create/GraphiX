#include "../include/Button.hpp"

//Default constructor: creates blue rectangle

Button::Button(){
	shape.setSize(sf::Vector2f(100.f, 40.f));
	shape.setPosition(650.f,500.f); //should be bottom right
	shape.setFillColor(sf::Color(100,149,237)); //Cornflower blue ;D
}

//Draw button to window

void Button::draw(sf::RenderWindow& window){
	window.draw(shape);
}
