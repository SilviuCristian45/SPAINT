#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Button.h"

void MenuButtonOnClick(sf::RenderWindow& window,Button& btnSave, Button& btnOpen, Button& btnNew) {
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
    window.setFramerateLimit(60);
    sf::Font f;

    if (!f.loadFromFile("BalooTammudu2-Regular.ttf"))
        std::cout << "could not load font\n";

    Button btnSave(sf::Vector2f(25,30), sf::Vector2f(150,70), sf::Color::Green, f, "save", sf::Color::White);
    Button btnOpen(sf::Vector2f(200, 30), sf::Vector2f(150, 70), sf::Color::Green, f, "open", sf::Color::White);
    Button btnNew(sf::Vector2f(400, 30), sf::Vector2f(150, 70), sf::Color::Green, f, "new", sf::Color::White);
    Button whiteCol(sf::Vector2f(1083, 137), sf::Vector2f(50, 50), sf::Color::White, f, "", sf::Color::White);
    
    std::vector <sf::RectangleShape> lines;//definim array-ul care va stoca linia care va fi desenata (endpoint-urile)
    bool isMouseClicked = false; //stores if mouse is clicked now 

    sf::RectangleShape workSpace(sf::Vector2f(900,650));
    workSpace.setPosition(sf::Vector2f(25, 120));
    workSpace.setFillColor(sf::Color::Blue);
    workSpace.setOutlineColor(sf::Color::White);

    //main loop 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))//while we have events
        {
            switch (event.type)
            {
                case sf::Event::Closed: // if the user pressed X in order to exit the program
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed: //if the user pressed any mouse button
                    if (event.mouseButton.button == sf::Mouse::Left) {//if the user pressed left click
                        MenuButtonOnClick(window, btnSave, btnOpen, btnNew);

                        if (!isMouseClicked) { //if the mouse is not clicked yet (so no dragging) 
                            isMouseClicked = true; //the mouse was clicked 
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.key.code == sf::Mouse::Left) {//if it was released from left click 
                        isMouseClicked = false; //mouse left is no longer pressed 
                    }
                    //std::cout << "release la mouse click stanga";
                    break;
                default:
                    break;
            }
        }

        //LOGIC 
        if (isMouseClicked) {//if the mouse is still clicked theen set the 2 element of line (basicly dragging)
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //get mousePosition
            sf::RectangleShape sh(sf::Vector2f(10, 10));
            sh.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
            lines.push_back(sh);
        }
        
        window.clear();
        window.draw(workSpace);
        btnSave.draw(window);
        btnOpen.draw(window);
        btnNew.draw(window);
        whiteCol.draw(window);
        for (auto line : lines) //desenam toate liniile desenate pana acum (sau punctele doar)
            window.draw(line);
        window.display();
    }

    return 0;
}