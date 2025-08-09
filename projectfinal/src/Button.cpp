#include "../include/Button.hpp"

//Default constructor: creates blue rectangle
Button::Button() {

	//default constructor
	shape.setSize(sf::Vector2f(100.f,40.f));
	shape.setFillColor(sf::Color(200,200,200));
	shape.setPosition(0.f,0.f);
	text.setString("");
}

//Custom constructor w/ font + label
Button::Button(float x, float y, float width, float height, sf::Font& font, const std::string& label){
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(x,y); //should be bottom right
	shape.setFillColor(sf::Color(100,149,237)); //Cornflower blue ;D
	
	text.setFont(font);
	text.setString(label);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Black);

	//center text inside button
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	text.setPosition(x+width / 2.0f, y + height / 2.0f);
}

bool Button::isClicked(const sf::Vector2f& mousePos) const {
	return shape.getGlobalBounds().contains(mousePos);
	}
//Draw button to window

void Button::draw(sf::RenderWindow& window){
	window.draw(shape);
	window.draw(text);
}
