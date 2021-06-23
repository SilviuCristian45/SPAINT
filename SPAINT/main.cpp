#include <SFML/Graphics.hpp>
#include <iostream>

#include <vector>
#include <string>
#include <Windows.h>

#include "Button.h"
#include "Canvas.h"


void OnClickButton(sf::RenderWindow& window, Button& button, Canvas& canvas, sf::Texture& background,sf::Sprite& backgroundSprite,std::vector<sf::CircleShape> &pixels,std::vector<sf::RectangleShape>& squares) {
    /*FOR MENU BUTTONS */
    if (button.isMouseOver(window) && button.getText().getString() == "save") { //daca a fost dat click pe butonul save
        std::cout << "save button clicked\n";
        canvas.Export(window);
    }
    if (button.isMouseOver(window) && button.getText().getString() == "open") {
        std::cout << "open button clicked\n";
        background.loadFromFile(canvas.Import());
        backgroundSprite.setTexture(background);
    }
    if (button.isMouseOver(window) && button.getText().getString() == "clear") {
        std::cout << "clear button clicked\n";
        pixels.clear();//stergem tot ce e desenat cu mana
        squares.clear();//stergem patratele
        backgroundSprite.setColor(sf::Color::Transparent);//facem transparent background-ul (daca o poza a fost importata)
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

void OnClickShapeBtn(sf::RenderWindow& window, Button& btn, bool& drawShape) {
    if (btn.isMouseOver(window)) {
        //draw a square 
        drawShape = true;
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

    //Button btnNew(sf::Vector2f(375, 30), sf::Vector2f(150, 70), sf::Color::Green, f, "new", sf::Color::White);
    Button btnClear(sf::Vector2f(375, 30), sf::Vector2f(150, 70), sf::Color::Green, f, "clear", sf::Color::White);

    sf::Vector2f btnColorSize(50, 50);

    //Buttons for selecting color 
    Button whiteCol(sf::Vector2f(1000, 137), btnColorSize, sf::Color::White, f, "", sf::Color::White);
    Button redCol(sf::Vector2f(1200, 137), btnColorSize, sf::Color::Red, f, "", sf::Color::Red);
    Button blackCol(sf::Vector2f(1000, 237), btnColorSize, sf::Color::Black, f, "", sf::Color::Black);
    Button blueCol(sf::Vector2f(1200, 237), btnColorSize, sf::Color::Blue, f, "", sf::Color::Blue);
    Button greenCol(sf::Vector2f(1000, 337), btnColorSize, sf::Color::Green, f, "", sf::Color::Green);
    Button purpleCol(sf::Vector2f(1200, 337), btnColorSize, sf::Color::Magenta, f, "", sf::Color::Magenta);

    Button squareButton(sf::Vector2f(1000, 500), sf::Vector2f(100, 50), sf::Color::Transparent, f, "", sf::Color::Magenta);
    Button circleButton(sf::Vector2f(1200, 500), sf::Vector2f(50, 50), sf::Color::Transparent, f, "Circle", sf::Color::Transparent);

    sf::Color currentColor = sf::Color::Black;
    sf::RectangleShape rec(sf::Vector2f(50,50));
    rec.setPosition(1100, 30);
    rec.setOutlineColor(sf::Color::White); rec.setOutlineThickness(1);

    std::vector <sf::CircleShape> pixels;//definim array-ul care va stoca pixelii sub forma de cerculete 
                                            //care va vor fi desenati 
    std::vector <sf::RectangleShape> squareShapes;
    std::vector <sf::CircleShape> circleShapes;

    bool isMouseClicked = false; //stores if mouse is clicked now 
    bool drawASquare = false; //stores if the user want to draw a square on the screen 
    bool drawAcircle = false; //stores if the user want to draw a circle on the screen 

    //sf::RectangleShape workSpace(sf::Vector2f(900,650));//900 650
    Canvas canvas(sf::Vector2f(900, 600), sf::Vector2f(25, 115),sf::Color::White);

    Button btnclearbtnNew(sf::Vector2f(400, 30), sf::Vector2f(150, 70), sf::Color::Green, f, "new", sf::Color::White);

    //pixel dimension (for freestyle drawing)
    const int pixelDimension = 10;

    sf::Texture backgroundImage;
    backgroundImage.create(875, 600);
    sf::Sprite  background;
    background.setPosition(25, 115);

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
                        OnClickButton(window, btnSave, canvas, backgroundImage, background, pixels, squareShapes);//we need to check if the user pressed the save button
                        OnClickButton(window, btnOpen, canvas, backgroundImage, background, pixels, squareShapes);//we need to check if the user pressed the open button
                        OnClickButton(window, btnClear, canvas, backgroundImage, background, pixels, squareShapes);
                        
                        OnClickColorBtn(window, greenCol, currentColor);
                        OnClickColorBtn(window, redCol, currentColor);
                        OnClickColorBtn(window, whiteCol, currentColor);
                        OnClickColorBtn(window, blackCol, currentColor);
                        OnClickColorBtn(window, purpleCol, currentColor);
                        OnClickColorBtn(window, blueCol, currentColor);

                        OnClickShapeBtn(window, squareButton, drawASquare);
                        OnClickShapeBtn(window, circleButton, drawAcircle);
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
                if (drawASquare) {//daca a dat user-ul sa deseneze un patrat 
                    std::cout << "afisam un patrat la pozitia" << mousePos.x << " " << mousePos.y << "\n";
                    int width, height;
                    std::cout << "width = "; std::cin >> width; std::cout << "height = "; std::cin >> height;
                    sf::RectangleShape sh(sf::Vector2f(width, height));
                    sh.setFillColor(currentColor);
                    sh.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
                    squareShapes.push_back(sh);
                    drawASquare = false;
                    isMouseClicked = false;//pt un bug dinasta care activa mouse-ul dupa ce se desena patratul 
                }
                else if (drawAcircle) {
                    std::cout << "afisam un cerc la pozitia" << mousePos.x << " " << mousePos.y << "\n";
                    int radius;
                    std::cout << "radius = "; std::cin >> radius;

                    sf::CircleShape circle(radius);
                    circle.setFillColor(currentColor);
                    circle.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
                    circleShapes.push_back(circle);
                    drawAcircle = false;
                    isMouseClicked = false;
                }
                else { //the user is drawing free hand if no specific shape is selected
                    sf::CircleShape sh2(10);
                    sh2.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
                    sh2.setFillColor(currentColor);
                    pixels.push_back(sh2);
                }
            }
            //std::cout << "Position of text : " << mousePos.x << " " << mousePos.y << std::endl;
        }
        
        rec.setFillColor(currentColor);

        //partea de desenat
        window.clear();//facem clear la ecran (pt update)
        canvas.draw(window);

        window.draw(background);
        window.draw(rec);
        btnSave.draw(window);
        btnOpen.draw(window);
        btnClear.draw(window);
        whiteCol.draw(window);
        redCol.draw(window);
        blueCol.draw(window);
        greenCol.draw(window);
        blackCol.draw(window);
        purpleCol.draw(window);
        squareButton.draw(window);
        circleButton.draw(window);
        for (auto line : pixels) //desenam toate liniile desenate pana acum (sau punctele doar)
            window.draw(line);
        for (auto square : squareShapes)
            window.draw(square);
        for (auto circle : circleShapes)
            window.draw(circle);
        window.display();//afisam tot pe ecran 
    }

    return 0;
}