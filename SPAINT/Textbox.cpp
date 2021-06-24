#include "Textbox.h"

Textbox::Textbox(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& f)
{
	rect.setPosition(position);
	rect.setSize(size);
	rect.setFillColor(sf::Color::Transparent);
	this->text.setPosition(position);
	this->text.setString(text);
	this->text.setFont(f);
}

sf::Text Textbox::getText()
{
	return text;
}

bool Textbox::getSelected()
{
	return selected;
}

void Textbox::checkIfSelected(sf::RenderWindow& window)
{
	sf::Vector2f workSpacePostion = rect.getPosition();
	sf::Vector2f workSpaceSize = rect.getSize();
	sf::Vector2i point = sf::Mouse::getPosition(window);
	std::cout << selected << "\n";
	selected = (point.x > workSpacePostion.x && point.x < workSpacePostion.x + workSpaceSize.x
		&& point.y > workSpacePostion.y && point.y < workSpacePostion.y + workSpaceSize.y);
	if (selected)
		text.setString(text.getString() + "_");
	else {
		std::string newString = text.getString();
		if (*newString.end() == '_')
			newString.pop_back();
	}
}


void Textbox::setText(std::string text)
{
	this->text.setString(text);
}

void Textbox::draw(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(text);
}
