#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/functions.h"

int main()
{
    sf::Image image;
   image = readInImage(listUsableImages());
   sf::Texture texture;
   texture.loadFromImage(image);
   sf::Sprite sprite;
   sprite.setTexture(texture);
    

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };

    while (window.isOpen())
    {
        sf::Event event;
       
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}