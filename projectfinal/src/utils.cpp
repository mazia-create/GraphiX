#include "../include/utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
std::vector<sf::Vector2f> loadXYData(const std::string& filename) {
	std::vector<sf::Vector2f> points;
	std::ifstream file(filename);
	if(!file.is_open()){
		std::cerr<< "could not open file: " << filename << std::endl;
		 return points;
	}
	float x,y;
	while (file >> x >> y) {
		points.emplace_back(x,y);
	}
	std::cerr<<"loaded"<<points.size()<<"points from file. \n";
	return points;
}
