#include "Canvas.h"
#include <windows.h>
#include "Utils.h"

Canvas::Canvas(sf::Vector2f size, sf::Vector2f pos, sf::Color col)
{
	workSpace.setSize(size);
	workSpace.setPosition(pos);
	workSpace.setFillColor(col);
}

std::string Canvas::Import()
{
    std::string path = openfile();
    std::cout << path << "\n";
    MessageBoxA(NULL, "Imagine importata cu succes!!", "Mesaj", MB_OKCANCEL | MB_ICONINFORMATION);
    return path;
}

void Canvas::clear()
{
	std::cout << "canvas cleared \n";
}

void Canvas::Export(sf::Window &window) {
	std::cout << "exported project \n";
    sf::Vector2u windowSize = window.getSize();//luam dimensiunea window-ului

    //parte din cod care preia o imagine cu tot ecranul aplicatiei intr-o textura 
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(window);

    sf::Image screenshot = texture.copyToImage();// convertim in imagine textura de mai sus 

    //o sa avem alta imagine in care o sa o cropam doar zona de lucru din imaginea de mai sus
    sf::Image result;
    result.create(875, 600);
    result.copy(screenshot, 0, 0, sf::IntRect(25, 115, 900, 713), true);

    try
    {
        std::string path = savefile();
        std::cout << path << "\n";
        if(path != "inchis"){ //daca a fost selectat un folder si denumit fisierul
            result.saveToFile(path);//salvarea efectiva in memorie a proiectului 
            MessageBoxA(NULL, "Proiect exportat cu succes!!", "Mesaj", MB_OKCANCEL | MB_ICONINFORMATION);
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "eroare la salvarea proiectului" << ex.what() << "\n";
    }
}

void Canvas::draw(sf::RenderWindow& win)
{
	win.draw(workSpace);
}

bool Canvas::contains(sf::Vector2i point)
{
    sf::Vector2f workSpacePostion = workSpace.getPosition();
    sf::Vector2f workSpaceSize = workSpace.getSize();

    return (point.x >= workSpacePostion.x && point.x <= workSpacePostion.x + workSpaceSize.x
            && point.y >= workSpacePostion.y && point.y <= workSpacePostion.y + workSpaceSize.y);
}

