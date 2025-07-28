#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class PlotData {

public:
	std::vector<sf::vector2f> points; //makes variable called points holds a list of 2D points
	
	bool loadFromFile(const std::string& filename);
};

