#include "../include/app.hpp"
#include "../include/utils.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
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

	//points input UI
	pointsInputBox.setSize(sf::Vector2f(400,100));
	pointsInputBox.setFillColor(sf::Color(240,240,240));
	pointsInputBox.setOutlineColor(sf::Color::Black);
	pointsInputBox.setOutlineThickness(2);
	pointsInputBox.setPosition(100,280);

	pointsInputPrompt.setFont(font);
	pointsInputPrompt.setCharacterSize(14);
	pointsInputPrompt.setFillColor(sf::Color::Black);
	pointsInputPrompt.setString("Enter points (ex. 0 0; 1 2; 2 4)");
	pointsInputPrompt.setPosition(100,260);

	pointsInputText.setFont(font);
	pointsInputText.setCharacterSize(16);
	pointsInputText.setFillColor(sf::Color::Black);
	pointsInputText.setPosition(110,285);
	//Header bar
	const float W = static_cast<float>(window.getSize().x);
	const float H = static_cast<float>(window.getSize().y);
	const float HeaderH = 80.f;

	headerBar.setSize({W, HeaderH});
	headerBar.setFillColor(sf::Color(28,35,52)); //Nice navy color ;D
	headerBar.setPosition(0.f,0.f);

	//Brand
	brand.setFont(font);
	brand.setString("GraphiX");
	brand.setCharacterSize(36);
	brand.setFillColor(sf::Color::White);
	brand.setPosition(24.f,18.f);
	
	//Subtitle
	subbrand.setFont(font);
	subbrand.setString("The app that plots!");
	subbrand.setCharacterSize(14);
	subbrand.setFillColor(sf::Color(190,198,214));
	subbrand.setPosition(26.f,56.f);
	
	//Build a small rising line aligned with title/brand
	//struggling with animating how much is drawn
	const float x0 = brand.getPosition().x + 5.f;
	const float y0 = brand.getPosition().y + 8.f;
	const float w = 240.f;
	const float h = 28.f;

	//Make a rising stair or curve(if possible) func {for looks ;) }
	heroLine.clear();
	for (int i=0; i<=24; ++i) {
		float t = static_cast<float>(i)/24.f;
		float x = x0 + t * w;
		float y = y0 + h * (1.f - t) + 6.f * std::sin(t*6.28318f*0.5f); //2pi = 6.28318, 0.5 slows it down
		heroLine.push_back(sf::Vertex({x,y}, sf::Color(100,200,255))); //aqua color
}	
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

		//Hover (for aesthetics)
		if(event.type == sf::Event::MouseMoved) {
			sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x),
					static_cast<float>(event.mouseMove.y));
			for (auto &btn : fileButtons) {
				btn.setHovered(btn.contains(mousePos));
			}
			addFileButton.setHovered(addFileButton.contains(mousePos));
		}
		
		//Handle text input for pop up
		if(showingTextInput && event.type == sf::Event::TextEntered) {
		std::string& buf = focusOnFilename ? userInput : userInputPoints;

			if(event.text.unicode == '\b') {
				if(!buf.empty())
					buf.pop_back(); //backspace
			}
			else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
				if (focusOnFilename) {
					focusOnFilename = false;
				} else {
					//create file with points
					std::string fname = userInput;

					if(!fname.empty()) {
					if(fname.find('.') == std::string::npos) fname += ".txt";
					std::string fullPath = "data/" + fname;

					std::ofstream out(fullPath);
					if (out) {
						std::string pts = userInputPoints;
						for (char &c : pts) if (c == ',' || c == ';' || c =='\t') c=' ';
						std::istringstream iss(pts);
						double v; std::vector<double> nums;
						while (iss >> v) nums.push_back(v);
						for (size_t i = 0; i +1 < nums.size(); i+=2)
							out << nums[i] << " " << nums[i+1] << "\n";
					}
					//refresh UI
					userInput.clear();
					userInputPoints.clear();
					inputText.setString("");
					pointsInputText.setString("");
					focusOnFilename = true;
					showingTextInput = false;
					loadDataFileButtons();
					}
				}
			}
			else if (event.text.unicode >= 32 && event.text.unicode < 127) {
				char ch = static_cast<char>(event.text.unicode);
				if (focusOnFilename) { if ( ch != ' ') buf.push_back(ch); } //no space
				else buf.push_back(ch);
			}
	inputText.setString(userInput + (focusOnFilename ? "_" : ""));
	pointsInputText.setString(userInputPoints + (!focusOnFilename ? "_" : ""));
	
	}
	
	//clicks (file buttons and add file)
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		
		//use window-mapped coordinates to make life easier
		sf::Vector2f mousePos = window.mapPixelToCoords(
			sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
			);
		//open plot for a file button
		for (size_t i = 0; i < fileButtons.size(); ++i) {
			if(fileButtons[i].isClicked(mousePos)) {
				launchPlotWindow(fileNames[i]);
				break;
			}
		}
		//open the dual-input pop up
		if (addFileButton.isClicked(mousePos)) {
			showingTextInput = true;
			userInput.clear();
			userInputPoints.clear();
			inputText.setString("");
			pointsInputText.setString("");
			focusOnFilename = true;
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
	//Draw grid (under everything)
	float W = static_cast<float>(window.getSize().x);
	float H = static_cast<float>(window.getSize().y);
	for (float x = 0.f; x <= W; x += gridSpacing) {
		sf::Vertex v[] = {
			sf::Vertex({x,0.f}, gridColor),
			sf::Vertex({x,H}, gridColor)
		};
		window.draw(v,2,sf::Lines);
	}
	for (float y = 0.f; y <= H; y += gridSpacing) {
		sf::Vertex v[] {
			sf::Vertex({0.f,y}, gridColor),
			sf::Vertex({W,y}, gridColor)
		};
		window.draw(v,2,sf::Lines);
	}
	//Header
	window.draw(headerBar);
	window.draw(brand);
	window.draw(subbrand);

	//animate line reveal
	heroAnim += heroSpeed * 0.016f; //approx. ~60fps
	if (heroAnim > 1.f) heroAnim = 1.f;

	//draw only first N vertices based on "progress"
	size_t N = static_cast<size_t>(heroAnim * heroLine.size());
	if (N >= 2) window.draw(heroLine.data(),N, sf::LineStrip);
	
	//Side panel (for aesthetics)
	sf::RectangleShape sidePanel;
	sidePanel.setPosition(16.f,96.f);
	sidePanel.setSize(sf::Vector2f(280.f, H - 120.f));
	sidePanel.setFillColor(sf::Color(255,255,255, 230)); // semi-transparent
	sidePanel.setOutlineColor(sf::Color(220,224,230)); //light gray/grey (idk difference)
	sidePanel.setOutlineThickness(1.f);
	window.draw(sidePanel);
	//Button time ;)
	for (auto& btn : fileButtons) {
		btn.draw(window);
	
	}
	//add file button
	addFileButton.draw(window);
	//text box for other UI
	if (showingTextInput) {
		window.draw(inputBox);
		window.draw(inputText);

		//draw points input UI
		window.draw(pointsInputBox);
		window.draw(pointsInputText);
		window.draw(pointsInputPrompt);
		
		//show which box is active
		if (focusOnFilename) {
			inputBox.setOutlineColor(sf::Color::Blue);
			pointsInputBox.setOutlineColor(sf::Color::Black);
		} else {
			inputBox.setOutlineColor(sf::Color::Black);
			pointsInputBox.setOutlineColor(sf::Color::Blue);
		}
	}
	window.display();
}
//we gon change a few things - make pop up window add gridlines to pop up window
void App::launchPlotWindow(const std::string& filePath){
	sf::RenderWindow plotWindow(sf::VideoMode(800,600),"GraphiX Plot View");
	Plotter plotter;
	
	bool savePNG = false;
	std::string pendingPath;
	//load data from file
	std::vector<sf::Vector2f> data = loadXYData(filePath);
	plotter.setData(data);
	
	while (plotWindow.isOpen()){
		sf::Event event;
		while (plotWindow.pollEvent(event)) {
			if(event.type == sf::Event::Closed){
				plotWindow.close();
			}
		if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::S)) {
			//derive output path from data file name
			auto posSlash = filePath.find_last_of("/\\");
			std::string base = (posSlash == std::string::npos)
					? filePath
					: filePath.substr(posSlash + 1);
			auto posDot = base.find_last_of('.');
			if(posDot != std::string::npos) base = base.substr(0, posDot);
			
			pendingPath = std::string("data/") + base + ".png";
			savePNG = true; //defer capture until after display
			std::cout << "[S] will save" << pendingPath << "\n";
		} //closes event type


		} //end pollevent
	plotWindow.clear(sf::Color::White); //clear screen
	plotter.draw(plotWindow); //draw grid and points
	plotWindow.display(); //display what we drew


	//snapshot saving block
	if(savePNG) {
		sf::Texture tex;
		tex.create(plotWindow.getSize().x, plotWindow.getSize().y);
		tex.update(plotWindow);
		sf::Image img = tex.copyToImage();
		if (img.saveToFile(pendingPath)) {
			std::cout << "Saved plot to" << pendingPath << "\n";
		} else {
			std::cout << "Failed to save plot image\n";
		}
		savePNG = false; //reset

	}
}

}
//main window GUI
void App::loadDataFileButtons() {
	fileButtons.clear(); //our little safety net
	fileNames.clear(); //same as ^^
	//positioning
	float yOffset = 100.f;
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
