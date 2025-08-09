#include "../include/app.hpp"
#include "../include/utils.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
//Constuctor: set up SFML window

namespace fs = std::filesystem;

App::App()
	: window(sf::VideoMode(800,600), "GraphiX") {
	loadDataFileButtons();
	addFileButton = Button(600.f,50.f,150.f,40.f, font, "Add File");
	//Future: Load fonts, configure settings, etc.
	//For input box setup
	inputBox.setSize(sf::Vector2f(400,50));
	inputBox.setFillColor(sf::Color(240,240,240));
	inputBox.setOutlineColor(sf::Color::Black);
	inputBox.setOutlineThickness(2);
	inputBox.setPosition(100,200); //Should be center-ish -_-
	//prompt
	inputPrompt.setFont(font);
	inputPrompt.setCharacterSize(14);
	inputPrompt.setFillColor(sf::Color::Black);
	inputPrompt.setString("Enter filename (no spaces, e.g. custom1.txt):");
	inputPrompt.setPosition(100,170);
	
	//Text field
	inputText.setFont(font);
	inputText.setCharacterSize(18);
	inputText.setFillColor(sf::Color::Blue);
	inputText.setPosition(110,210);
	inputText.setString("");
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
		launchPlotWindow("data/points.txt");
		} //fallback / test
		//Handle text input for pop up
		if(showingTextInput && event.type == sf::Event::TextEntered) {
			if(event.text.unicode == '\b') {
				if(!userInput.empty())
					userInput.pop_back(); //backspace
			}
			else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
				if(!userInput.empty()) {
					std::ofstream outFile("data/" + userInput);
					if (outFile) {
						fileNames.push_back("data/" + userInput);
						loadDataFileButtons();
					}
				userInput = "";
				showingTextInput = false;
			}
		}	else if (event.text.unicode < 128 && userInput.size() <30) {
			char entered = static_cast<char>(event.text.unicode);
			if (entered != ' ') {		//NO SPACES
				userInput += entered;  }
			}
			inputText.setString(userInput);
			std::cout<<"[DEBUG] Typing : " <<userInput<<std::endl;
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		for (size_t i = 0; i < fileButtons.size(); i++) {
			if(fileButtons[i].isClicked(mousePos)) {
				launchPlotWindow(fileNames[i]); //grabs file name
			}
		}
		if (addFileButton.isClicked(mousePos)) {
			showingTextInput = true;
			userInput = "";
			inputText.setString("");
		std::cout<< "[DEBUG] Add File button clicked" << std::endl;
			}

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
	//plotter.draw(window); //draws grid (once plotter is ready)
	/*testButton.draw(window); //draw button<< was our test button gyal 	*/
	//window.display(); //shows everything on screen
	for (auto& btn : fileButtons) {
		btn.draw(window);
	
	}
	addFileButton.draw(window);
	window.display();
	if (showingTextInput) {
		window.draw(inputBox);
		window.draw(inputText);
	}
}
//we gon change a few things - make pop up window add gridlines to pop up window
void App::launchPlotWindow(const std::string& filePath){
	sf::RenderWindow plotWindow(sf::VideoMode(800,600),"GraphiX Plot View");
	Plotter plotter;
	//load data from file
	std::vector<sf::Vector2f> data = loadXYData(filePath);
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

//main window GUI
void App::loadDataFileButtons() {
	fileButtons.clear(); //our little safety net
	fileNames.clear(); //same as ^^
	//positioning
	float yOffset = 50.f;
	float buttonHeight = 40.f;
	float Buttonspacing = 10.f;
	if (!font.loadFromFile("arial.ttf")) {
		std::cerr << "Failed to load font. \n";
		return;
		}
	for (const auto& entry : fs::directory_iterator("data")) {
		if(!entry.is_regular_file()) continue;
		std::string ext = entry.path().extension().string();
		if (ext != ".txt" &&  ext != ".dat") continue;
		std::string label = entry.path().filename().string();
		std::string filePath = entry.path().string();
	
		Button btn(50.f, yOffset, 200.f, buttonHeight, font, label);
		fileButtons.push_back(btn);
		fileNames.push_back(filePath);

		yOffset += buttonHeight + Buttonspacing;
	
		}
}
std::string App::promptAndCreateDataFile() {
	std::string fileName;
	std::cout << "Enter name for new data file(no spaces, e.g. 'custom1.txt'):";
	std::cin>> fileName;

	if (fileName.empty()) return "";

	//open file and write default set of points
	std::string fullPath = "data/" + fileName;
	std::ofstream outFile(fullPath);
	if (!outFile) {
		std::cerr << "could not create a file. \n";
		return "";
	}
	
	outFile << "0 0\n1 2\n2 4\n"; //sample data
	outFile.close();
	std::cout << "Created" << fullPath << "\n";

	return fullPath;
}
