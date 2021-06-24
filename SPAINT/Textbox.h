#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Textbox
{
private:
	sf::RectangleShape rect;
	sf::Text text;
	bool selected = false;
public:
	Textbox(sf::Vector2f, sf::Vector2f, std::string, sf::Font&);
	sf::Text getText();
	bool getSelected();
	void checkIfSelected(sf::RenderWindow&);
	void setText(std::string);
	void draw(sf::RenderWindow&);
};

