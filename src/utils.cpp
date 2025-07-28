#include "../include/utils.hpp"
#include <fstream>
#include <sstream>

std::vector<sf::Vector2f> loadXYData(const std::string& filename) {
	std::vector<sf::Vector2f> points;
	std::ifstream file(filename);
	if(!file.is_open()) return points;

	float x,y;
	while (file >> x >> y) {
		points.emplace_back(x,y);
	}
	return points;
}
