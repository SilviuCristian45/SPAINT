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
	if (selected) //daca user-ul a selectat textbox-ul
		text.setString(text.getString() + "_"); //adaugam la final un _ pt a fi mai vizibil faptul ca e textbox-ul selectat
	else {
		//stergem _ din string pentru a marca faptul ca nu mai e selectat textbox-ul
		std::string newString = text.getString();
		int tt = newString.find("_");//stocam pozitia underscore-ului
		if(tt != -1){
			newString.erase(tt);//stergem underscore-ul
			text.setString(newString);
		}
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
