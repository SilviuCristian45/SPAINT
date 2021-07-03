#include <SFML/Graphics.hpp>
#include <iostream>

#include <vector>
#include <string>
#include <Windows.h>

#include "Button.h"
#include "Canvas.h"
#include "Textbox.h"
#include <stack>

void OnClickButton(sf::RenderWindow& window, Button& button, Canvas& canvas, sf::Texture& background,sf::Sprite& backgroundSprite,std::vector<sf::CircleShape> &pixels,std::vector<sf::RectangleShape>& squares, std::vector<sf::CircleShape>& circleShapes, std::vector<sf::CircleShape>& triangleShapes, std::vector<sf::VertexArray>& lines) {
    /*FOR MENU BUTTONS */
    if (button.isMouseOver(window) && button.getText().getString() == "save") { //daca a fost dat click pe butonul save
        std::cout << "save button clicked\n";
        canvas.Export(window);
    }
    if (button.isMouseOver(window) && button.getText().getString() == "open") {
        std::cout << "open button clicked\n";
        background.loadFromFile(canvas.Import());
        backgroundSprite.setTexture(background);
        backgroundSprite.setColor(sf::Color(255,255,255,255));
    }
    if (button.isMouseOver(window) && button.getText().getString() == "clear") {
        std::cout << "clear button clicked\n";
        pixels.clear();//stergem tot ce e desenat cu mana
        squares.clear();//stergem patratele
        circleShapes.clear();//stergem cercurile
        triangleShapes.clear();//stergem triunghiurile
        backgroundSprite.setColor(sf::Color::Transparent);//facem transparent background-ul (daca o poza a fost importata)
        lines.clear();
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

void OnClickEraserBtn(sf::RenderWindow& window, Button& btn, bool& eraserEnabled) {
    if (btn.isMouseOver(window))
        eraserEnabled = !eraserEnabled;
}

double Distance(sf::Vector2f A, sf::Vector2f B) // returns distance between two points
{
    return sqrt((B.y - A.y) * (B.y - A.y) + (B.x - A.x) * (B.x - A.x));
}

//function that returns the area of a Triangle defined by these points A(x1,y1) B(x2,y2) C(x3,y3)
long double AreaTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return abs((x1 * static_cast<long double>(y2 - y3) + x2 * static_cast<long double>(y3 - y1) + x3 * static_cast<long double>(y1 - y2)) / 2.0);
}

void DeleteWithEraser(sf::RenderWindow& window, std::vector<sf::CircleShape>& pixels, std::vector<sf::RectangleShape>& squares, std::vector<sf::CircleShape>& circleShapes, std::vector<sf::CircleShape>& triangleShapes, std::vector<sf::VertexArray>& lines, float pixelRadius) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); //luam pozitia mouse-ului de pe window

    auto startItPixels = pixels.begin();
    //daca e cazul sa stergem puncte 
    for (int i = 0; i < pixels.size(); i++) { //parcurgem toate punctele desenate pana acum 
        sf::Vector2f pixelPos = pixels[i].getPosition();//stocam pozitia punctului curent
        if (Distance(pixelPos,sf::Vector2f(mousePos.x,mousePos.y)) <= pixelRadius) { //daca radiera(cursorul) intersecteaza punctul
            pixels.erase(startItPixels + i);//stergem punctul 
        }
    }
    auto startItSquares = squares.begin();
    //daca e cazul sa stergem patrate 
    for (int i = 0; i < squares.size(); i++) {
        sf::Vector2f squarePos = squares[i].getPosition();
        sf::Vector2f squareSize = squares[i].getSize();
        if (mousePos.x > squarePos.x && mousePos.x < squarePos.x + squareSize.x &&
                        mousePos.y > squarePos.y && mousePos.y < squarePos.y + squareSize.y) {
            squares.erase(startItSquares + i);
        }
    }
    auto startItCircles = circleShapes.begin();
    //daca e cazul sa stergem cercuri 
    for (int i = 0; i < circleShapes.size(); i++) {
        sf::Vector2f circlePos = circleShapes[i].getPosition();
        double radius = circleShapes[i].getRadius();

        if (Distance(circlePos, sf::Vector2f(mousePos.x, mousePos.y)) <= radius) {
            circleShapes.erase(startItCircles + i);
        }
    }
    auto startItTriangles = triangleShapes.begin();
    sf::Vector2f pointA, pointB, pointC;
    //daca e cazul sa stergem triunghiuri
    for (int i = 0; i < triangleShapes.size(); i++) {
        sf::Vector2f center = triangleShapes[i].getPosition();
        double radius = triangleShapes[i].getRadius();

        //obtinem punctele de la capetele din triunghiul echilateral (nu e chiar echilateral dar aproximam)
        pointA.x = center.x;
        pointA.y = center.y - radius;

        pointB.x = center.x - radius / 2;
        pointB.y = center.y + radius * std::sqrt(3) / 2;

        pointC.x = center.x + radius / 2;
        pointC.y = center.y + radius * std::sqrt(3) / 2;

        //metoda de verificare cu arii 
        long double area = AreaTriangle(pointA.x, pointA.y, pointB.x, pointB.y, pointC.x, pointC.y);
        long double a1 = AreaTriangle(pointA.x, pointA.y, pointB.x, pointB.y, mousePos.x, mousePos.y);
        long double a2 = AreaTriangle(pointB.x, pointB.y, mousePos.x, mousePos.y, pointC.x, pointC.y);
        long double a3 = AreaTriangle(pointC.x, pointC.y, mousePos.x, mousePos.y, pointA.x, pointA.y);

        if (a1 + a2 + a3 == area) {//inseamna ca radiera este in interiorul triunghiului 
            triangleShapes.erase(startItTriangles + i);
        }
    }
    //daca e cazul sa stergem linii 
    auto startItLines = lines.begin();
    for (int i = 0; i < lines.size(); i++) {
        sf::Vertex v1 = lines[i][0];
        sf::Vertex v2 = lines[i][1];
        double slope = (v1.position.y - v2.position.y) / (v1.position.x - v2.position.x);
        //daca distanta de la mouse pana la slope e mai mica decat 0.1 atunci inseamna ca trebuie stearsa linia 
        //avem nevoie de ecuatia dreptei 
        //y = m * x + n 
        long n = v2.position.y - slope * v2.position.x; //aflam pe n inlocuind in formula de mai sus pe x si y cu coordonatele punctului v2
        //=> m*x - y + n == 0 - asta e ecuatia pt care folosim formula distantei de la un punct (pozitia radierei) la o dreapta 
        long distance = std::abs(slope * mousePos.x - 1 * mousePos.y + n) / std::sqrt(slope * slope + 1);
        if (distance < 1)
            lines.erase(startItLines + i);
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
    Button triangleButton(sf::Vector2f(1000, 600), sf::Vector2f(100, 50), sf::Color::Transparent, f, "Triangle", sf::Color::Transparent);
    Button lineButton(sf::Vector2f(1200, 600), sf::Vector2f(100, 50), sf::Color::Transparent, f, "Line", sf::Color::Transparent);
    Button eraserButton(sf::Vector2f(1000, 35), btnColorSize, sf::Color::White, f, "", sf::Color::Transparent);

    sf::Color currentColor = sf::Color::Black;
    sf::RectangleShape rec(sf::Vector2f(50,50));
    rec.setPosition(1200, 30);
    rec.setOutlineColor(sf::Color::White); rec.setOutlineThickness(1);

    std::vector <sf::CircleShape> pixels;//definim array-ul care va stoca pixelii sub forma de cerculete 
                                            //care va vor fi desenati 
    std::vector <sf::RectangleShape> squareShapes;
    std::vector <sf::CircleShape> circleShapes;
    std::vector <sf::CircleShape> triangles;
    std::vector <sf::VertexArray> lines;
    std::vector <sf::CircleShape> erasedPixels;

    bool isMouseClicked = false; //stores if mouse is clicked now 
    bool drawASquare = false; //stores if the user want to draw a square on the screen 
    bool drawAcircle = false; //stores if the user want to draw a circle on the screen 
    bool drawAtriangle = false;
    bool drawALine = false;
    bool eraserEnabled = false;

    //sf::RectangleShape workSpace(sf::Vector2f(900,650));//900 650
    Canvas canvas(sf::Vector2f(900, 600), sf::Vector2f(25, 115),sf::Color::White);

    Button btnclearbtnNew(sf::Vector2f(400, 30), sf::Vector2f(150, 70), sf::Color::Green, f, "new", sf::Color::White);

    //pixel dimension (for freestyle drawing)
    const int pixelDimension = 10;

    sf::Texture backgroundImage;
    backgroundImage.create(875, 600);
    sf::Sprite  background;
    background.setPosition(25, 115);

    Textbox sizeTextBox(sf::Vector2f(1125,40),sf::Vector2f(200,40), "10", f);
    int lineSize = 10;

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
                case sf::Event::MouseButtonReleased:
                    if (event.key.code == sf::Mouse::Left) {//if it was released from left click 
                        isMouseClicked = false; //mouse left is no longer pressed 
                    }
                    break;
                case sf::Event::MouseButtonPressed: //if the user pressed any mouse button
                    if (event.mouseButton.button == sf::Mouse::Left) {//if the user pressed left click
                        OnClickButton(window, btnSave, canvas, backgroundImage, background, pixels, squareShapes, circleShapes, triangles, lines);//we need to check if the user pressed the save button
                        OnClickButton(window, btnOpen, canvas, backgroundImage, background, pixels, squareShapes, circleShapes, triangles, lines);//we need to check if the user pressed the open button
                        OnClickButton(window, btnClear, canvas, backgroundImage, background, pixels, squareShapes, circleShapes, triangles, lines);
                        
                        OnClickColorBtn(window, greenCol, currentColor);
                        OnClickColorBtn(window, redCol, currentColor);
                        OnClickColorBtn(window, whiteCol, currentColor);
                        OnClickColorBtn(window, blackCol, currentColor);
                        OnClickColorBtn(window, purpleCol, currentColor);
                        OnClickColorBtn(window, blueCol, currentColor);
                        
                        OnClickShapeBtn(window, squareButton, drawASquare);
                        OnClickShapeBtn(window, circleButton, drawAcircle);
                        OnClickShapeBtn(window, triangleButton, drawAtriangle);
                        OnClickShapeBtn(window, lineButton, drawALine);
                        OnClickEraserBtn(window, eraserButton, eraserEnabled);

                        sizeTextBox.checkIfSelected(window);
                        if (!isMouseClicked) { //if the mouse is not clicked yet (so no dragging) 
                            isMouseClicked = true; //the mouse was clicked 
                        }
                    }
                    break;
                
                case sf::Event::TextEntered:
                    if(event.text.unicode < 128 && sizeTextBox.getSelected()) {//daca a apasat user-ul pe un caracter si daca e textbox-ul selectat
                        if (event.text.unicode == 8) {//daca a apasat backspace
                            std::cout << "backspace" << std::endl;
                            std::string newString = sizeTextBox.getText().getString(); //preluam ce avem in texbox
                            if (newString.size() > 0) { //daca e ceva in textbox
                                newString.pop_back(); //stergem _ de la final 
                                newString.pop_back(); // stergem ultima cifra
                                newString += "_"; //adaugam la final _ ca sa fie efectul de selectie vizibil 
                                sizeTextBox.setText(newString);//actualizam string-ul pe ecran 
                            }
                        }
                        else { //daca a introdus un caracter altul decat backspace 
                            char c = static_cast<char>(event.text.unicode); //stocam caracterul corespunzator tastei (convertim codul ascii in char)
                            std::string newString = sizeTextBox.getText().getString(); //preluam ce avem in textbox 
                            newString.pop_back(); //stergem _ de la finalul din texbox
                            sizeTextBox.setText(newString + c + '_'); //adaugam la final caracterul introddus + _ pt efectul de selectie  
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        //LOGIC 
        if (isMouseClicked) {//if the mouse is still clicked theen set the 2 element of line (basicly dragging)
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //get mousePosition
            if (canvas.contains(mousePos)) {//draw a pixel only if it is the canvas
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
                    int radius, optionEllipse;
                    std::cout << "radius = "; std::cin >> radius;
                    std::cout << "Sa fie elipsa ?  1- da ||| 0 - nu : "; std::cin >> optionEllipse;

                    sf::CircleShape circle(radius);
                    circle.setFillColor(currentColor);
                    circle.setPosition(sf::Vector2f(mousePos.x, mousePos.y));

                    if (optionEllipse == 1) circle.setScale(2, 1);//in caz ca utilizatorul doreste sa fie elipsa

                    circleShapes.push_back(circle);
                    drawAcircle = false;
                    isMouseClicked = false;
                }
                else if (drawAtriangle) {
                    std::cout << "afisam un triunghi la pozitia" << mousePos.x << " " << mousePos.y << "\n";

                    int latura;
                    std::cout << "latura triunghi = "; std::cin >> latura;

                    sf::CircleShape sh(latura);
                    sh.setPointCount(3);
                    sh.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
                    sh.setFillColor(currentColor);

                    triangles.push_back(sh);
                    drawAtriangle = false;
                    isMouseClicked = false;
                }
                else if (drawALine) {
                    std::cout << "afisam o linie la pozitia" << mousePos.x << " " << mousePos.y << "\n";
                    if (lines.size() == 0 || lines[lines.size() - 1].getVertexCount() == 2) {
                        sf::VertexArray newLine(sf::LinesStrip);//o linie plina formata din 2 capete (2 vertexi )
                        newLine.append(sf::Vertex(sf::Vector2f(mousePos.x, mousePos.y), currentColor));//primul capat al liniei 
                        lines.push_back(newLine);// adaugam la 
                        std::cout << "primul punct\n";
                        isMouseClicked = false; //mouse-ul nu mai e apasat la punctul acesta 
                    }
                    else {
                        if (lines[lines.size() - 1].getVertexCount() == 1) {//daca e inserat primul vertex in ultima linie desenata
                            lines[lines.size() - 1].append(sf::Vertex(sf::Vector2f(mousePos.x, mousePos.y), currentColor));//al doilea capat al liniei 
                            drawALine = false; //e terminata linia de desenat, deci nu mai desenam
                            std::cout << "al doilea punct\n";
                        }
                    }
                }
                else if (eraserEnabled) {
                    std::cout << "eraser enabled\n";
                    std::string p = sizeTextBox.getText().getString();//preluam valoarea scrisa in textbox 
                    float pixelRadius = std::atof(p.c_str());
                    DeleteWithEraser(window, pixels, squareShapes, circleShapes, triangles, lines, pixelRadius);
                }
                else {//the user is drawing free hand if no specific shape is selected

                    std::string p = sizeTextBox.getText().getString();//preluam valoarea scrisa in textbox 
                    lineSize = std::atoi(p.c_str());//convertim in int 

                    sf::CircleShape sh2(lineSize); //la raza pixelului setam valoarea din texbox
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

        sizeTextBox.draw(window);

        btnSave.draw(window);
        btnOpen.draw(window);
        btnClear.draw(window);

        whiteCol.draw(window);
        eraserButton.draw(window);
        redCol.draw(window);
        blueCol.draw(window);
        greenCol.draw(window);
        blackCol.draw(window);
        purpleCol.draw(window);
        squareButton.draw(window);
        circleButton.draw(window);
        triangleButton.draw(window);
        lineButton.draw(window);

        for (auto line : pixels) //desenam toate liniile desenate pana acum (sau punctele doar)
            window.draw(line);
        for (auto square : squareShapes)
            window.draw(square);
        for (auto circle : circleShapes)
            window.draw(circle);
        for (auto triangle : triangles)
            window.draw(triangle);
        for (auto line : lines)
            window.draw(line);
        for (auto erasedPixel : erasedPixels)
            window.draw(erasedPixel);

        window.display();//afisam tot pe ecran 
    }

    return 0;
}