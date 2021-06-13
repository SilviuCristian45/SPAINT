#include <SFML/Graphics.hpp>
#include <iostream>

#include "Button.h"

void MenuButtonOnClick(sf::RenderWindow& window, Button& btnSave, Button& btnOpen, Button& btnNew) {
    if (btnSave.isMouseOver(window)) {
        std::cout << "save btn clicked\n";
    }
    if (btnOpen.isMouseOver(window)) {
        std::cout << "open btn clicked\n";
    }
    if (btnNew.isMouseOver(window)) {
        std::cout << "new btn clicked\n";
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SPAINT!");//initialize the window
    sf::Font f;

    if (!f.loadFromFile("BalooTammudu2-Regular.ttf"))
        std::cout << "could not load font\n";

    Button btnSave(sf::Vector2f(25,30), sf::Vector2f(150,70), sf::Color::Green, f, "save", sf::Color::White);
    Button btnOpen(sf::Vector2f(200, 30), sf::Vector2f(150, 70), sf::Color::Green, f, "open", sf::Color::White);
    Button btnNew(sf::Vector2f(400, 30), sf::Vector2f(150, 70), sf::Color::Green, f, "new", sf::Color::White);

    //main loop 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))//while we have events
        {
            if (event.type == sf::Event::Closed)//if the user pressed X in order to exit the program
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//if the user pressed click
                MenuButtonOnClick(window, btnSave, btnOpen, btnNew);
        }
        
        window.clear();
        btnSave.draw(window);
        btnOpen.draw(window);
        btnNew.draw(window);
        window.display();
    }

    return 0;
}