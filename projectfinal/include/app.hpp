#pragma once 					\\file is included once per compilation
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
	//Button testButton; //<< Placeholder UI button
	std::vector<Button> fileButtons; // << Buttons for each .txt/.dat file in /data folder
	std::vector<std::string> fileNames; //corresponding names
	sf::Font font;	//shared font
//	Button addFileButton; //Button to open file creation prompt (fingers crossed this works)
	//^^sucks, so going with a different route vvvv
//	std::string promptAndCreateDataFile(); //creates new data file & returns path
	bool isCreatingFile = false;	//Typing mode flag
	std::string userInputBuffer = ""; //Stores typed filename
	sf::RectangleShape inputBox;	//Creates the input box to type in
	sf::Text inputText;		//Displays the typed text
	Button createFileButton;	//New UI Button to start input
	Button addFileButton;
	//for input pop-up
	bool showingTextInput = false;
	std::string userInput = "";
	sf::Text inputPrompt;

public:
	/*brief constructor: new app object
	initializes window and subcomponents
	*/
	App();
	/*
	starts the main loop of the app
	*/
	void run();
	std::string promptAndCreateDataFile();
	//opens a separate window for plotting
	void launchPlotWindow(const std::string& filePath); //pop-up plot view
	
private:
	//Handles window events like closing window
	void processEvents();

	//updates app state
	void update();
	
	//draws all objects to screen
	void render();
	
	//scan folder and make buttons
	void loadDataFileButtons();
};
