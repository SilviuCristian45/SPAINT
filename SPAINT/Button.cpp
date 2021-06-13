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

//set-eri
void Button::setButtonRect(sf::RectangleShape buttonRect)
{
	_buttonRect = buttonRect;
}

void Button::setText(sf::Text text)
{
	_text = text;
}

//metoda pt desenarea pe ecran a butonului 
void Button::draw(sf::RenderWindow &screen)
{
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





