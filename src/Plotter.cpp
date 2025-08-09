#include "../include/Plotter.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <sstream>
//code updated > added adjusted point drawing and tick marks/ labels
//Draw light gray gridlines across entire window >> updated to add margins and origin lines
//Grid spacing set to 50 pixels vertically and horizontally

void Plotter::draw(sf::RenderWindow& window) {
	if (plotPoints.empty()) {
	std::cerr<< "no data points, exiting draw function. \n";
	return;
	}
	/*const int spacing = 50; //Distance between grid lines */
	const float marginLeft = 50.f; //space for y-axis labels (to make it pretty ;D)
	const float marginBottom = 50.f; //space for x-axis labels (we getting professional wit it)
	const float marginTop = 20.f; // Leaves space at top of plot
	const float marginRight = 20.f; //make it cleaan
	
	const float plotWidth = window.getSize().x - marginLeft - marginRight;
	const float plotHeight = window.getSize().y - marginTop - marginBottom;
	//Calculate data bounds
	float minX = plotPoints[0].x, maxX = plotPoints[0].x;
	float minY = plotPoints[0].y, maxY = plotPoints[0].y;
	for (const auto& pt : plotPoints) {
		if (pt.x < minX) minX = pt.x;
		if (pt.x > maxX) maxX = pt.x;
		if (pt.y < minY) minY = pt.y;
		if (pt.y > maxY) maxY = pt.y;
	}
	float xRange = maxX - minX;
	float yRange = maxY - minY;
	float xScale = plotWidth / (xRange == 0 ? 1 : xRange);
	float yScale = plotHeight / (yRange == 0 ? 1 : yRange);
	
	//GRID LINES~~
	//ticks
	const int numTicks = 10;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cerr << "could not load font 'arial.ttf'. make sure in same folder as executable pls .\n";
		return;
	}
	
	//Draw vertical lines within plot area (add dynamic ranges)
	for (int i = 0; i <=numTicks; i++) {
		float xVal = minX + i * xRange / numTicks;
		float yVal = minY + i * yRange / numTicks;

		float xPix = marginLeft + (xVal - minX) * xScale;
		float yPix = marginTop + plotHeight - (yVal - minY) * yScale;
		//Vertical grid lines
		sf::Vertex yline[] = {
			sf::Vertex(sf::Vector2f(xPix, marginTop), sf::Color(220,220,220)), //Top
			sf::Vertex(sf::Vector2f(xPix, marginTop + plotHeight), sf::Color(220,220,220)) //bottom
	};
	window.draw(yline, 2, sf:: Lines);
	//Draw horizontal lines within plot area
		sf::Vertex hline[] = {
			sf::Vertex(sf::Vector2f(marginLeft ,yPix), sf::Color(220,220,220)), //left
			sf::Vertex(sf::Vector2f(marginLeft + plotWidth, yPix), sf::Color(220,220,220)) //right
	};
	window.draw(hline,2,sf::Lines);

	//Tick labels (shesh this is a lot)
	//sf::Text xText(std::to_string(std::round(yVal * 100) / 100), font, 12);
	std::stringstream ssX;
	ssX<<std::fixed<<std::setprecision(2)<<yVal; //x-axis labels
	sf::Text xText(ssX.str(),font, 12);
	xText.setPosition (xPix - 10, marginTop + plotHeight + 5);
	xText.setFillColor (sf::Color::Black);
	window.draw(xText);
	
	//sf::Text yText(std::to_string(std::round(xVal *100) / 100), font, 12);
	std::stringstream ssY;
	ssY<<std::fixed<<std::setprecision(2)<<xVal; //y-axis labels
	sf::Text yText(ssY.str(),font,12);
	yText.setPosition (marginLeft - 40, yPix - 8);
	yText.setFillColor (sf::Color::Black);
	window.draw(yText);
}	
	//make axes
	sf::Vertex xAxis[] = {
		sf::Vertex(sf::Vector2f(marginLeft, marginTop+ plotHeight), sf::Color::Black),
		sf::Vertex(sf::Vector2f(marginLeft + plotWidth, marginTop + plotHeight), sf::Color::Black)
	};
	sf::Vertex yAxis[] = {
		sf::Vertex(sf::Vector2f(marginLeft, marginTop), sf::Color::Black),
		sf::Vertex(sf::Vector2f(marginLeft, marginTop + plotHeight), sf::Color::Black)
	};
	window.draw(xAxis, 2, sf::Lines);
	window.draw(yAxis, 2, sf::Lines);

	//Axis Labels
	sf::Text xLabel("X-Axis",font,14);
	xLabel.setPosition(marginLeft + plotWidth / 2 - 30, marginTop + plotHeight + 30);
	xLabel.setFillColor(sf::Color::Black);
	window.draw(xLabel);

	sf::Text yLabel("Y-Axis",font, 14);
	yLabel.setRotation(-90);
	yLabel.setPosition(15, marginTop + plotHeight / 2 + 30);
	yLabel.setFillColor(sf::Color::Black);
	window.draw(yLabel);
	
	
	//plot points and line strip
	/*float scale = spacing; //each unit should equal one grid box >> what we used to use to scale */
	sf::VertexArray lineStrip(sf::LineStrip); // starts empty

	for (const auto& pt : plotPoints) {
		float px = marginLeft + (pt.x- minX) * xScale;
		float py = marginTop + plotHeight -( pt.y-minY )* yScale;
	
		//Draw red circle at each point
		sf::CircleShape circle(3); //radius of 3 pixels
		circle.setFillColor(sf::Color::Red);
		circle.setOrigin(3, 3);
		circle.setPosition(px,py);
		window.draw(circle);
		//for line strip
		lineStrip.append(sf::Vertex(sf::Vector2f(px,py),sf::Color::Red));

		}
		if (lineStrip.getVertexCount() > 1)
			window.draw(lineStrip);
		/*float windowHeight = static_cast<float>(window.getSize().y);
		float flippedY = windowHeight - (pt.y * scale);
		circle.setPosition(pt.x * scale - 3, flippedY -3); //offset to center the circle */
		std::cout<<"Number of points:" << plotPoints.size() << std::endl;
	
		
	
	if (lineStrip.getVertexCount() > 1) {
	window.draw(lineStrip);
}
}
void Plotter::setData(const std::vector<sf::Vector2f>& data) {
	plotPoints = data; //copy the data into private vector
	}
