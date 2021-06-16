#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Button.h"
#include "Canvas.h"

//void MenuButtonOnClick(sf::RenderWindow& window,Button& btnSave, Button& btnOpen, Button& btnNew) {
//    if (btnSave.isMouseOver(window)) {
//        std::cout << "save btn clicked\n";
//    }
//    if (btnOpen.isMouseOver(window)) {
//        std::cout << "open btn clicked\n";
//    }
//    if (btnNew.isMouseOver(window)) {
//        std::cout << "new btn clicked\n";
//    }
//}

void OnClickButton(sf::RenderWindow& window, Button& button, Canvas &canvas) {
    /*FOR MENU BUTTONS */
    if (button.isMouseOver(window) && button.getText().getString() == "save") {//daca a fost dat click pe butonul save
        canvas.Export("jpg", window);
    }

    if (button.isMouseOver(window) && button.getText().getString() == "open") {

    }

    if (button.isMouseOver(window) && button.getText().getString() == "new") {

    }
}

void OnClickColorBtn(sf::RenderWindow& window, Button& button, sf::Color &color) {
    /*FOR COLOR BUTTONS */

    if (button.isMouseOver(window) && button.getbtnColor() == sf::Color::Green) {
        std::cout << " green color selected \n";
        color = sf::Color::Green;
    }
    if (button.isMouseOver(window) && button.getbtnColor() == sf::Color::Red) {
        std::cout << " red color selected \n";
        color = sf::Color::Red;
    }
    if (button.isMouseOver(window) && button.getbtnColor() == sf::Color::Blue) {
        std::cout << " bllue color selected \n";
        color = sf::Color::Blue;
    }
    if (button.isMouseOver(window) && button.getbtnColor() == sf::Color::Black) {
        std::cout << " black color selected \n";
        color = sf::Color::Black;
    }
    if (button.isMouseOver(window) && button.getbtnColor() == sf::Color::Magenta) {
        std::cout << " purple color selected \n";
        color = sf::Color::Magenta;
    }
    if (button.isMouseOver(window) && button.getbtnColor() == sf::Color::White) {
        std::cout << " white color selected \n";
        color = sf::Color::White;
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
    Button btnNew(sf::Vector2f(375, 30), sf::Vector2f(150, 70), sf::Color::Green, f, "new", sf::Color::White);
    
    sf::Vector2f btnColorSize(50, 50);

    //Buttons for selecting color 
    Button whiteCol(sf::Vector2f(1000, 137), btnColorSize, sf::Color::White, f, "", sf::Color::White);
    Button redCol(sf::Vector2f(1200, 137), btnColorSize, sf::Color::Red, f, "", sf::Color::Red);
    Button blackCol(sf::Vector2f(1000, 237), btnColorSize, sf::Color::Black, f, "", sf::Color::Black);
    Button blueCol(sf::Vector2f(1200, 237), btnColorSize, sf::Color::Blue, f, "", sf::Color::Blue);
    Button greenCol(sf::Vector2f(1000, 337), btnColorSize, sf::Color::Green, f, "", sf::Color::Green);
    Button purpleCol(sf::Vector2f(1200, 337), btnColorSize, sf::Color::Magenta, f, "", sf::Color::Magenta);

    sf::Color currentColor = sf::Color::Black;

    std::vector <sf::CircleShape> pixels;//definim array-ul care va stoca pixelii sub forma de patratele 
                                            //care va vor fi desenati 
    bool isMouseClicked = false; //stores if mouse is clicked now 

    //sf::RectangleShape workSpace(sf::Vector2f(900,650));//900 650
    Canvas canvas(sf::Vector2f(900, 600), sf::Vector2f(25, 115),sf::Color::White);

    //pixel dimension (for freestyle drawing)
    const int pixelDimension = 10;
    
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
                        //MenuButtonOnClick(window, btnSave, btnOpen, btnNew);
                        OnClickButton(window, btnSave, canvas);
                        OnClickColorBtn(window, greenCol, currentColor);
                        OnClickColorBtn(window, redCol, currentColor);
                        OnClickColorBtn(window, whiteCol, currentColor);
                        OnClickColorBtn(window, blackCol, currentColor);
                        OnClickColorBtn(window, purpleCol, currentColor);
                        OnClickColorBtn(window, blueCol, currentColor);
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
            if (canvas.contains(mousePos)){//draw a pixel only if it is the canvas
                sf::CircleShape sh2(10);
                sh2.setPosition(sf::Vector2f(mousePos.x,mousePos.y));
                sh2.setFillColor(currentColor);
                pixels.push_back(sh2);
            }
            std::cout << "Position of text : " << mousePos.x << " " << mousePos.y << std::endl;
        }
        
        window.clear();//facem clear la ecran (pt update)
        //partea de desenat
        canvas.draw(window);
        btnSave.draw(window);
        btnOpen.draw(window);
        btnNew.draw(window);
        whiteCol.draw(window);
        redCol.draw(window);
        blueCol.draw(window);
        greenCol.draw(window);
        blackCol.draw(window);
        purpleCol.draw(window);

        for (auto line : pixels) //desenam toate liniile desenate pana acum (sau punctele doar)
            window.draw(line);
        window.display();//afisam tot pe ecran 
    }

    return 0;
}