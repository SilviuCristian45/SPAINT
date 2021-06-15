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

void OnClickMenuButton(sf::RenderWindow& window, Button& button, Canvas &canvas) {
    if (button.isMouseOver(window) && button.getText().getString() == "save") {//daca a fost dat click pe butonul save
        canvas.Export("png");

        sf::Vector2u windowSize = window.getSize();//luam dimensiunea window-ului
        
        //parte din cod care preia o imagine cu tot ecranul aplicatiei
        sf::Texture texture;
        texture.create(windowSize.x, windowSize.y);
        texture.update(window);

        sf::Image screenshot = texture.copyToImage();

        //o sa avem alta imagine in care o sa o cropam doar zona de lucru din imaginea de mai sus
        sf::Image result;
        result.create(875, 600);
        result.copy(screenshot, 0, 0, sf::IntRect(25, 115, 900, 713), true);
        
        try
        {
            result.saveToFile("result.png");
        }
        catch (const std::exception& ex)
        {
            std::cout << "eroare la salvarea proiectului" << ex.what() << "\n";
        }
        
        
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
    
    std::vector <sf::RectangleShape> pixels;//definim array-ul care va stoca pixelii sub forma de patratele 
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
                        OnClickMenuButton(window, btnSave, canvas);
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
            //draw a pixel 
            sf::RectangleShape sh(sf::Vector2f(pixelDimension, pixelDimension));
            sh.setFillColor(sf::Color::Black);//set pixel color
            sh.setPosition(sf::Vector2f(mousePos.x, mousePos.y));//set pixel position 
            pixels.push_back(sh);
            std::cout << "Position of text : " << mousePos.x << " " << mousePos.y << std::endl;
        }
        
        window.clear();//facem clear la ecran (pt update)
        //partea de desenat
        canvas.draw(window);
        btnSave.draw(window);
        btnOpen.draw(window);
        btnNew.draw(window);
        whiteCol.draw(window);
        for (auto line : pixels) //desenam toate liniile desenate pana acum (sau punctele doar)
            window.draw(line);
        window.display();//afisam tot pe ecran 
    }

    return 0;
}