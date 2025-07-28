#pragma once \\file is included once per compilation
#include <SFML/Graphics.hpp>
#include "Plotter.hpp"
#include "Button.hpp"

/*

Class App
Briefs the main app controller for GraphiX program (cool name I know)

This class' purpose is to manage the SFML window, handles events, and coordinates
all rendering and updates (grid, UI elements, etc.)

*/

class App {
private:
	sf::RenderWindow window; // <<Main SFML window
	Plotter plotter; // << Should give us some grid lines
	Button testButton; //<< Placeholder UI button

public:
	/*brief constructor: new app object
	initializes window and subcomponents
	*/
	App();
	/*
	starts the main loop of the app
	*/
	void run();
	//opens a separate window for plotting
	void launchPlotWindow();
private:
	//Handles window events like closing window
	void processEvents();

	//updates app state
	void update();
	
	//draws all objects to screen
	void render();
};
