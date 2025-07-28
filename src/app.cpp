#include "../include/app.hpp"
#include "../include/utils.hpp"
//Constuctor: set up SFML window

App::App()
	: window(sf::VideoMode(800,600), "GraphiX") {
	//Future: Load fonts, configure settings, etc.
}

//Main loop: runs until the window is closed

void App::run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
		window.close();
		return;
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
		launchPlotWindow();
		}
	}
		update();
		render();
}
}
//Handles basic window events (ie. close)
void App::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		}
}
//placeholder: could update UI state or animation 

void App::update() {

	//idk ;3
}

//clear screen and draw component
void App::render() {
	window.clear(sf::Color::White); //background is our chronically used white ;D
	plotter.draw(window); //draws grid (once plotter is ready)
	testButton.draw(window); //draw button
	window.display(); //shows everything on screen
}
//we gon change a few things - make pop up window add gridlines to pop up window
void App::launchPlotWindow(){
	sf::RenderWindow plotWindow(sf::VideoMode(800,600),"GraphiX Plot View");
	Plotter plotter;
	//load data from file
	std::vector<sf::Vector2f> data = loadXYData("data/points.txt");
	plotter.setData(data);
	
	while (plotWindow.isOpen()){
		sf::Event event;
		while (plotWindow.pollEvent(event)) {
			if(event.type == sf::Event::Closed){
				plotWindow.close();
			}
		}
	plotWindow.clear(sf::Color::White); //clear screen
	plotter.draw(plotWindow); //draw grid and points
	plotWindow.display(); //display what we drew
	}
}
