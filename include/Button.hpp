#pragma once
#include <SFML/Graphics.hpp>

//Placeholder for now
class Button {
private:
	sf::RectangleShape shape;	//visual apperance of said button
	sf::Text text;

public:
	Button();			//constructor
	Button(float x, float y, float width, float height, sf::Font &font, const std::string& text);
	void draw(sf::RenderWindow& window); //draw the button
	bool isClicked(const sf::Vector2f& mousePos) const;
	bool contains(const sf::Vector2f& point) const {
		return shape.getGlobalBounds().contains(point);
	}
	void setHovered(bool hovered) {
		if(hovered) {
			shape.setFillColor(sf::Color(180,180,255));
		} else {
			shape.setFillColor(sf::Color::White);
		}
	}
};
