#include "Player.h"

Player::Player() {
	shape.setSize(sf::Vector2f(50.f, 50.f));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(0.f, 225.f);
	velocityX = 0.5f;
	velocityY = 0.5f;
	speed = 0.5f;
	}

void Player::handleInput(){
	//Optional: add key input if you want manual control (we gon try)
	velocityX = 0.f;
	velocityY = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
	velocityY = -speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	velocityY = speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
	velocityX = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
	velocityX = speed;
	}
}
void Player::update() {
	shape.move(velocityX, velocityY);
	sf::Vector2f pos = shape.getPosition();
	sf::Vector2f nextPos = pos + sf::Vector2f(velocityX, velocityY);
	//Define boundries - we set window 500x500 and shape is 50x50
	float left =0.f;
	float right = 500.f - shape.getSize().x;
	float top = 0.f;
	float bottom = 500.f - shape.getSize().y;

	//only move within bounds
	if (nextPos.x >= left && nextPos.x <= right && nextPos.y >= top && nextPos.y <= bottom) {
	shape.move(velocityX,velocityY);
	}
}
void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
}
