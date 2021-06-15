#include "Canvas.h"

Canvas::Canvas(sf::Vector2f size, sf::Vector2f pos, sf::Color col)
{
	workSpace.setSize(size);
	workSpace.setPosition(pos);
	workSpace.setFillColor(col);
}

void Canvas::Import(std::string path)
{
	std::cout << "import in the canvas \n";
}

void Canvas::clear()
{
	std::cout << "canvas cleared \n";
}

void Canvas::Export(std::string extension) {
	std::cout << "exported project \n";
}

void Canvas::draw(sf::RenderWindow& win)
{
	win.draw(workSpace);
}

