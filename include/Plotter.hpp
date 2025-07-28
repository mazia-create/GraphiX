#pragma once
#include <SFML/Graphics.hpp>

//Plotter class handles drawing the gridlines in the background

class Plotter {
public:
	//draws gridlines onto given window
	void draw(sf::RenderWindow& window);
	void setData(const std::vector<sf::Vector2f>& data);
	
private:
	std::vector<sf::Vector2f> plotPoints;
}; //; apparently needed after defining classes or structs (remember this future Mikayla -.-)


