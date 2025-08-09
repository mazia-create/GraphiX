#include "../include/PlotData.hpp"
#include <fstream>
#include <sstream>
#include<iostream>

bool PlotData::loadFromFile(const std::string& filename) {
	points.clear(); //clear old data
	
	std::ifstream infile(filename);
	if (!infile.is_open()) {
		std::cerr << "Error: Could not open " << filename << std:: endl;
		return false;
	}
	float x,y;
	std::string line;
	while (std::getline(infile, line)) {
		std::istringstream.iss(line);
		if(!(iss >> x >> y)) {
			std::cerr << "Warning: Invalid line skipped: " << line << std::endl;
			continue;
		}
		points.emplace_back(x,y); //add point to vector
	}
	infile.close();
	return true;

}
