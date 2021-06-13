#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
private:
	sf::RectangleShape _buttonRect;//we need a shape for a button
	sf::Text _text;//also a text in it
public:
	Button(sf::Vector2f, sf::Vector2f , sf::Color , sf::Font& , std::string , sf::Color);
	//getters and setters
	sf::RectangleShape getbuttonRect();
	sf::Text getText();

	void setButtonRect(sf::RectangleShape buttonRect);
	void setText(sf::Text text);

	void draw(sf::RenderWindow &screen);//trebuie declarata ca referinta ca nu se mai poate pune pe stiva inca un window.
	bool isMouseOver(sf::RenderWindow&); //returns if the user clicked inside the button
};

