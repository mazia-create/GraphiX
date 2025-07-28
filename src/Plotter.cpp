#include "../include/Plotter.hpp"
#include <iostream>
//Draw light gray gridlines across entire window
//Grid spacing set to 50 pixels vertically and horizontally

void Plotter::draw(sf::RenderWindow& window) {
	const int spacing = 50; //Distance between grid lines

	//Draw vertical lines
	for (int x = 0; x < static_cast<int>(window.getSize().x); x += spacing) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(x,0), sf::Color(220,220,220)), //Top
			sf::Vertex(sf::Vector2f(x, static_cast<float>(window.getSize().y)), sf::Color(220,220,220)) //bottom
	};
	window.draw(line, 2, sf:: Lines);
	}

	//Draw horizontal lines
	for(int y=0; y < static_cast<int>(window.getSize().y); y+= spacing) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(0,y), sf::Color(220,220,220)), //left
			sf::Vertex(sf::Vector2f(static_cast<float>(window.getSize().x), y), sf::Color(220,220,220)) //right
	};
	window.draw(line,2,sf::Lines);
}
	std::cout<<"Number of points:" << plotPoints.size() <<std::endl;
	for (const auto& pt : plotPoints) {
		sf::CircleShape circle(3); //radius of 3 pixels
		circle.setFillColor(sf::Color::Red);
		float scale = 50.0f; //scale up data points for better visibility
		circle.setPosition(pt.x * scale - 3, pt.y*scale -3); //offset to center the circle
		std::cout<<"Drawing point at: ("<<pt.x*scale<<","<<pt.y*scale<<")\n";
		window.draw(circle);
	}
}
void Plotter::setData(const std::vector<sf::Vector2f>& data) {
	plotPoints = data; //copy the data into private vector
	}
