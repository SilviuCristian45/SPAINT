#include "Button.h"

/*Constructor*/
	/**rectPosition - pozitia butonului
	* btnRectSize  - dimensiunea butonului
	* btnColor     - culoarea de background a butonului
	* textFont     - fontul textului prin referinta. ca se creeaza altul pe stiva care nu e incarcat si atunci e null => probleme
	* text         - textul butonului
	* textColor    - culoarea textului butonului
	*/
Button::Button(sf::Vector2f rectPosition, sf::Vector2f btnRectSize, sf::Color btnColor, sf::Font &textFont, std::string text, sf::Color textColor) {
	_buttonRect.setPosition(rectPosition);
	_buttonRect.setSize(btnRectSize);
	_buttonRect.setFillColor(btnColor);
	_buttonRect.setOutlineColor(sf::Color::White);
	_buttonRect.setOutlineThickness(1);
	//setam pozitia textului in interiorul butonului (la mijlocul rectshape-ului)
	//std::cout << "Position of text : " << rectPosition.x + btnRectSize.x / 2 << " " << rectPosition.y + btnRectSize.y / 2 << std::endl;
	_text.setPosition(rectPosition.x + btnRectSize.x/4, rectPosition.y + btnRectSize.y/4);
	_text.setFont(textFont);
	_text.setString(text);
	_text.setFillColor(textColor);
}

//Gett-eri
sf::RectangleShape Button::getbuttonRect(){
	return _buttonRect;
}

sf::Text Button::getText(){
	return _text;
}

sf::Color Button::getbtnColor()
{
	return _buttonRect.getFillColor();
}

//set-eri
void Button::setButtonRect(sf::RectangleShape buttonRect)
{
	_buttonRect = buttonRect;
}

void Button::setText(sf::Text text)
{
	_text = text;
}

void Button::setColor(sf::Color col)
{
	_buttonRect.setFillColor(col);
}

//metoda pt desenarea pe ecran a butonului 
void Button::draw(sf::RenderWindow &screen)
{
	if (_text.getString() == "Circle"){//daca e cumva un  buton sub forma de cerc
		sf::CircleShape sh(25);
		sh.setPosition(_buttonRect.getPosition());
		sh.setFillColor(sf::Color::Transparent);
		sh.setOutlineColor(sf::Color::White);
		sh.setOutlineThickness(1);
		screen.draw(sh);
	}
	else if (_text.getString() == "Triangle") {//daca e cumva un buton sub forma de triunghi 
		sf::CircleShape sh(40);
		sh.setPosition(_buttonRect.getPosition());
		sh.setPointCount(3);
		sh.setFillColor(sf::Color::Transparent);
		sh.setOutlineColor(sf::Color::White);
		sh.setOutlineThickness(1);
		screen.draw(sh);
	}
	else
		screen.draw(_buttonRect);
	screen.draw(_text);
}

bool Button::isMouseOver(sf::RenderWindow &window)
{
	//luam coordonatele mouse-ului 
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f btnPos = _buttonRect.getPosition();
	sf::Vector2f btnSize = _buttonRect.getSize();

	return (mousePos.x > btnPos.x && mousePos.x < btnPos.x + btnSize.x) &&
		(mousePos.y > btnPos.y && mousePos.y < btnPos.y + btnSize.y);
}





