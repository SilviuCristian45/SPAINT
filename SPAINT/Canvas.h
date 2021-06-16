#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Canvas
{
private:
	sf::RectangleShape workSpace;
public:
	Canvas(sf::Vector2f, sf::Vector2f, sf::Color);
	void Export(std::string, sf::Window&);// export all the canvas contains in an jpeg or png file (specify there)
	void Import(std::string);//		import a png or jpg photo in the canvas (specified by the path given by string)
	void clear();            // clear all the canvas contains
	void draw(sf::RenderWindow&); //metoda pt desenarea canvas-ului 
	bool contains(sf::Vector2i); //metoda care verifica daca avem un anumit punct in interior canvas
};

